def read():
    n = int(input())
    return n, [[int(s) for s in input().split()] for i in range(n)]


def solve(n, activities):
    ans, covering = [-1 for i in range(n)], [False, False]
    for event in sorted([(activity[0], 1, i) for i, activity in enumerate(activities)]
            + [(activity[1], -1, i) for i, activity in enumerate(activities)]):
        _, interval_type, idx = event

        if interval_type == 1:
            if not covering[0]:
                ans[idx], covering[0] = 0, True
            elif not covering[1]:
                ans[idx], covering[1] = 1, True
            else:
                return 'IMPOSSIBLE'

        elif interval_type == -1:
            covering[ans[idx]] = False

    return ''.join('J' if cover == 0 else 'C' for cover in ans)


if __name__ == '__main__':
    for tc in range(int(input())):
        print('Case #{}: {}'.format(tc+1, solve(*read())))
