# Practice 13. Sorting 
from math import floor
MERGE_SORT = 'M'
QUICK_SORT = 'Q'

def Merge(L1, L2):
  tmp = []
  while L1 and L2:
    if L1[0] > L2[0]:
      tmp.append(L1.pop(0))
    else:
      tmp.append(L2.pop(0))
  l = L1 if L1 else L2
  tmp = tmp + l
  return tmp

def MergeSort(L):
  if len(L) <= 1:
    return L
  mid = len(L) // 2
  L1 = MergeSort(L[:mid])
  L2 = MergeSort(L[mid:])
  tmp = Merge(L1, L2)
  return tmp

def Partition(L, low, high):
  pivot = L[high]
  l = low
  r = high
  while l < r:
    while l < high and L[l] > pivot:
      l += 1
    while r > low and L[r] <= pivot:
      r -= 1
    if l < r:
      L[l], L[r] = L[r], L[l]
  L[l], L[high] = L[high], L[l]
  return l

def QuickSort(L, l, r):
  if l < r:
    p = Partition(L, l, r)
    QuickSort(L, l, p-1)
    QuickSort(L, p+1, r)

if __name__ == "__main__":
  with open('input.txt', 'r') as inFile:
    lines = inFile.readlines()
  with open('output.txt', 'w') as outFile:
    i = 0
    while i < len(lines):
      line = lines[i].split()
      if len(line) != 2:
        raise Exception("Error: invalid input")
      op = line[0]
      size = int(line[1])
      i += 1
      arr = [int(j) for j in lines[i].split()]

      if op == MERGE_SORT:
        if len(line) != 2:
          raise Exception("MERGE_SORT: invalid input")
        sortedList = MergeSort(arr)
        sortedList = [str(j) for j in sortedList]
        outFile.write(" ".join(sortedList))
        outFile.write("\n")
        
      elif op == QUICK_SORT:
        if len(line) != 2:
          raise Exception("QUICK_SORT: invalid input")
        QuickSort(arr, 0, len(arr)-1)
        sortedList = [str(j) for j in arr]
        outFile.write(" ".join(sortedList))
        outFile.write("\n")

      else:
        raise Exception("Undefined operator")
      
      i += 1
