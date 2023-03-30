# Practice 4. Palindromes and Balance
from collections import deque

# Check whether string is paleindrom or not
# Return True or False
# Time complexity : O(n),
# Since it takes length n string, and take floor(n/2) calculation.
def isPalindrome(string: str) -> bool:
  # String to deque
  string = deque(list(string))
  # Since I used deque, we can check in both first / last one
  while len(string) >= 2:
    if string.pop() != string.popleft():
      return False
  return True

# Check whether brackets are balanced or not.
# Return True or False
# Time complexity : O(n)
# Check the whole length n string, it takes O(n)
# If it is bracket, check its matching
# If not, append it : O(1)
# else, pop it : O(1)
# We can simplify it to O(n).
def balance(string: str) -> bool:
  stack = deque()
  # Dictionary for each bracket's pair
  brackets = {"}" : "{", "]" : "[", ")" : "("}
  for i in string:
    # If it is not a bracket
    if i not in "{}[]()":
      pass
    # stack is empty, or opening bracket : append it
    elif not stack or i in "{[(":
      stack.append(i)
    # If it is matched well, instead of appending, pop
    elif stack[-1] == brackets[i]:
      stack.pop()

  if stack:
    return False
  else:
    return True

if __name__ == "__main__":
  # Instead of using "python practice4.py input.txt output.txt", just use it
  # for vscode code runner...
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

      # Also check even if it has space (So sentence also okay!)
      # As we can see in infile.txt
      elif op == 'B':
        ret = "T" if balance("".join(words[1:])) else "F"
        outFile.write(ret+"\n")

      else:
        raise Exception("Undefined operator")

        
