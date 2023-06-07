# Practice 15. Autocomplete system
BUILD_TRIE = 'T'
AUTOCOMPLETE = 'A'
ENDS_HERE = '#'

class Trie:
  def __init__(self):
    self.root = {}
    self.l = []
  def reset_l(self):
    self.l = []

  def build(self, ss):
    for s in ss:
      cur = self.root
      for char in s:
        if char not in cur:
          cur[char] = {}
        cur = cur[char]
      cur[ENDS_HERE] = s

  def search(self, cur):
    if ENDS_HERE in cur:
      self.l.append(cur[ENDS_HERE])
    else:
      for c in cur.keys():
        self.search(cur[c])
  
  def check(self, s):
    cur = self.root
    i = 0
    while i < len(s):
      if s[i] in cur:
        cur = cur[s[i]]
        i += 1
      else:
        break
    if i == len(s):
      self.reset_l()
      self.search(cur)
      return " ".join(self.l)
  
  
if __name__ == '__main__':
  with open('input.txt', 'r') as inFile:
    lines = inFile.readlines()
  with open('output.txt', 'w') as outFile:
    i = 0
    t = Trie()
    while i < len(lines):
      words = lines[i].split()
      op = words[0]

      if op == BUILD_TRIE:
        if len(words) != 2:
          raise Exception("BUILD_TRIE: invalid input")
        n = int(words[1])
        strings = []
        while n:
          i += 1
          strings.append(lines[i].strip())
          n -= 1
        # TODO. Build a trie with "strings"
        t.build(strings)

      elif op == AUTOCOMPLETE:
        if len(words) != 2:
          raise Exception("AUTOCOMPLETE: invalid input")
        prefix = words[1]
        # TODO. Run autocomplete with "prefix" and write results into "outFile"
        outFile.write(t.check(prefix))
        outFile.write("\n")

      else:
        raise Exception("Undefined operator")
      i += 1
