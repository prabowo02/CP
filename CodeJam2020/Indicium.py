def swap_row(square, r1, r2):
    square[r1], square[r2] = square[r2], square[r1]


def swap_col(square, c1, c2):
    for row in square:
        row[c1], row[c2] = row[c2], row[c1]


def construct_latin3(n, a, b, c):
    mapper = dict()
    mapper[0] = a
    mapper[1] = b
    mapper[n-1] = c

    for i in range(2, n-1):
        for j in range(n):
            if j not in mapper.values():
                mapper[i] = j
                break

    res = [[mapper[(j-i)%n] + 1 for j in range(n)] for i in range(n)]
    res[0], res[1] = res[1], res[0]
    return res


def construct_latin2(n, a, b):
    square = [[(j-i) % n for j in range(n)] for i in range(n)]
    square[0], square[1] = square[1], square[0]



def solve(n, k):
    if k == n+1 or k == n*n - 1:
        return None

    if n == 3 and k % 3 != 0:
        return None

    k -= n

    if k % n == 0:
        return [[(j-i + k//n) % n + 1 for j in range(n)] for i in range(n)]

    for i in range(n):
        for j in range(n):
            if (k - i-j) % (n-2) == 0:
                if i != j:
                    return construct_latin3(n, (k-i-j) // (n-2), i, j)

    return None


if __name__ == '__main__':
    for tc in range(int(input())):
        result = solve(*[int(s) for s in input().split()])
        print('Case #{}: {}'.format(tc+1, 'POSSIBLE' if result else 'IMPOSSIBLE'))
        if result:
            for row in result:
                print(*row)
