import sys


def ask(blades):
    print(*blades)
    sys.stdout.flush()
    return [int(i) for i in input().split()]
    
    
def answer(g):
    print(g)
    sys.stdout.flush()
    return int(input())


def solve(n, ls):
    mods = [4, 3, 5, 7, 11, 13, 17]
    rems = [sum(ask([m for i in range(18)])) % m for m in mods]
    
    # prod = functools.reduce(lambda x, y: x*y, mods)
    # phis = [2, 2, 4, 6, 10, 12, 16]
    # invs = [pow(prod // m, phi-1, m) for m, phi in zip(mods, phis)]
    
    prod = 1021020
    invs = [3, 2, 4, 1, 6, 2, 16]
    
    result = answer(sum([prod//m * inv * r for r, m, inv in zip(rems, mods, invs)]) % prod)
    if result == -1:
        exit(0)


def main():
    t, n, m = input().split()
    for tc in range(int(t)):
        solve(int(n), int(m))


if __name__ == '__main__':
    main()
