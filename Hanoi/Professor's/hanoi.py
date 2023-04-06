# Tower of Hanoi
# Daily Coding Problem, Chapter 12, p146
import sys
import unittest

def hanoi(n: int, a=1, b=2, c=3) -> int:
  if n < 1: return 0
  numAToB = hanoi(n-1, a, c, b)
  print("Move {} to {}".format(a, c))
  numBToC = hanoi(n-1, b, a, c)
  return numAToB + 1 + numBToC

def test(n: int) -> int:
  print("Hanoi({})".format(n))
  return hanoi(n)

class Test(unittest.TestCase):
  def testHanoi(self):
    self.assertEqual(test(1), 1)
    self.assertEqual(test(2), 3)
    self.assertEqual(test(3), 7)
    self.assertEqual(test(4), 15)
    self.assertEqual(test(7), 127)

if __name__ == "__main__":
  if len(sys.argv) == 2:
    hanoi(int(sys.argv[1]))
  else:
    unittest.main()
    
