from collections import deque
size: int = 5

stack = deque(maxlen=size)  # Make Stack
stack.append()  # Push
stack.pop()  # Pop
stack[-1]  # Top
len(stack) == 0  # IsEmpty
len(stack) == size  # IsFull

queue = deque(maxlen=size)  # make Queue
queue.append()  # Push
queue.popleft()  # Pop
queue[0]  # head
len(queue) == 0  # IsEmpty
len(queue) == size  # IsFull