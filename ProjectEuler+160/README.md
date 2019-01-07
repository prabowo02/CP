The original [problem](https://www.hackerrank.com/contests/projecteuler/challenges/euler160/problem)

## Problem

Find the five digits before the trailing zeroes in N! written in base b

Contraints:
- 0 ≤ N ≤ 10^18
- 2 ≤ b ≤ 36

## Solution

Let N! = a * b^k, where b does not divide a. Then we are actually trying to find N! / b^k (mod b^5). We will use CRT to find such number.

Write b^5 as the product of p_i^e_i, for different primes p_i. Now we are to find N! / b^k (mod p_i^e_i) for all i, then combine the answers with CRT.

To find N! / b^k (mod p_i^e_i), find largest integer x such that p_i^x | N! (it can be found using Legendre's formula), then write N! / b^k = N! / (p_i^x * c^k) * p_i^(x - e_i*k), where c is the value of b without the prime factor p_i. Since c and p_i are coprime, the inverse can be found easily. 

The problem is now to find N! / (p_i^x). It can be shown that N! / (p_i^x) can be written as (p_i - 1)^x * n_0! * n_1! * ... , for some integer u, and n_j non negative integer ≤ p_i - 1 for all j. The values of n_j can be found while evaluating x using Legendre's formula (n_j = floor(N / p_i^j) % p_i, where % is modulo operation).

Now that all the values can be computed using standard modulo operation, the rest is trivial.
