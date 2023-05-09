def balance(s):
    opening = '{(['
    closing = '}])'
    matching = {'}' : '{', ')': '(', ']' : '['}
    stack = []
    for c in s:
        if c in opening:
            stack.append(c)
        elif c in closing:
            if not stack:
                stack.append(c)
            elif stack[-1] == matching[c]:
                stack.pop()
            else: stack.append(c)
    return (len(stack)==0)

print(balance('([a])[b]({})'))
print(balance('([)]))'))
print(balance('(([])'))
print(balance('([]))'))
print(balance('([{}])'))
print(balance('([()])'))