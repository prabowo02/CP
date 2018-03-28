"""
Let b be number of blue disc, n be number of n disc
Let x = 2b-1, y = 2y-1

We can reduce this problem to find solutions (x, y) to
Qx^2 - Py^2 = Q-P

Let q*r^2 = Q, where r is the largest divisors of Q such that r^2 | Q
then the equation above can be rewritten as
(q*r x)^2 - Pqy^2 = q(Q-P)

Then we have to solve the Pell equation x^2 - Dy^2 = N, where D = Pq and N = q(Q-P)
The first step of solving Pell equation is to find all z such that z^2 = D mod N
Therefore we have to find all z such that z^2 = Pq mod q(Q-P)

Since q and Q-P are coprime, we can split into two equivalence:
x^2 = Pq (mod q) => x can only be 0 since q is squarefree
x^2 = Pq (mod Q-P) => x^2 = Pq + (Q-P)q (mod Q-P) => x^2 = Qq (mod Q-P) => x^2 = (q*r)^2 (mod Q-P)
Solving x^2 = (q*r)^2 can be done using CRT by factoring Q-P into its prime factor. Since we already know one solution to x (which is q*r), the other solution can be generated easily

After finding all such z, apply the standard PQa algorithm to solve the Pell equation

As an attempt to prevent copy-and-pasting solution, some (easy) functions are intentionally left not implemented.
"""

import decimal
import fractions
import itertools

N = 10**5 + 1
pfactors = [[] for i in range(N)]
euler = [i for i in range(N)]


# Precompute small prime factors of numbers and euler phi function
def sieve():
    for i in range(2, N):
        if not pfactors[i]:
            for j in range(i, N, i):
                pfactors[j].append(i)
                euler[j] = euler[j] // i * (i-1)


# Find prime factors of n
def find_p(n):
    if n < N:
        return pfactors[n]

    ret = []
    i = 2
    while i*i <= n:
        if n % i == 0:
            ret.append(i)
            while n % i == 0:
                n //= i
        i += 1

    if n > 1:
        ret.append(n)

    return ret


# Find euler phi function of n
def find_euler(n):
    pass


# Find largest e such that p^e | n
def find_e(n, p):
    pass


# Returns floor(sqrt(n))
def square_root(n, prec=50):
    return int(decimal.Decimal(n).sqrt(context=decimal.Context(prec=prec)).to_integral_exact(rounding=decimal.ROUND_FLOOR))


# Returns floor((p + sqrt(d)) / q)
def floor_quadratic_irrational(p, q, d):
    return int(((d + p) / q).to_integral_exact(rounding=decimal.ROUND_FLOOR))


# Returns divisors of n
def divisors(n):
    ret = [1]
    for p in find_p(n):
        prod = 1
        sz = len(ret)
        for i in range(find_e(n, p)):
            prod *= p
            for j in range(sz):
                ret.append(ret[j] * prod)
    return ret


# Returns square divisors of n (e.g. input: 36 => output: {1, 4, 9, 36})
def square_divisors(n):
    pass


# x^2 = a^2 mod m
def solve_squareroot_mod(a, m):
    if m == 1:
        return [0]

    ls = []
    primes = find_p(m)
    moduli = []
    for p in primes:
        e = find_e(m, p)
        r = p**e
        if p == 2:
            if e == 1:
                ls.append((1,))
            elif e == 2:
                ls.append((1, 3))
            else:
                ls.append((a % r, -a % r, (a + r//2) % r, (-a + r//2) % r))
        else:
            ls.append((a % r, -a % r))

        moduli.append(r)

    ret = []
    for mods in itertools.product(*ls):
        res = 0
        for i, ai in enumerate(mods):
            res += m // moduli[i] * pow(m//moduli[i], moduli[i] // primes[i] * (primes[i]-1) - 1, moduli[i]) * ai
        ret.append(res % m)
    return ret


# Returns first (x, y) s.t. x^2 - Dy^2 = N
def fundamental(p, q, D, N):
    a0 = square_root(D)
    a0_frac = decimal.Decimal(D).sqrt(context=decimal.Context(prec=200))

    P, Q, a = p, q, floor_quadratic_irrational(p, q, a0_frac)

    p0, q0, p1, q1 = 0, 1, 1, 0
    g0, g1 = -P, Q

    for i in range(100):
        p0, q0, p1, q1 = p1, q1, p0 + a*p1, q0 + a*q1
        g0, g1 = g1, g0 + a*g1

        if q1 > 2**63:
            break

        if g1**2 - D*q1**2 == N:
            return g1, q1

        P = a*Q - P
        Q = (D - P**2) // Q
        a = floor_quadratic_irrational(P, Q, a0_frac)

    return None


# Returns some solutions to x^2 - Dy^2 = 1.
def pell(D):
    a0 = square_root(D)
    a0_frac = decimal.Decimal(D).sqrt(context=decimal.Context(prec=200))

    P, Q, a = 0, 1, a0
    p0, q0, p1, q1 = 0, 1, 1, 0

    ret = [(1, 0)]
    for i in range(100):
        p0, q0, p1, q1 = p1, q1, p0 + a*p1, q0 + a*q1
        
        if q1 > 2**63:
            break

        if p1**2 - D * q1**2 == 1:
            ret.append((p1, q1))

        P = a*Q - P
        Q = (D - P**2) // Q
        a = floor_quadratic_irrational(P, Q, a0_frac)

    return ret


# Solve for D not square
def solve(p, q, minimum):
    sqQ = max(square_divisors(q))
    sfreeQ = q // sqQ
    sqQ = square_root(sqQ)
    D = p * sfreeQ

    unity = pell(D)
    
    ans = None
    def check(r, s):
        nonlocal ans
        
        for u, v in unity:
            x = abs(r*u + s*v*D)
            y = abs(r*v + s*u)
            
            if x % (q // sqQ) == 0:
                x //= q // sqQ

                if x & 1 and y & 1:
                    x, y = x + 1 >> 1, y + 1 >> 1

                    if y > minimum and (not ans or y < ans[1]):
                        ans = (x, y)

    for f2 in square_divisors(q-p):
        eulerQP = find_euler((q-p) // f2)
        sf2 = square_root(f2)
        N = sfreeQ * (q-p) // f2
        for b in solve_squareroot_mod(sfreeQ * sqQ, (q-p) // f2):
            res = sfreeQ * pow(sfreeQ, eulerQP-1, (q-p)//f2) * b % N

            if res > N // 2:
                res -= N

            fun = fundamental(res, N, D, N)            
            if not fun:
                continue

            fun = (fun[0] * sf2, fun[1] * sf2)

            check(fun[0], fun[1])

    return ans


# Solve for D square
def solve_square(p, q, minimum):
    sq = square_root(p * q)
    div1 = divisors(q)
    div2 = divisors(q-p)

    ans = None
    for d in [d1 * d2 for d1 in div1 for d2 in div2]:
        tmp = d + q*(q-p)//d
        if tmp % (2 * q):
            continue
        x = tmp // (2 * q)
        
        tmp = q*(q-p)//d - d
        if tmp % (2 * sq):
            continue
        y = tmp // (2 * sq)
        
        x, y = abs(x), abs(y)

        if x & 1 and y & 1:
            x, y = x + 1 >> 1, y + 1 >> 1
            if y > minimum and (not ans or y < ans[1]):
                ans = (x, y)

    return ans


if __name__ == '__main__':
    sieve()
    for tc in range(int(input())):
        p, q, d = [int(i) for i in input().split()]
        p, q = p // fractions.gcd(p, q), q // fractions.gcd(p, q)
        if square_root(p*q)**2 == p*q:
            ans = solve_square(p, q, d)
        else:
            ans = solve(p, q, d)

        if not ans:
            print('No solution')
        else:
            print(*ans)
