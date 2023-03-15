def hanoi(num, a, b, c):
    if num == 1:
        print(f"{a} -> {c}")
    else:
        hanoi(num-1, a, c, b)
        print(f"{a} -> {c}")
        hanoi(num-1, b, a, c)
    
n = int(input())
print(f"function called : {2**n - 1} times")
hanoi(n, 1, 2, 3)