import sys


def ask(d):
    print(d)
    sys.stdout.flush()
    return int(input())


def solve():
    ls = [0 for i in range(6+1)]
    
    ring = ask(200)
    ls[6] = (ring >> 33) % 128
    ls[5] = (ring >> 40) % 128
    ls[4] = (ring >> 50) % 128
    
    ring = ask(50)
    ring -= ls[6] * (1 << 8) + ls[5] * (1 << 10) + ls[4] * (1 << 12)
    ls[3] = (ring >> 16) % 128
    ls[2] = (ring >> 25) % 128
    ls[1] = (ring >> 50) % 128
    
    print(*ls[1:])
    sys.stdout.flush()
    return int(input())


def main():
    tc, w = input().split()
    for i in range(int(tc)):
        solve()
    
if __name__ == '__main__':
    main()
