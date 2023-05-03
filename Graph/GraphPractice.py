# Practice 10. Graph Representation 
from collections import deque
from pprint import pprint
CONSTRUCT = 'C'
IS_ADJACENT = 'I'
GET_NEIGHBORS = 'N'
BFS = 'B'
DFS = 'D'
REACHABILITY = 'R'
TOPOLOGICAL_SORT = 'T'
SHORTEST_PATH = 'S'

class Graph:
  # TODO. Define a constructor and proper methods
  def __init__(self):
    pass
  
  def Construct(self, v):
    self.nodes = v
    self.adjacency = [[0] * v for _ in range(v)]

  def AddVertice(self, v1, v2, w):
    self.adjacency[v1][v2] = w

  def IsAdjacent(self, v1, v2):
    if self.adjacency[v1][v2] != 0:
      return 'T'
    else:
      return 'F'

  def Neighbors(self, v):
    adjacency = []
    for i in range(self.nodes):
      if self.adjacency[v][i] != 0:
        adjacency.append(str(i))
    return adjacency


if __name__ == "__main__":
  g = Graph()
  with open('input.txt', 'r') as inFile:
    lines = inFile.readlines()
  with open('output.txt', 'w') as outFile:
    i = 0

    while i < len(lines):
      words = lines[i].split()
      op = words[0]

      if op == CONSTRUCT:
        if len(words) != 3:
          raise Exception("CONSTRUCT: invalid input")
        
        n, m = int(words[1]), int(words[2])
        g.Construct(m)
        for _ in range(m):
          i += 1
          v1, v2, w = map(int, lines[i].split())
          g.AddVertice(v1, v2, w)

      elif op == IS_ADJACENT:
        if len(words) != 3:
          raise Exception("IS_ADJACENT: invalid input")
        u, v = int(words[1]), int(words[2])
        outFile.write(f'{u} {v} {g.IsAdjacent(u, v)}\n')

      elif op == GET_NEIGHBORS:
        if len(words) != 2:
          raise Exception("GET_NEIGHBORS: invalid input")
        u = int(words[1])
        outFile.write(" ".join(g.Neighbors(u)))
        outFile.write('\n')

      else:
        raise Exception("Undefined operator")
      i += 1
