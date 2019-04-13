from math import gcd
from string import ascii_uppercase


def solve(cipher):
    primes = [None for i in range(len(cipher) + 1)]

    for i in range(1, len(cipher)):
        if cipher[i] != cipher[i-1]:
            primes[i] = gcd(cipher[i], cipher[i-1])
            break
    
    for j in range(i)[::-1]:
        primes[j] = cipher[j] // primes[j+1]
    
    for j in range(i+1, len(cipher) + 1):
        primes[j] = cipher[j-1] // primes[j-1]

    prime_to_char = {p: c for p, c in zip(sorted(set(primes)), ascii_uppercase)}
    return ''.join([prime_to_char[p] for p in primes])


def main():
    from sys import stdin
    lines = stdin.readlines()
    
    for tc in range(int(lines[0])):
        print('Case #{}: {}'.format(tc+1, solve([int(i) for i in lines[tc*2 + 2].split()])))


if __name__ == '__main__':
    main()
