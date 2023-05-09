# Practice 10. Graph Representation 
import sys
from collections import deque
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
    self.adjacency = {}

  def AddVertice(self, v1, v2, w):
    if self.adjacency.get(v1) == None:
      self.adjacency[v1] = []
    if self.adjacency.get(v2) == None:
      self.adjacency[v2] = []
    self.adjacency[v1].append((v2, w))

  def IsAdjacent(self, v1, v2):
    if v2 in map(lambda x: x[0], self.adjacency[v1]):
      return 'T'
    else:
      return 'F'

  def Neighbors(self, v):
    adjacency = []
    for tmp in self.adjacency[v]:
      adjacency.append(str(tmp[0]))
    return adjacency
  
  def DepthFirstSearch(self, st):
    visited = []
    def DFS(u, l):
      l.append(u)
      for (v, w) in self.adjacency[u]:
        if v not in l:
          DFS(v, l)
    DFS(st, visited)
    visited = [str(i) for i in visited]
    return " ".join(visited)

  def BreadthFirstSearch(self):
    pass

  def PrintGraph(self):
    for i in self.adjacency.keys():
      print(f"{i} : {self.adjacency[i]}")

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

      elif op == DFS:
        outFile.write(g.DepthFirstSearch(int(words[1])))
        outFile.write("\n")

      elif op == BFS:
        pass

      elif op == TOPOLOGICAL_SORT:
        pass
      
      elif op == SHORTEST_PATH:
        pass

      else:
        raise Exception("Undefined operator")
      
      i += 1