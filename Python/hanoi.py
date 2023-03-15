def hanoi(num, a, b, c):
    if num == 1:
        print(a, c)
    else:
        hanoi(num-1, a, c, b)
        print(a, c)
        hanoi(num-1, b, a, c)
    
n = int(input())
print(2**n - 1)
if n <= 20:
    hanoi(n, 1, 2, 3)