from sys import stdout
from sys import stderr


def test_store(s):
    print(s)
    stdout.flush()
    return input()
    
    
def answer(bs):
    print(*bs)
    stdout.flush()
    return input()


def solve(n, b, f):
    queries = [''.join(t) for t in zip(*['{:05b}'.format(i % 32) for i in range(n)])]
    nums = [int(''.join(t), 2) for t in zip(*[test_store(s) for s in queries])]
    
    cur = 0
    ans = []
    for i, num in enumerate(nums):
        while cur % 32 != num:
            ans.append(cur)
            cur += 1
            
        cur += 1
    
    while len(ans) < b:
        ans.append(cur)
        cur += 1

    answer(ans)


def main():
    for tc in range(int(input())):
        n, b, f = input().split()
        solve(int(n), int(b), int(f))


if __name__ == '__main__':
    main()
