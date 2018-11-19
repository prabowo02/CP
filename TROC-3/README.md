## TOKI Regular Open Contest 3

Contest Link: https://tlx.toki.id/contests/troc-3
Problems: https://training.ia-toki.org/problemsets/145/problems/
Editorial: https://docs.google.com/document/d/1IubDd1DEveZABVmawgmH6zGjbJ5La3DZgkZof3xxxKQ/edit?usp=sharing

## My Solutions

### A

Same as editorial, but instead of directly compute floor(X / (A+B+C)), I iterate from 0 instead because of the small constraints.
http://codeforces.com/blog/entry/20304

### B

Let `s` be the number of `i` such that `a[i] == a[i+1]`.
Three cases:
- `s > 1` ==> answer is 0
- `s = 1` ==> answer is 1
- `s = 0` ==> answer is n+1

### C

For every i, greedily takes the largest number (which has not been taken before) that is congruent to A_i (mod M). If such number no longer available, output -1.

### D

Same as editorial, notice that x ^ x = 0 (^ means XOR operation), ^ is associative, ^ is commutative, and (A_1 ^ B_1) ^ (A_x ^ B_1) ^ (A_1 ^ B_y) = (A_x ^ B_y). Therefore, just ask for the value of (A_1 ^ B_y) for all y, and (A_x ^ B_1) for all x, then use those values to find the queried matrix.

### E

3 states DP. Notice that when a piece is at location (i, j), every time it moves, will increase the value of i+j by 1. This i+j "diagonal" will be the first state of the DP. The other two states are the positions of the pieces on this diagonal.

### F

Not solved this during contest time.

We create a 100x100 matrix that denotes the count transition when doing one hopping from building with height j to building with height i. Lets call this matrix A.
Precompute A^1, ..., A^20, where ^ denotes the power operation.
For each query, create a 0s vector, and set the value at h[x] position to 1. Multiply this vector with the corresponding matrix (O(N^2) for each matrix), then the rest is trivial.
