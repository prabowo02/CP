The original [problem](https://www.hackerrank.com/contests/projecteuler/challenges/euler182) statement

## Problem

Given p, q distinct odd primes, find the sum of all e such that gcd(e, (p-1)(q-1)) = 1 and the number of m in [0, pq-1] satisfy the equivalence m^e = m (mod pq) is minimum.

Constraints:
- 11 < p, q ≤ 10^9

## Solution

[Number of RSA fixed point](https://math.stackexchange.com/questions/1298664/rsa-fixed-point) (including m = 0) is (1 + gcd(e-1, p-1))(1 + gcd(e-1, q-1)). To minimize the number of unconcealed messages, gcd(e-1, p-1) and gcd(e-1, q-1) must be minimized. Since p and q are odd primes and gcd(e, (p-1)(q-1)) = 1 => gcd(e, (p-1)) = gcd(e, (q-1)) = 1, gcd(e-1, p-1) must not be 1 because 2 | p-1 and 2 | e-1. In fact, the least possible value of gcd(e-1, p-1) is 2.

### Lemma 1: When p odd prime and gcd(e, p-1) = 1, then gcd(e-1, p-1) = 2 always exists.

Factorize p-1 = 2^{a_0} * p_1^{a_1) * ... * p_k^{a_k}

Because gcd(e, p-1) = 1, by CRT: e != 0 (mod p_i^{a_i}) => e != 0 (mod p_i), for all i. Since p_i > 2, there exists e such that e-1 != 0 (mod p_i) for all i.
When a_0 = 1, taking e = 1 (mod 2) is enough to make gcd(e-1, p-1) = 2, but when a_0 > 1, it is necessary to use e = 3 (mod 4).

### Main Solution

From the prove of lemma 1, it can be seen that our e must not satisfy e = 0 (mod p_i) and e = 1 (mod p_i) where p_i is the odd prime factors of p-1 or q-1.
It is also important to note that e must satisfy e = 3 (mod 4) if 4 | p-1 or 4 | q-1, otherwise e = 1 (mod 2).

First, factorize (p-1) and (q-1) into their prime factors, then merge those prime factors. To find the sum of all such e, we do inclusion-exclusion on the prime factors, and for each subset of prime factors, use CRT to find the number of e such that e != 0 (mod p_i) and e != 1 (mod p_i) for each p_i the odd prime factors from the subset. To find the sum of all e that satisfy those equivalences, CRT is applied for every 2^n possibilities where n is the number of odd prime factors on the subset. 

The whole inclusion-exclusion will take around O(N * 3^N) time complexity where N is the number of distinct odd prime factors of (p-1)(q-1). Theoretically, this N can goes up to 14, but since p and q are not arbitrary integers, the N is actually quiet small.
