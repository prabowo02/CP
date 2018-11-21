# Given n, returns list of prime factors of n
def factorize(n):
    # This function is intentionally left blank to avoid copy-paste solution
    pass


def merge(a, b):
    return sorted(set(a + b))


def main():
    p, q = map(int, input().split())

    factors = merge(factorize(p-1), factorize(q-1))[1:]

    two = (4 if (p-1) % 4 == 0 or (q-1) % 4 == 0 else 2)

    ans = 0
    for i in range(1 << len(factors)):
        mod = two

        idxs = []
        for j in range(len(factors)):
            if i >> j & 1:
                mod *= factors[j]
                idxs.append(j)

        crts = []
        for idx in idxs:
            factor = factors[idx]
            crts.append(pow(mod // factor, factor-2, factor) * (mod // factor))

        sign = (-1 if len(idxs) % 2 else 1)

        initSum = mod // two % two * (mod // two) * (two-1)
        for j in range(1 << len(idxs)):
            first = initSum
            for k in range(len(idxs)):
                if j >> k & 1:
                    first += crts[k]
            first %= mod

            num = (p-1) * (q-1) // mod
            term = num * (num - 1) // 2 * mod + first * num

            ans += sign * term

    print(ans % 1000000007)


if __name__ == '__main__':
    main()
