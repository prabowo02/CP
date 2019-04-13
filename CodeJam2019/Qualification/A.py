def solve(N):
    A, B = zip(*[('0', c) if c != '4' else ('1', '3') for c in N])
    A, B = int(''.join(A)), int(''.join(B))
    return '{} {}'.format(A, B)


def main():
    for tc in range(int(input())):
        print('Case #{}: {}'.format(tc+1, solve(input())))


if __name__ == '__main__':
    main()
