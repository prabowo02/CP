## Problem

Find all non-negative integers n < N such that 2*n^2 + 1 is prime

Constraints:

1 <= N <= 2 * 10^6

## Solution

The solution will utilize the modified sieve:
- First we initialize an array `a` with `a[n] = 2*n*n + 1`.
- Iterate from i=1 to N:
  - If a[i] = 1, then continue to the next i
  - Otherwise, a[i] is prime. If a[i] == 2*i*i + 1 (a[i] has never been modified before), push i as one of our answers
  - Suppose p = a[i]. For all j = +/- i (mod p), divide a[j] with p until coprime.
  

### Proof

We first find the relation between a[n], a[m], and p.

Suppose p > 2, p | n*n + 1 and p | m*m + 1, then

2*n*n + 1 = 2*m*m + 1 (mod p)
2*n*n - 2*m*m = 0 (mod p)
2(n + m)(n - m) = 0 (mod p)

n = m (mod p) or n = -m (mod p) ... (1)

We are to prove that by the time we iterate i, a[i] is either 1 or prime using induction.

Base case: When n = 1, a[n] is already prime from initial.

Assume that for i < n, a[i] is either 1 or prime.

If a[n] = 1, then we are done.

Suppose prime p | a[n].
- Case p = 2: Impossible because 2*n^2 + 1 = 1 (mod p)
- Case p < n: We know that n - p >= 1, from (1) p | a[j] for j < n and j = n (mod p). By our assumption, there exist j such that a[j] is prime (when we are iterating i = j), therefore a[n] had its prime divided out already. Hence it is not possible p < n
- Case p = n: Impossible because 2*n^2 + 1 = 1 (mod p)
- Case n < p < 2n: This case is similar to case p < n. We know that 0 < p - n < n, from (1) p | a[j] for j < n and j = -n (mod p). By our assumption, there exists j such that a[j] is prime (when we are iterating i = j), therefore a[n] had its prime divided out already. Hence it is not possible n < p < 2n.
- Case p >= 2n: If a[n] is prime then we are done. Otherwise, a[n] can be written as p*q, where p, q >= 2n. But 4n^2 > 2*n^2 + 1. Therefore a[n] is prime.

### Notes

The above method also works for other quadratic formula, but with a few changes.

For example:
- f(n) = n^2 + 1. The above algorithm works without major changes.
- f(n) = 2*n^2 - 1. Start iterating from i = 2, instead from i = 1.
- f(n) = n^2 - n + 1. The relation from (1) is changed to n = m (mod p) or n = -m+1 (mod p), therefore the "divide until coprime" part has different j.
- f(n) = n^2 - 2. Start iterating from i = 2.
- f(n) = n^2 + 5. Manually divide all a[i] with 2 and 3 (so that our base case holds) before running the algorithm.
- f(n) = n^2 - 4. Except for n = 3, n^2 - 4 will never be prime because n^2 - 4 = (n+2)(n-2). In general, you will find either one or zero prime when b^2 - 4ac is a square, where an^2 + bn + c is our formula.
- f(n) = n^2 - 6. Things start to get complicated with negative values. Either handle the negative values carefully (by using abs(a[i])) or "left-shift" the function to (n + 2)^2 - 6 and adjust all the parameters (including N) accordingly.

The time complexity is the same as the standard sieve of Eratosthenes: O(N log log N)

## A More General Solution

The core idea is to combine the squareroot primality checking and the sieve idea from above.

Suppose f(n) = an^2 + bn + c, and a is not large (around 2). Like before, initialize a[n] = f(n). Note that the maximum value of f(n) for n = 1..N is around N^2

Using sieve, repeatedly generate a prime p.
We want to satisfy the equivalence an^2 + bn + c = 0 (mod p). Let D = b^2 - 4ac, completing the square, we obtain n = (-b +/- sqrt(D)) * (2a)^(-1) (mod p). After obtaining the values of n, for all j = n (mod p), if a[j] = p, then a[j] is prime, otherwise a[j] is not a prime. Also mark visited[j] = true

After completing the sieve, all values that has not been visited by j (i.e. visited[j] = false), then a[j] is prime, because it is not divided by any prime <= sqrt(a[j])

To find the value of sqrt(D) (mod p), use the tonelli-shanks algorithm, which runs in O(log^2 N). Since the order of prime number up to N is O(N / log N), then the overall time complexity is O(N log N).

Example Problems:
- [Project Euler+ #221](https://www.hackerrank.com/contests/projecteuler/challenges/euler221)
- [Project Euler+ #131](https://www.hackerrank.com/contests/projecteuler/challenges/euler131)
- [Project Euler+ #216](https://www.hackerrank.com/contests/projecteuler/challenges/euler216) This one must use the solution from "A More General Solution" (in fact, they are similar problem).

```C++
for (int i=1; i<N; i++) {
  a[i] = i*i + 1;
  isPrime[i] = false;
}

for (int i=1; i<N; i++) {
  if (a[i] == 1) continue;
  if (a[i] == i*i + 1) isPrime[i] = true;
  
  int p = a[i];
  
  for (int j=i; j<=N; j+=i) do {
    a[j] /= p;
  } while (a[j] % p == 0);
  
  for (int j=p-i; j<=N; j+=i) do {
    a[j] /= p;
  } while (a[j] % p == 0);
}
```

