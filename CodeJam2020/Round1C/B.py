from collections import Counter


def solve(U, Q, M):
    counter, alpha = Counter(), set()
    for m in M:
        counter.update([m[0]])
        alpha.update(m)

    alpha.difference_update(set(counter))
    return alpha.pop() + ''.join([c[0] for c in counter.most_common()])


if __name__ == '__main__':
    for tc in range(int(input())):
        ans = solve(int(input()), *zip(*[input().split() for line in range(10000)]))
        print('Case #{}: {}'.format(tc+1, ans))
