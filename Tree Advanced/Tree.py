# Practices 6&7. Binary Search Tree Operations
from collections import deque
BUILD = 'B'
FIND_MIN = 'm'
FIND_MAX = 'M'
SEARCH = 'S'
INSERT = 'I'
DELETE = 'D'
INORDER = 'N'
PREORDER = 'R'
POSTORDER = 'O'

# Node implementation
class TreeNode:
  def __init__(self, k, l=None, r=None):
    self.key = k
    self.left = l
    self.right = r

class BinarySearchTree:
  def __init__(self):
    self.root = None
    self.cur = self.root

  # Return True if tree is empty; False otherwise
  # Just checking, so O(1)
  def isEmpty(self):
    return self.root == None

  # Given a sequence arr of integers, build a binary search (sub)tree.
  # Return the root node of the tree
  # It is almost similar to divide part in merge sort.
  # So time complexity is O(NlogN)
  def arrayToBST(self, arr: list[int]) -> TreeNode:
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
  # in balanced tree, height is O(logN)
  # So, time complexity is O(logN)
  def findMin(self, st=None):
    if not st:
      ptr = self.root
    else:
      ptr = st
    while ptr.left != None:
      ptr = ptr.left
    return ptr

  # Return the node with the maximum value 
  # in balanced tree, height is O(logN)
  # So, time complexity is O(logN)
  def findMax(self, st=None):
    if not st:
      ptr = self.root
    else:
      ptr = st
    while ptr.right != None:
      ptr = ptr.right
    return ptr

  # O(logN)
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
      print(str(curr.key), end="")

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

  # Given a query, search for the node whose key is equal to query.
  # If the node exists, return the key
  # Otherwise, return nullptr  
  # On average, search function takes time complexity of O(logN).
  # Here, N is the number of nodes in tree.
  def search(self, st, query):
    def s(p, k):
      if not p:
        return
      if k == p.key:
        return p
      elif k < p.key and p.left != None:
        return s(p.left, k)
      elif k > p.key and p.right != None:
        return s(p.right, k)
      return p
    
    return s(st, query)

  # Given an output file, write the keys of all the nodes 
  # visited in inorder traversal
  # We need to visit all N nodes, so time complexity is O(N)
  def writeInorder(self, p, file):
    # Practice 6
    if p:
      self.writeInorder(p.left, file)
      file.write(f'{p.key} ')
      self.writeInorder(p.right, file)

  # Given an output file, write the keys of all the nodes 
  # visited in preorder traversal
  # We need to visit all N nodes, so time complexity is O(N)
  def writePreorder(self, p, file):
    # Practice 6
    # TODO
    if p:
      file.write(f'{p.key} ')
      self.writePreorder(p.left, file)
      self.writePreorder(p.right, file)
  
  # Given an output file, write the keys of all the nodes 
  # visited in postorder traversal
  # We need to visit all N nodes, so time complexity is O(N)
  def writePostorder(self, p, file):
    # Practice 6
    # TODO
    if p:
      self.writePostorder(p.left, file)
      self.writePostorder(p.right, file)
      file.write(f'{p.key} ')
  
  # If node with key k alreay exists in the tree, do nothing
  # Otherwise, insert new node with key k 
  # Find location to insert : same with search, so O(logN)
  # Adding Nodes : O(1)
  # So, time complexity is O(logN)
  def insertNode(self, p, k):
    # Practice 7
    if p == None:
      p = TreeNode(k)
    elif k < p.key:
      p.left = self.insertNode(p.left, k)
    elif k > p.key:
      p.right = self.insertNode(p.right, k)
    return p
      
  # If deletion fails, immediately terminate the program
  # Otherwise, delete the node with key k
  # It takes tree's root and key to remove, and returns root node of that subtree.
  # When calling, we just need to call like this:
  # tree.root = tree.deleteNode(tree.root, key)
  # On average, time complexity is O(logN).
  # Here, N is the number of nodes in tree.
  def deleteNode(self, r: TreeNode, k: int) -> TreeNode:
    if r == None:
      return None
    if k < r.key:
      r.left = self.deleteNode(r.left, k)
    elif k > r.key:
      r.right = self.deleteNode(r.right, k)
    else:
      if r.left == None:
        return r.right
      elif r.right == None:
        return r.left
      p = r
      while p.left != None:
        p = p.left
      r.key = p.key
      r.right = self.deleteNode(r.right, k)
    return r

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
          outFile.write(str(found.key) + "\n")

      elif op == FIND_MAX:
        found = tree.findMax()
        if not found:
          raise Exception("FindMax failed")
        else:
          outFile.write(str(found.key) + "\n")

      elif op == SEARCH:
        if len(words) != 2:
          raise Exception("SEARCH: invalid input")
        k = int(words[1])
        # Practice 5. Call the function for search
        found = tree.search(tree.root, k)
        if found:
          outFile.write(str(found.key) + "\n")
        else:
          raise Exception("SEARCH: Not found")
        pass

      elif op == INORDER:
        # Practice 5. Call the function for inorder traversal
        tree.writeInorder(tree.root, outFile)
        outFile.write('\n')

      elif op == PREORDER:
        # Practice 5. Call the function for preorder traversal
        tree.writePreorder(tree.root, outFile)
        outFile.write('\n')

      elif op == POSTORDER:
        # Practice 5. Call the function for postorder traversal
        tree.writePostorder(tree.root, outFile)
        outFile.write('\n')

      elif op == INSERT:
        if len(words) != 2:
          raise Exception("INSERT: invalid input")
        k = int(words[1])
        # TODO. Practice 6. Call the function for insertion
        tree.root = tree.insertNode(tree.root, k)
        if tree.search(tree.root, k):
          outFile.write(f"I {k}\n")

      elif op == DELETE:
        if len(words) != 2:
          raise Exception("DELETE: invalid input")
        k = int(words[1])
        # TODO. Practice 6. Call the function for deletion
        tree.root = tree.deleteNode(tree.root, k)
        if tree.search(tree.root, k).key != k:
          outFile.write(f"D {k}\n")

      else:
        raise Exception("Undefined operator")
        
