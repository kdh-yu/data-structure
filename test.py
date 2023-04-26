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

  # Return True if tree is empty; False otherwise
  def isEmpty(self):
    return self.root == None

  # Given a sequence arr of integers, start index l, the end index r, 
  # build a binary search (sub)tree that contains keys in arr[l], ..., arr[r].
  # Return the root node of the tree
  def arrayToBST(self, arr, l, r):
    for i in range(len(arr) - 1):
      if arr[i] > arr[i + 1]:
        print("Error : Sequence is not sorted in ascending order.")
        exit()

    if l > r:
      return None

    mid = (l + r) // 2
    root = TreeNode(arr[mid])
    root.left = self.arrayToBST(arr, l, mid - 1)
    root.right = self.arrayToBST(arr, mid + 1, r)
    return root

  # Return the node with the minimum value 
  def findMin(self):
    if self.root is None:
      return None
    else:
      p = self.root
    while p.left is not None:
      p = p.left
    return p

  # Return the node with the maximum value 
  def findMax(self):
    if self.root is None:
      return None
    else:
      p = self.root
    while p.right is not None:
      p = p.right
    return p

  def _getHeight(self, curr):
    if not curr:
      return 0
    return 1 + max(self._getHeight(curr.left), self._getHeight(curr.right))

  def _printSpaces(self, n, curr):
    for i in range(int(n)):
      print("  ", end="")
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
  def search(self, query):
    curr = self.root
    while curr is not None :
      if curr == query :
        return curr.key
      elif query < curr.key :
        curr = curr.left
      else :
        curr = curr.right
    return None


  # Given an output file, write the keys of all the nodes 
  # visited in inorder traversal
  def writeInorder(self, outFile):
    def inorder_traversal(root) :
      if root is not None :
        inorder_traversal(root.left)
        outFile.write(f"{root.key} ")
        inorder_traversal(root.right)
    inorder_traversal(self.root)

  # Given an output file, write the keys of all the nodes 
  # visited in preorder traversal
  def writePreorder(self, outFile):
    def preorder_traversal(root) :
      if root is not None :
        print(root.key)
        preorder_traversal(root.left)
        preorder_traversal(root.right)
    preorder_traversal(self.root)


  
  # Given an output file, write the keys of all the nodes 
  # visited in postorder traversal
  def writePostorder(self, outFile):
    def postorder_traversal(root) :
      if root is not None :
        postorder_traversal(root.left)
        postorder_traversal(root.right)
        print(root.key)
    postorder_traversal(self.root)
  
  # If node with key k alreay exists in the tree, do nothing
  # Otherwise, insert new node with key k 
  def insertNode(self, k):
    if self.root is None:
      self.root = TreeNode(k)
      return

    curr = self.root
    while True:
      if k < curr.key:
        if curr.left is None:
          curr.left = TreeNode(k)
          return
        else:
          curr = curr.left
      elif k > curr.key:
        if curr.right is None:
          curr.right = TreeNode(k)
          return
        else:
          curr = curr.right
      else:
        # k is equal to the current node's key, so the node already exists
        return

  # If deletion fails, immediately terminate the program
  # Otherwise, delete the node with key k
  def deleteNode(self, k):
    if self.root is None :
      return

    #Find the node to delete and its parent
    parent = None
    curr = self.root
    while curr is not None and curr.key != k :
      parent = curr
      if k < curr.key :
        curr = curr.left
      else :
        curr = curr.right

    if curr is None :
      return

    if curr.left is None and curr.right is None :
      #Case 1 : The node to delete has no children
      if parent is None :
        self.root = None
      elif parent.left == curr :
        parent.left = None
      else :
        parent.right = None
    elif curr.left is not None and curr.right is not None :
      #Case 3 : The node to delete has two children
      succ = curr.right
      while succ.left is not None :
        succ = succ.left
      self.deleteNode(succ.key)
      curr.key = succ.key
    else :
      #Case 2 : The node to delete has one child
      if curr.left is not None :
        child = curr.left
      else :
        child = curr.right
      if parent is None :
        self.root = child
      elif parent == curr :
        parent.left = child
      else :
        parent.right = child

if __name__ == "__main__":
  inputfile = "inputfile.txt"
  outputfile = "outputfile.txt"
  
  tree = BinarySearchTree()
  with open(inputfile, 'r') as inFile:
    lines = inFile.readlines()
  with open(outputfile, 'w') as outFile:
    for line in lines:
      words = line.split()
      op = words[0]
      if op == BUILD:
        data = [int(s) for s in words[1:]]
        tree.root = tree.arrayToBST(data, 0, len(data) - 1)
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
        pass
      elif op == INORDER:
        # Practice 5. Call the function for inorder traversal
        pass
      elif op == PREORDER:
        # Practice 5. Call the function for preorder traversal
        pass
      elif op == POSTORDER:
        # Practice 5. Call the function for postorder traversal
        pass
      elif op == INSERT:
        if len(words) != 2:
          raise Exception("INSERT: invalid input")
        k = int(words[1])
        # TODO. Practice 6. Call the function for insertion
        tree.insertNode(k)
      elif op == DELETE:
        if len(words) != 2:
          raise Exception("DELETE: invalid input")
        k = int(words[1])
        # TODO. Practice 6. Call the function for deletion
        pass
      else:
        raise Exception("Undefined operator")