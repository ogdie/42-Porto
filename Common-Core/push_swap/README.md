*This project has been created as part of the 42 curriculum by diemonte, jfaria-c.*
# push_swap

## Description
`push_swap` receives a list of integers and prints a sequence of stack operations that
sorts stack `a` in ascending order while leaving stack `b` empty.
The first number passed as an argument is the top of stack `a`.

## Instructions
Compile:
```sh
make
```
Run:
```sh
./push_swap 3 2 1
./push_swap --simple 5 4 3 2 1
./push_swap --medium 8 2 5 1 7 3
./push_swap --complex 4 67 3 87 23
./push_swap --adaptive 4 67 3 87 23
./push_swap --bench --adaptive 4 67 3 87 23
```
If no strategy is provided, `--adaptive` is used by default.

## Algorithms
### Simple strategy - O(n^2)
The simple strategy uses the Turk algorithm. It repeatedly finds the element in stack
`a` with the lowest combined rotation cost to reach its target position in stack `b`,
keeping `b` in circular descending order. After all but three elements are pushed to
`b`, the remaining three in `a` are sorted directly. Then each element in `b` is
pushed back to `a` using the same cheapest-first logic, maintaining `a` in circular
ascending order. Finally, `a` is rotated to place the minimum at the top.

### Medium strategy - O(n sqrt(n))
The medium strategy divides the normalized values into chunks of size `sqrt(n) * 3`.
Each chunk is pushed from `a` to `b` in order: elements below the chunk midpoint are
rotated to the bottom of `b`, keeping larger values accessible at the top. Once all
elements are in `b`, the same Turk cheapest-first logic from the simple strategy is
used to push every element back to `a` in the correct position. Finally, `a` is
rotated to place the minimum at the top.

### Complex strategy - O(n log n)
The complex strategy uses chunk sort with a chunk size of `2 * log2(n)^2`, producing
fewer but larger chunks than the medium strategy. Each chunk is pushed from `a` to
`b` using the same logic: smaller values within the chunk go to the bottom of `b`,
larger values stay near the top. The return phase uses the same Turk cheapest-first
algorithm to restore all elements from `b` to `a` in sorted order, followed by a
final rotation to place the minimum at the top.

### Adaptive strategy
The adaptive strategy computes the disorder of the original input before any moves.
Disorder is the ratio of inverted pairs to total pairs.
- `disorder < 0.2`: chooses the simple O(n^2) strategy.
- `0.2 <= disorder < 0.5`: chooses the medium O(n sqrt(n)) strategy.
- `disorder >= 0.5`: chooses the complex O(n log n) strategy.
For inputs of size 5 or less, the program uses a dedicated small-size sorter.

#### Complexity arguments (Push_swap operation model)
- **Simple O(n²):** n elements × up to O(n) rotations each to reach target = O(n²) ops.
- **Medium O(n√n):** ~√n chunks × O(n) rotations per chunk push/pull = O(n√n) ops.
- **Complex O(n log n):** ~O(log n) chunks × O(n) rotations per chunk push/pull = O(n log n) ops.
- **Space:** O(n) for stack b in all regimes.

## Benchmark mode
The optional `--bench` flag prints benchmark information to `stderr` only.
The operation stream still goes to `stdout`, so benchmarking can be used with
`checker` or redirected output.
Benchmark output includes:
- disorder as a percentage with two decimals
- selected strategy name
- reported complexity class
- total number of operations
- count for each operation type

## Resources
- 42 push_swap subject
- Radix sort and stack sorting references
- Big-O complexity references
AI was used to help analyze the subject, structure the implementation, and review
code patterns; all final code and design decisions were written, tested, and
validated by the learners.

## Contributions
- diemonte: project core, stack operations, complex strategy, adaptive integration.
- jfaria-c: parsing, disorder metric, simple and medium strategies, benchmark mode,
  README and validation.
