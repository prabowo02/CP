def solve(s):
    res, depth = '', 0
    for c in s:
        c = int(c)

        if depth < c:
            res += '(' * (c - depth)
        elif depth > c:
            res += ')' * (depth - c)
        
        depth = c
        res += str(c)

    return res + ')' * depth


if __name__ == '__main__':
    for tc in range(int(input())):
        print('Case #{}: {}'.format(tc+1, solve(input())))
