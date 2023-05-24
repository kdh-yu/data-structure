# Practice 13. Sorting 
from math import floor
MERGE_SORT = 'M';
QUICK_SORT = 'Q';

def Merge(L1, L2):
  L = []
  while L1 and L2:
    if L1[0] > L2[0]:
      L.append(L1.pop(0))
    else:
      L.append(L2.pop(0))
  l = L1 if L1 else L2
  L = L + l
  return L

def MergeSort(L):
  if len(L) > 1:
    m = floor(len(L)/2)
    L1 = L[:m]
    L2 = L[m:]
    L = Merge(MergeSort(L1), MergeSort(L2))
  return L

def Partition(L, i, j):
  pivot = L[-1]
  while i < j:
    if L[i] > L[j]:
      L[i], L[j] = L[j], L[i]
    else:
      while L[i] <= pivot:
        i += 1
      while L[j] > pivot:
        j -= 1
  return i

def QuickSort(L, p, r):
  if p < r:
    q = Partition(L, p, r)
    L1 = QuickSort(L, p, q-1)
    L2 = QuickSort(L, q+1, r)
    for i in range(len(L1)):
      L[i] = L1[i]
    for j in range(len(L2)):
      L[q+j] = L2[j]
    print(L)
  return L

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
        # TODO
        QuickSort(arr, 0, len(arr)-1)
        pass

      else:
        raise Exception("Undefined operator")
      
      i += 1
