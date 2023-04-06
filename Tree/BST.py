# Practice 5. Binary Search Tree
import sys
sys.setrecursionlimit(10**7)
from collections import deque
BUILD = 'B'
FIND_MIN = 'm'
FIND_MAX = 'M'

# Node implementation
class TreeNode:
  def __init__(self, data):
    self.data = data
    self.left = None
    self.right = None

class BinarySearchTree:
  def __init__(self):
    self.root = None

  # Return True if tree is empty; False otherwise
  def isEmpty(self):
    return (self.root == None)

  def findPlace(self, data):
    ptr = self.root
    if ptr.data < data:
      if ptr.left == None:
        return ptr
      else:
        return self.findPlace(ptr.left)
    elif ptr.data > data:
      if ptr.right == None:
        return ptr
      else:
        return self.findPlace(ptr.right)
    else:
      return None
    
  # Given a sequence arr of integers, start index l, the end index r, 
  # build a binary search (sub)tree that contains keys in arr[l], ..., arr[r].
  # Return the root node of the tree
  def arrayToBST(self, arr):
    if arr != sorted(arr) or not len(arr):
      return None
    
    middle = round(len(arr)/2 - 1)
    root = TreeNode(arr[middle])
    if len(arr) == 2:
      root.right = TreeNode(arr[1])
    else:
      root.left = self.arrayToBST(arr[:middle])
      root.right = self.arrayToBST(arr[middle+1:])

    return root

  # Return the node with the minimum value 
  def findMin(self):
    ptr = self.root
    while ptr.left != None:
      ptr = ptr.left
    return ptr

  # Return the node with the maximum value 
  def findMax(self):
    ptr = self.root
    while ptr.right != None:
      ptr = ptr.right
    return ptr

  def _getHeight(self, curr):
    if not curr:
      return 0
    return 1 + max(self._getHeight(curr.left), self._getHeight(curr.right))

  def _printSpaces(self, n, curr):
    for _ in range(int(n)):
      print(" ", end="")
    if not curr:
      print(" ", end="")
    else:
      print(str(curr.data), end="")

  def printTree(self):
    if not self.root:
      return 
    q = deque()
    q.append(self.root)
    temp = deque()
    cnt = 0
    height = self._getHeight(self.root) - 1
    nMaxNodes = 2**(height + 1) - 1
    while cnt <= height:
      curr = q.popleft()
      if len(temp) == 0:
        self._printSpaces(nMaxNodes / (2**(cnt+1)), curr)
      else:
        self._printSpaces(nMaxNodes / (2**cnt), curr)
      if not curr:
        temp.append(None)
        temp.append(None)
      else:
        temp.append(curr.left)
        temp.append(curr.right)
      if len(q) == 0:
        print("\n")
        q = temp
        temp = deque()
        cnt += 1

if __name__ == "__main__":
  tree = BinarySearchTree()
  with open('input.txt', 'r') as inFile:
    lines = inFile.readlines()
  with open('output.txt', 'w') as outFile:
    for line in lines:
      words = line.split()
      op = words[0]
      if op == BUILD:
        data = [int(s) for s in words[1:]]
        tree.root = tree.arrayToBST(data)
        if tree.root:
          outFile.write(BUILD + "\n")
          tree.printTree()
        else:
          raise Exception("BUILD: invalid input")
      elif op == FIND_MIN:
        found = tree.findMin()
        if not found:
          raise Exception("FindMin failed")
        else:
          outFile.write(str(found.data) + "\n")
      elif op == FIND_MAX:
        found = tree.findMax()
        if not found:
          raise Exception("FindMax failed")
        else:
          outFile.write(str(found.data) + "\n")
      else:
        raise Exception("Undefined operator")
        
