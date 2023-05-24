# Practice 12. Search
from math import floor
BINARY_SEARCH = 'B'
PERFECT_SQUARE = 'P'

def BinarySearch(A, x, l, r):
  if l > r:
    return -1
  else:
    mid = floor((l+r)/2)
    if x == A[mid]:
      return mid
    elif x < A[mid]:
      return BinarySearch(A, x, l, mid-1)
    else:
      return BinarySearch(A, x, mid+1, r)

def PerfectSquare(x, l, r):
  if l > r:
    return -1
  else:
    mid = floor((l+r)/2)
    if mid * mid == x:
      return mid
    elif mid * mid > x:
      return PerfectSquare(x, l, mid-1)
    else:
      return PerfectSquare(x, mid+1, r)


if __name__ == "__main__":
  with open('input.txt', 'r') as inFile:
    lines = inFile.readlines()
  with open('output.txt', 'w') as outFile:
    i = 0
    while i < len(lines):
      line = lines[i]
      words = line.split()
      op = words[0]

      if op == BINARY_SEARCH:
        if len(words) != 3:
          raise Exception("BINARY_SEARCH: invalid input")
        size, x = int(words[1]), int(words[2])
        i += 1
        sequence = [int(i) for i in lines[i].split()]
        search = BinarySearch(sequence, x, 0, size-1)

        if search == -1:
          search = 'N'

        outFile.write(f'B {size} {x}\n')
        outFile.write(f'{search}\n')

      elif op == PERFECT_SQUARE:
        if len(words) != 2:
          raise Exception("PERFECT_SQUARE: invalid input")
        x = int(words[1])
        search = PerfectSquare(x, 1, x)
        search = 'T' if search != -1 else 'F'
        outFile.write(f'{search}\n')

      else:
        raise Exception("Undefined operator")
      i += 1

        
