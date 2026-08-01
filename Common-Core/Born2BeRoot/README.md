*This project has been created as part of the 42 curriculum by diemonte.*

# Born2beRoot

## Description

Born2beRoot is a system administration project from the 42 curriculum. The goal is to create and configure a secure Linux server inside a virtual machine, following strict rules and implementing fundamental system administration concepts.

The project covers: virtualization, disk partitioning with encryption (LUKS) and logical volume management (LVM), SSH configuration, firewall setup, password policies, sudo configuration, user and group management, AppArmor security, and system monitoring scripting.

## Instructions

### Requirements

- VirtualBox (or UTM for Apple Silicon)
- Debian 13 (Trixie) netinstall ISO

### Setup

1. Create a VirtualBox VM (Linux/Debian 64-bit, 2048MB RAM, 20GB dynamic VDI disk)
2. Boot from the Debian netinstall ISO
3. During installation, select **"Guided - use entire disk and set up encrypted LVM"** for partitioning
4. Configure the following logical volumes inside the LUKS container:
   - `root` (~14GB, ext4, mounted at `/`)
   - `home` (~5GB, ext4, mounted at `/home`)
   - `swap_1` (~1GB, swap)
   - `/boot` (1GB, ext4, outside LUKS)
5. Complete the Debian base installation without a graphical environment
6. Apply all post-installation configurations as described below

### Post-Installation Configuration

```bash
# SSH — port 4242, root login disabled
nano /etc/ssh/sshd_config
# Set: Port 4242 | PermitRootLogin no | PasswordAuthentication yes
systemctl restart ssh

# UFW — only port 4242 open
apt install ufw -y
ufw allow 4242
ufw enable

# Password policy
nano /etc/login.defs
# Set: PASS_MAX_DAYS 30 | PASS_MIN_DAYS 2 | PASS_WARN_AGE 7
apt install libpam-pwquality -y
nano /etc/security/pwquality.conf
# Set: minlen=10 | dcredit=-1 | ucredit=-1 | lcredit=-1 | maxrepeat=3 | usercheck=1 | difok=7

# Apply expiration to existing accounts
chage -M 30 -m 2 -W 7 root
chage -M 30 -m 2 -W 7 diemonte

# Sudo configuration
apt install sudo -y
visudo
# Add: Defaults passwd_tries=3
# Add: Defaults badpass_message="Wrong password! Try again."
# Add: Defaults logfile="/var/log/sudo/sudo.log"
# Add: Defaults log_input, log_output
# Add: Defaults requiretty
# Add: Defaults secure_path="/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/snap/bin"
mkdir -p /var/log/sudo

# User and groups
groupadd user42
usermod -aG sudo diemonte
usermod -aG user42 diemonte

# Monitoring script
nano /usr/local/bin/monitoring.sh
chmod +x /usr/local/bin/monitoring.sh
crontab -e
# Add: */10 * * * * /usr/local/bin/monitoring.sh
```

### Verifying the Setup

```bash
# Check SSH
ss -tlnp | grep 4242

# Check UFW
ufw status

# Check AppArmor
aa-status

# Check partitions
lsblk

# Check groups
groups diemonte

# Check boot target (must be multi-user, not graphical)
systemctl get-default

# Run monitoring script manually
bash /usr/local/bin/monitoring.sh
```

### Signature

To generate the `signature.txt` for submission, run on Windows:

```
certUtil -hashfile "C:\Users\DiegoMenezesMonteiro\VirtualBox VMs\diemonte42\diemonte42.vdi" sha1
```

Paste the resulting hash into a `signature.txt` file at the root of your Git repository.

## Project Description

### Operating System Choice: Debian

**Debian** was chosen over Rocky Linux for this project. Debian is the recommended choice for newcomers to system administration due to its stability, extensive documentation, and large community support.

| | Debian | Rocky Linux |
|---|---|---|
| **Base** | Independent | RHEL-based |
| **Package manager** | apt / dpkg | dnf / rpm |
| **Security module** | AppArmor | SELinux |
| **Firewall** | UFW | firewalld |
| **Target users** | General purpose, servers, desktops | Enterprise environments |
| **Release cycle** | Stable, conservative | Follows RHEL releases |
| **Complexity** | Lower — recommended for beginners | Higher — enterprise-oriented |
| **Documentation** | Extensive community docs | Enterprise-focused docs |

Debian's `apt` package manager is straightforward to use, its configuration files follow well-documented conventions, and AppArmor is simpler to understand than SELinux for an introductory project.

### Design Choices

**Partitioning:**
The disk is partitioned with LUKS encryption wrapping an LVM volume group. This means the entire logical volume structure (root, home, swap) is encrypted at rest. The `/boot` partition is kept outside the LUKS container since the bootloader (GRUB) needs to read the kernel before the decryption passphrase can be entered.

- `/boot` — 1GB, ext4, unencrypted
- `sda5_crypt` — LUKS encrypted container
  - `root` — 14GB, ext4, mounted at `/`
  - `home` — 5GB, ext4, mounted at `/home`
  - `swap_1` — 1GB, swap

**Security policies:**
- SSH runs only on port 4242 with root login disabled
- UFW blocks all traffic except port 4242
- Passwords require minimum 10 characters, with uppercase, lowercase, and numeric characters, no more than 3 consecutive identical characters, and must differ from the previous password by at least 7 characters
- Passwords expire every 30 days with a minimum of 2 days between changes and a 7-day warning
- `sudo` is limited to 3 password attempts, logs all input/output, requires a real TTY, and restricts executable paths

**User management:**
- `diemonte` belongs to `sudo` (administrative privileges) and `user42` (project-required group)
- Root login via SSH is disabled; administrative access is only possible through `sudo`

**Services:**
- `openssh-server` — remote access on port 4242
- `ufw` — firewall
- `apparmor` — mandatory access control
- `cron` — periodic execution of the monitoring script

### AppArmor vs SELinux

| | AppArmor | SELinux |
|---|---|---|
| **Model** | Path-based (profiles per program) | Label-based (every file/process has a security context) |
| **Complexity** | Lower — easier to configure and understand | Higher — steeper learning curve |
| **Default in** | Debian, Ubuntu | RHEL, Rocky Linux, Fedora |
| **Configuration** | Profiles in `/etc/apparmor.d/` | Policies via `semanage`, `restorecon`, etc. |
| **Modes** | Enforce, Complain | Enforcing, Permissive, Disabled |
| **Use case** | Confining specific programs/processes | Fine-grained system-wide mandatory access control |

AppArmor confines individual programs based on file path rules defined in profiles. SELinux applies security labels to every object on the system (files, processes, ports) and enforces rules based on those labels, which gives more granular control but requires significantly more configuration knowledge.

### UFW vs firewalld

| | UFW | firewalld |
|---|---|---|
| **Full name** | Uncomplicated Firewall | firewalld |
| **Default in** | Debian, Ubuntu | RHEL, Rocky Linux, Fedora |
| **Backend** | iptables / nftables | nftables / iptables |
| **Interface** | Simple command-line | CLI (`firewall-cmd`) + zones concept |
| **Complexity** | Low — designed for simplicity | Medium — more flexible with zones |
| **Dynamic rules** | No (requires reload) | Yes (rules apply without restart) |
| **Zones** | No | Yes (public, internal, dmz, etc.) |

UFW is a frontend for iptables/nftables designed to make firewall configuration simple. firewalld uses the concept of zones to define trust levels for network connections, offering more flexibility for complex network environments but requiring more knowledge to configure correctly.

### VirtualBox vs UTM

| | VirtualBox | UTM |
|---|---|---|
| **Platform** | Windows, macOS (Intel), Linux | macOS (Intel + Apple Silicon) |
| **Architecture** | x86_64 (Type 2 hypervisor) | x86_64 + ARM (uses QEMU) |
| **Cost** | Free and open source | Free (Mac App Store version paid) |
| **Performance** | Good on x86_64 hosts | Native ARM performance on Apple Silicon |
| **Snapshots** | Yes | Yes |
| **GUI** | Full-featured | Simple and clean |
| **Use case** | Cross-platform x86 virtualization | macOS users, especially Apple Silicon |

VirtualBox is the standard choice for this project on Windows and Intel-based systems. UTM is the alternative for Apple Silicon Macs (M1/M2/M3) where VirtualBox is not natively supported, as UTM leverages QEMU to provide both emulation and virtualization.

## Resources

### References

- [Debian Official Documentation](https://www.debian.org/doc/)
- [Debian Administrator's Handbook](https://debian-handbook.info/)
- [AppArmor Documentation](https://wiki.debian.org/AppArmor)
- [UFW Documentation](https://help.ubuntu.com/community/UFW)
- [LVM HowTo — tldp.org](https://tldp.org/HOWTO/LVM-HOWTO/)
- [LUKS/dm-crypt Documentation](https://gitlab.com/cryptsetup/cryptsetup)
- [Linux PAM Documentation](http://www.linux-pam.org/Linux-PAM-html/)
- [sudoers man page](https://www.sudo.ws/docs/man/sudoers.man/)
- [cron man page](https://man7.org/linux/man-pages/man8/cron.8.html)
- [VirtualBox Documentation](https://www.virtualbox.org/wiki/Documentation)

### AI Usage

Claude (Anthropic) was used as a tutor throughout this project. The AI was not used to complete tasks directly — instead, it was used to:

- Explain concepts before hands-on work (e.g., how LUKS+LVM layering works, what AppArmor does, why `/boot` must be outside the LUKS container)
- Guide step-by-step through the installation and configuration process
- Clarify error messages and unexpected behavior encountered during setup
- Review configurations before applying them

All commands were understood and executed by the student. The AI served as an interactive reference and learning aid, consistent with the 42 approach of understanding before executing.
