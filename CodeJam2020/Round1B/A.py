def solve(x, y):
    if x & 1 == y & 1:
        return 'IMPOSSIBLE'

    ans = ''
    while True:
        if x == 0 and y == 0:
            break

        if x & 1:
            if abs(x) == 1 and y == 0 or abs(x) & 2 != abs(y) & 2:
                if x < 0:
                    ans += 'W'
                    x += 1
                else:
                    ans += 'E'
                    x -= 1
            else:
                if x < 0:
                    ans += 'E'
                    x -= 1
                else:
                    ans += 'W'
                    x += 1
        else:
            if abs(y) == 1 and x == 0 or abs(x) & 2 != abs(y) & 2:
                if y < 0:
                    ans += 'S'
                    y += 1
                else:
                    ans += 'N'
                    y -= 1
            else:
                if y < 0:
                    ans += 'N'
                    y -= 1
                else:
                    ans += 'S'
                    y += 1

        x //= 2
        y //= 2

    return ans


if __name__ == '__main__':
    for tc in range(int(input())):
        print('Case #{}: {}'.format(
            tc+1,
            solve(*[int(s) for s in input().split()]),
        ))