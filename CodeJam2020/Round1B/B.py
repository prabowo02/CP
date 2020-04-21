import sys


MAXC = 10**9
CENTER, HIT, MISS = 'CENTER', 'HIT', 'MISS'


memo = dict()
found_center = False
def ask(x, y):
    global found_center
    if (x, y) in memo:
        return memo[(x, y)]
    if found_center:
        return MISS

    print(x, y)
    sys.stdout.flush()
    ans = input()
    if ans == CENTER:
        found_center = True

    memo[(x, y)] = ans
    return ans


def search(l, r, check):
    ret = l
    while l <= r:
        mid = (l + r) // 2
        if check(mid):
            ret = mid
            l = mid + 1
        else:
            r = mid - 1

    return ret


def solve():
    global found_center
    memo.clear()
    found_center = False

    M = MAXC // 2
    for x, y in [(0, 0), (M, M), (M, -M), (-M, M), (-M, -M)]:
        if ask(x, y) != MISS:
            x1 = search(-MAXC, x, lambda x: ask(x, y) == MISS)
            x2 = search(x, MAXC, lambda x: ask(x, y) != MISS)
            y1 = search(-MAXC, y, lambda y: ask(x, y) == MISS)
            y2 = search(y, MAXC, lambda y: ask(x, y) != MISS)
            ask((x1 + x2 + 1) // 2, (y1 + y2 + 1) // 2)
            return


if __name__ == '__main__':
    t, a, b = [int(s) for s in input().split()]
    for tc in range(t):
        solve()
