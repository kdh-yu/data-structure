# Node
class Node:
    def __init__(self, k, p=None):
        self.key = k
        self.next = p

# Linked List
class LinkedList:
    def __init__(self):
        self.head = None

    def Search(self, k):
        p = self.head
        while p != None:
            if p.key == k:
                break
            p = p.next
        return p
    
    def Traverse(self):
        p = self.head
        while p != None:
            print(f"{p.key} ")
            p = p.next
        print()

    def Insert(self, k, i):
        newNode = Node(k)
        
        # If empty
        if self.head == None:
            self.head = newNode

        else:
            p = self.head
            for _ in range(i):
                if p.next == None:
                    break
                p = p.next

            # Insert node at the beginning
            if p == self.head:
                newNode.next = self.head
                self.head = newNode

            # Insert node at the end
            elif p.next == None:
                p.next = newNode

            # Insert node in the middle
            else:
                newNode.next = p.next
                p.next = newNode

    def Delete(self, k):
        p = self.head

        # Find location
        while True:
            if p == None:
                break
            if p.key == k or p.next.key == k:
                break
            p = p.next
        
        # Failed
        if p == None:
            return

        # Delete node at the beginning
        elif p == self.head and p.key == k:
            self.head = self.head.next
        
        # Delete node at the end
        elif p.next.next == None and p.next.key == k:
            p.next = None
        
        # Delete node in the middle
        else:
            p.next = p.next.next