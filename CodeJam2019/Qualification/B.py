def solve(s):
    return ''.join(['S' if c == 'E' else 'E' for c in s])


def main():
    from sys import stdin
    lines = stdin.readlines()
    
    for tc in range(int(lines[0])):
        print('Case #{}: {}'.format(tc+1, solve(lines[tc*2 + 2].strip())))


if __name__ == '__main__':
    main()
