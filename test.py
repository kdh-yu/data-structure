arr = [1,2,3,4]

def Partition(L, low, high):
  pivot = L[high]
  l = low
  r = high
  while l < r:
    while L[l] > pivot:
      l += 1
    while L[r] <= pivot:
      r -= 1
    if l < r:
      L[l], L[r] = L[r], L[l]
  L[r], L[high] = L[high], L[r]
  return r

print(arr)
p = Partition(arr, 0, 2)
print(arr)