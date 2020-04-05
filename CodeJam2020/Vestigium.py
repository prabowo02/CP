def read():
    n = int(input())
    return n, [[int(s) for s in input().split()] for i in range(n)]


def solve(n, square):
    def has_duplicate(ls):
        return len(set(ls)) != len(ls)

    return sum(square[i][i] for i in range(n)), \
        sum(1 for row in square if has_duplicate(row)), \
        sum(1 for col in zip(*square) if has_duplicate(col))


if __name__ == '__main__':
    for tc in range(int(input())):
        print('Case #{}: {} {} {}'.format(tc+1, *solve(*read())))
