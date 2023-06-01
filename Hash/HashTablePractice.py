# Practice 12. Use hash tables
from itertools import combinations
TWO_SUM = 'T'
SYMMETRIC_PAIRS = 'S'

def readIntegers(n: int, s: str) -> list:
  words = s.split()
  assert(len(words) == n)
  arr = [int(w) for w in words]
  return arr

def twoSum(n, arr):
  hashTable = {}
  for i, j in combinations(arr, 2):
    hashTable[i+j] = True
  return hashTable.get(n)

def symmetricPairs(arr):
  hashTable = {}
  symmetric = []
  for pair in arr:
    exist = hashTable.get(pair[0]) and hashTable.get(pair[1])
    if exist:
      symmetric.append(pair)
    else:
      hashTable[pair[0]] = pair[1]
      hashTable[pair[1]] = pair[0]
  symmetric = list(map(lambda x: (x[1], x[0]) if x[0] > x[1] else x, symmetric))
  return symmetric

if __name__ == "__main__":
  with open('input.txt', 'r') as inFile:
    lines = inFile.readlines()
  with open('output.txt', 'w') as outFile:
    i = 0
    while i < len(lines):
      words = lines[i].split()
      op = words[0]

      if op == TWO_SUM:
        if len(words) != 3:
          raise Exception("TWO_SUM: invalid input")
        k, n = int(words[1]), int(words[2])
        i += 1
        nums = readIntegers(n, lines[i])
        summed = twoSum(k, nums)
        if summed:
          outFile.write("T\n")
        else:
          outFile.write("F\n")
        # TODO 
        # Take k and nums as input, and run twoSum(k, nums)
        # Write whether two sum exists into output file

      elif op == SYMMETRIC_PAIRS:
        if len(words) != 2:
          raise Exception("SYMMETRIC_PAIRS: invalid input")
        n = int(words[1])
        pairs = []
        while n:
          i += 1
          words = lines[i].split()
          if len(words) != 2:
            raise Exception("SYMMETRIC_PAIRS: invalid input")
          a, b = int(words[0]), int(words[1])
          pairs.append((a, b))
          n -= 1
        symPairs = symmetricPairs(pairs)
        for pair in symPairs:
          outFile.write(f"{pair[0]} {pair[1]}\n")
        # TODO
        # Take pairs as input, and run symmetricPairs(pairs)
        # Write every symmetric pair into output file

      else:
        raise Exception("Undefined operator")
      i += 1

