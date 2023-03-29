# Practice 4. Palindromes and Balance
from collections import deque

def isPalindrome(string: str) -> bool:
  string = deque(list(string))

  while len(string) >= 2:
    if string.pop() != string.popleft():
      return False
  return True

def balance(string: str) -> bool:
  stack = deque()
  brackets = {"}" : "{", "]" : "[", ")" : "("}
  for i in string:
    if i not in "{}[]()": pass
    elif not stack or i in "{[(":
      stack.append(i)
    elif stack[-1] == brackets[i]:
      stack.pop()

  if stack:
    return False
  else:
    return True

if __name__ == "__main__":
  inputfile = "infile.txt"
  outputfile = "outfile.txt"
  with open(inputfile, 'r') as inFile:
    lines = inFile.readlines()

  with open(outputfile, 'w') as outFile:
    for line in lines:
      words = line.split()
      op = words[0]

      if op == 'P':
        if len(words) != 2:
          raise Exception("PALINDROME: invalid input")
        ret = "T" if isPalindrome(words[1]) else "F"
        outFile.write(ret+"\n")

      elif op == 'B':
        ret = "T" if balance("".join(words[1:])) else "F"
        outFile.write(ret+"\n")

      else:
        raise Exception("Undefined operator")

        
