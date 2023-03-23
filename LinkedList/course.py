ADD = 'A'
DELETE = 'D'
FIND = 'F'

# Node
class Student:
  def __init__(self, i, n, p=None):
    self.id = i
    self.name = n
    self.next = p

# Linked List
class Course:
  def __init__(self):
    self.head = None

  def __len__(self):
    return self.size

  def isEmpty(self):
    return self.size == 0

  def addStudent(self, newID, newName):
    stu = Student(newID, newName)
    success = True
    # If empty
    if self.head == None:
      self.head = stu
    
    else:
      p = self.head
      while p.next != None:
        if p.id <= newID and p.next.id > newID: break
        p = p.next

      # Same ID
      if p.id == newID:
        success = False
    
      # Insert node at the beginning
      elif p == self.head and p.id > newID:
        stu.next = self.head
        self.head = stu
      
      # Insert node at the end
      elif p.next == None:
        p.next = stu
      
      # Insert node in the middle
      else:
        stu.next = p.next
        p.next = stu
    
    return success

  def deleteStudent(self, queryID):
    p = self.head
    while True:
      # If last node
      if p.next == None:
        # Delete the first node
        if p.id == queryID:
          self.head = None
          return True
        # Failed to search
        else:
          return False
        
      # Delete the first node
      elif p == self.head and p.id == queryID:
        self.head = p.next
        return True
      
      elif p.next.id == queryID:
        # Delete the last node
        if p.next.next == None:
          p.next = None
          return True
        # Delete the intermediate node
        else:
          p.next = p.next.next
          return True
      else:
        # Failed to search
        if p.next == None:
          return False
        # Traverse
        else:
          p = p.next
        
  def find(self, queryID):
    p = self.head
    while p != None and p.id != queryID:
      p = p.next
    return p

  def write(self, outFile):
    p = self.head
    while p != None:
      outFile.write(f'{p.id} {p.name} ')
      p = p.next
    outFile.write('\n')

if __name__ == "__main__":
  infile = "infile.txt"
  outfile = "outfile.txt"
  
  course = Course()
  with open(infile, 'r') as inFile:
    lines = inFile.readlines()

  with open(outfile, 'w') as outFile:
    for line in lines:
      words = line.split()
      op = words[0]

      if op == ADD:
        if len(words) != 3:
          raise Exception("ADD: invalid input")
        i, n = int(words[1]), words[2]
        if course.addStudent(i, n):
          course.write(outFile)
        else:
          outFile.write("Addition failed\n")

      elif op == DELETE:
        if len(words) != 2:
          raise Exception("DELETE: invalid input")
        i = int(words[1])
        if course.deleteStudent(i):
          course.write(outFile)
        else:
          outFile.write("Deletion failed\n")

      elif op == FIND:
        if len(words) != 2:
          raise Exception("DELETE: invalid input")
        i = int(words[1])
        found = course.find(i)
        if not found:
          outFile.write("Search failed\n")
        else:
          outFile.write(str(found.id) + " " + found.name + "\n")

      else:
        raise Exception("Undefined operator")
        
