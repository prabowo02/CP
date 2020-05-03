def solve(x, y, m):
    for i, c in enumerate(m):
        if c == 'N':
            y += 1
        elif c == 'S':
            y -= 1
        elif c == 'E':
            x += 1
        elif c == 'W':
            x -= 1

        if abs(x) + abs(y) <= i+1:
            return i+1

    return 'IMPOSSIBLE'



if __name__ == '__main__':
    for tc in range(int(input())):
        x, y, m = input().split()
        print('Case #{}: {}'.format(tc+1, solve(int(x), int(y), m)))
