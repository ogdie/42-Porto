from __future__ import annotations
from collections import deque
from mazegen_core.maze import Maze


def shortest_path(maze: Maze) -> str:
    # Cria uma fila para guardar as coordenadas que ainda precisamos visitar.
    queue: deque = deque()
    # Coloca a entrada do labirinto na fila.
    queue.append(maze.entry)
    # Guarda de onde cada célula veio.
    previous: dict = {}
    # A entrada não veio de nenhuma outra célula.
    previous[maze.entry] = None
    # Enquanto existirem células para visitar.
    while len(queue) > 0:
        # Retira a primeira coordenada da fila.
        current = queue.popleft()
        # Se chegamos à saída, podemos parar.
        if current == maze.exit:
            break
        # Descobre os vizinhos que podemos alcançar.
        neighbors = maze.open_neighbors(current)
        # Percorre todos os vizinhos.
        for neighbor in neighbors:
            # A primeira posição da tupla é a direção.
            direction = neighbor[0]
            # A segunda posição da tupla é a coordenada.
            next_coord = neighbor[1]
            # Se já visitamos essa coordenada, ignoramos.
            if next_coord in previous:
                continue
            # Guarda de onde viemos e qual direção usamos.
            previous[next_coord] = (current, direction.letter)
            # Coloca a nova coordenada no final da fila.
            queue.append(next_coord)
    # Se a saída não foi encontrada, não existe caminho.
    if maze.exit not in previous:
        raise ValueError("No path exists between entry and exit.")
    # Lista onde vamos guardar as letras do caminho.
    path_letters = []
    # Começamos pela saída.
    cursor = maze.exit
    # Vamos voltar até chegar à entrada.
    while cursor != maze.entry:
        # Descobre de onde viemos para chegar até cursor.
        step = previous[cursor]
        # Se não existe informação, paramos.
        if step is None:
            break
        # A primeira posição é a célula anterior.
        cursor = step[0]
        # A segunda posição é a direção usada.
        letter = step[1]
        # Guarda a letra do caminho.
        path_letters.append(letter)
    # O caminho foi encontrado da saída para a entrada.
    # Por isso precisamos inverter a lista.
    path_letters.reverse()
    # Junta todas as letras numa única string.
    path = "".join(path_letters)
    return path
