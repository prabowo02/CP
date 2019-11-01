The original [problem](https://www.hackerrank.com/contests/projecteuler/challenges/euler238/problem).

This problem may sounds classical to some people, but it requires some rare topics such as multipoint evaluation and generating function, so I decided to share the analysis to this problem.

## Problem

Given a periodic sequence P of size N and has a period of 89060.
Find the value of sum_{k=1}^N P(k)^e modulo 1004535809.

Constraints:

- 1 ≤ N ≤ 10^18
- 1 ≤ e ≤ 10^5
- 0 ≤ P(k) ≤ 50

## Solution

For simplicity, we assume 89060 \| N, and N > 89060. (If they are not, then compute the remaining parts as usual).

We can break the summation to 89060 parts: sum P(89060\*k + x) for x = 0 .. 89060-1.

Suppose S_k(n) = 1^k + 2^k + ... + n^k, then we are left to compute P(x) \* sum_k (89060k + x)^e = P(x) \* sum_k (S_0(n) 89060^0 * C(e, 0) x^0 + S_{1}(n) 89060^1 C(e, 1) x^1 + ... + S_e(n) 89060^e C(e, e) x^e), where n = N / 89060

### Computing the k-th power of the first n positive integers

Our first challenge is: Given n and k, compute S_0(n), S_1(n), ..., S_k(n).

Consider the series expansion of e^x = sum_k x^k / k!

e^0 + e^(x) + e^(2x) + ... + e^(nx) = sum_k S_k(n) x^k / k!

((e^((n+1)x)) - 1) / (e^x - 1) = sum_k S_k(n) x^k / k!

Therefore, we can compute the value of S by finding the series ((e^((n+1)x)) - 1) / (e^x - 1) = ( (e^((n+1)x) - 1) / x ) \* ( (e^x - 1) / x )^-1 (for a polynomial to have an inverse, its constant must be non-zero).

The computation of an inverse can be done iteratively:
Suppose Q(x) = P(x)^-1, and P_n(x) = P(x) (mod x^n) (the first n terms of P(x)) then

Q_2n(x) = 2Q_n(x) - P_{2n}(x) Q_n(x)^2

with Q_0(x) = P_0(x)^-1 is computed using modular inverse as usual.

The overall complexity of computing inverse is O(N log N) using NTT.

In general, the computation for function of polynomial can be done using [Newton's method](https://en.wikipedia.org/wiki/Newton%27s_method) by letting x be the polynomial to be found (e.g. for inverse, f(Q) = P - Q^-1).

### Multipoint Evaluation

Now that we have obtained the values of S_k(n), we are left with the polynomial Q(x) = P(x) \* sum_k a_k x^k, with a_k = S_k(n) 89060^k C(e, k). Computing Q(0) + Q(1) + ... + Q(89060-1) by multipoint evaluation on P(0), ..., P(89060-1) will give us the answer.

The idea of multipoint evaluation is that P(x_i) is computed using P mod (x - x_i). Therefore, given points x_1, x_2, ... x_n, we compute P mod (x - x_1)(x - x_2)...(x - x_mid) and P mod (x - x_{mid+1})...(x - x_n) then proceed recursively. Of course, we need to compute the value of prod(x - x_i) beforehand in another (possibly another recursive) function.

The computation of D(x) = P(x) mod Q(x) can be done as: D^r(x) = A^r(x) (B^r(x))^-1 (mod x^(n-m+1)) where P^r(x) is polynomial having its coefficients reversed.

The complexity of computing modulo is O(N log N), and therefore the complexity of multipoint evaluation is O(N log^2 N).

## References

[Codeforces: Counting sums of powers](https://codeforces.com/blog/entry/60756)
[Codeforces: Operations on Formal Power Series](https://codeforces.com/blog/entry/56422)
[Moscow Workshop 2017: On Fast Fourier Transform](https://drive.google.com/file/d/1B9BIfATnI_qL6rYiE5hY9bh20SMVmHZ7/view)
