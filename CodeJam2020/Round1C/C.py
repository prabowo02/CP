from fractions import Fraction


def solve(n, d, a):
    pizza = dict()
    for ang in a:
        for i in range(d):
            f = Fraction(ang, i+1)
            if f not in pizza:
                pizza[f] = []
            pizza[f].append(i+1)

    l, r, fracs = 0, len(pizza) - 1, sorted(pizza.keys())
    while l <= r:
        mid = (l + r) // 2
        if sum([ang // fracs[mid] for ang in a]) >= d:
            l = mid + 1
        else:
            r, fracs = mid - 1, fracs[:mid]

    ans = d-1
    for frac in fracs:
        cnt, cum = 0, 0
        for s in sorted(pizza[frac]):
            cnt += 1
            cum += s
            if cum > d:
                cnt -= 1
                break
        ans = min(ans, d - cnt)

    return ans


if __name__ == '__main__':
    for tc in range(int(input())):
        n, d = input().split()
        a = [int(s) for s in input().split()]
        print('Case #{}: {}'.format(tc+1, solve(int(n), int(d), a)))
