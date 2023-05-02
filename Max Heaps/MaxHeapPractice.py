# Practice 9. Max Heap
import sys
from math import floor
INSERT = 'I'
DELETE = 'D'
MAXIMUM = 'M'
MAX_CAPACITY = 1000
INT_MIN = -sys.maxsize

class MaxHeap:
  def __init__(self, num=MAX_CAPACITY):
    self.elements = [0] * num
    self.count = 0
    self.capacity = num

  # Given the index i of element, return the index of that element's parent in the heap
  def parent(self, i):
    return floor((i-1) / 2)
  
  # Given the index i of element, return the index of that element's left child in the heap
  def left(self, i):
    return 2 * i + 1
  
  # Given the index i of element, return the index of that element's right child in the heap
  def right(self, i):
    return 2 * i + 2

  # Insert a given element elem into the heap
  # If the insertion fails, immediately terminate the program with the error message.
  def insertElement(self, elem):
    i = self.count
    p = self.parent(i)
    self.elements[self.count] = elem
    while i > 0 and self.elements[p] < elem:
      self.elements[i], self.elements[self.parent(i)] = self.elements[self.parent(i)], self.elements[i]
      i = p
      p = self.parent(i)
    self.count += 1

  # Return the maximum of the heap if it exists
  # Otherwise, terminate program with an error
  def maximum(self):
    if self.count == 0:
      return None
    return self.elements[0]

  def MaxHeapify(self, i):
    l = self.left(i)
    r = self.right(i)
    if l <= self.count and self.elements[l] > self.elements[i]:
      largest = l
    else:
      largest = i
    
    if r <= self.count and self.elements[r] > self.elements[largest]:
      largest = r
    if largest != i:
      self.elements[i], self.elements[largest] = self.elements[largest], self.elements[i]
      self.MaxHeapify(largest)

  # Delete the maximum from the heap and return the maximum
  # If deletion fails, terminate program with an error
  def deleteMaximum(self):
    if self.count < 1:
      raise Exception("Heap Underflow")
    
    maxElement = self.elements[0]
    self.elements[0] = self.elements[self.count - 1]
    self.elements[self.count - 1] = 0
    self.count -= 1
    self.MaxHeapify(0)
    return maxElement

if __name__ == "__main__":
  input_file = "input.txt"
  output_file = "output.txt"

  h = MaxHeap()
  with open(input_file, 'r') as inFile:
    lines = inFile.readlines()
  with open(output_file, 'w') as outFile:
    for line in lines:
      words = line.split()
      op = words[0]
      if op == INSERT:
        if len(words) != 2:
          raise Exception("INSERT: invalid input")
        i = int(words[1])
        # TODO. Call the insertion method
        # If the insertion succeeds, write every element in the array into output file.
        h.insertElement(i)
        elements = [str(i) for i in h.elements if i != 0]
        outFile.write(f"{' '.join(elements)}\n")
      elif op == DELETE:
        # TODO. Call the deletion method
        # If the deletion succeeds, write every element in the array into output file.
        if not h.deleteMaximum():
          outFile.write("Deletion Failed\n")
        else:
          elements = [str(i) for i in h.elements if i != 0]
          outFile.write(f"{' '.join(elements)}\n")
          
      elif op == MAXIMUM:
        # TODO. Call the function to get the maximum
        # If getting the maximum succeeds, write the maximum into output file.
        outFile.write(f"{h.maximum()}\n")
      else:
        raise Exception("Undefined operator")
        

