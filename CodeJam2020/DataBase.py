import sys


def ask(i):
    print(i+1)
    sys.stdout.flush()
    return int(input())


def solve(b):
    complement, reversal = False, False

    ans = [-1 for i in range(b)]
    same, diff = -1, -1

    def get(x):
        if complement and reversal:
            return ans[b-x-1] ^ 1
        if complement:
            return ans[x] ^ 1
        if reversal:
            return ans[b-x-1]
        return ans[x]

    l, r = 0, b-1
    query_num = 0
    while l <= r:
        x, y = ask(l), ask(r)
        if reversal:
            x, y = y, x
        if complement:
            x, y = x^1, y^1

        if x == y:
            same = l
        else:
            diff = l

        ans[l], ans[r] = x, y
        l, r = l+1, r-1

        query_num += 2
        if query_num % 10 == 0:
            has_complement, has_reversal = False, False
            if same != -1 and diff != -1:
                x, y = ask(same), ask(diff)

                has_complement = (get(same) != x)
                has_reversal = (get(diff) != y) ^ has_complement
            elif same != -1:
                x = ask(same)
                ask(same) # Dummy, for easier implementation

                has_complement = (get(same) != x)
            elif diff != -1:
                x = ask(diff)
                ask(diff) # Dummy, for easier implementation

                has_complement = (get(diff) != x)

            if has_complement:
                complement = not complement
            if has_reversal:
                reversal = not reversal

            query_num += 2

    return ''.join([str(get(i)) for i in range(b)])


if __name__ == '__main__':
    t, b = [int(s) for s in input().split()]
    for tc in range(t):
        print(solve(b))
        sys.stdout.flush()
        input() # Read the verdict
