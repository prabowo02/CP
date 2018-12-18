The original [problem](https://www.hackerrank.com/contests/projecteuler/challenges/euler224/problem).

While this may sound like a standard problem, the core problem lies in optimization in several parts of the code.

## Problem

Count the number of triangles with sides a, b, c, such that a^2^ + b^2^ = c^2^ - 1, and a + b + c ≤ N, for a given N.
The problem consists of Q queries, each giving another value of N.

Constraints:

- 15 ≤ N ≤ 15 * 10^8^
- 1 ≤ Q ≤ 150

## Solution

The required triangles can be generated using the same matrices as to [generate pythagorean triples](https://en.wikipedia.org/wiki/Tree_of_primitive_Pythagorean_triples):

`A = Matrix({{1, -2, 2}, {2, -1, 2}, {2, -2, 3}})`
`B = Matrix({{1, 2, 2}, {2, 1, 2}, {2, 2, 3}})`
`C = Matrix({{-1, 2, 2}, {-2, 1, 2}, {-2, 2, 3}})`

The only difference is instead of using (3, 4, 5) as the root, we use (2, 2, 3) as the root. Be careful when handling isosceles triangle, as two of its children are equivalent.

```C++
Triangles generateTriangles() {
  stack<Triangle> st;
  st.push(Triangle(2, 2, 3));
  
  // Initialize matrix A, B, and C as above
  Matrix A, B, C;
  
  while (st.size() > 0) {
    Triangle t = st.pop();
    yield t;
    
    if ((A*t).perimeter() <= N) st.push(A*t);
    if ((B*t).perimeter() <= N) st.push(B*t);
    if ((C*t).perimeter() <= N && !t.isosceles()) st.push(C*t);
  }
}
```

For simplicity, assume `yield` is C++'s equivalence of Python's generator.

```C++
for (Triangle t: generateTriangles()) {
  counters[t.perimeter()] += 1;
}
```

The answer for each query will then be the sum from `counters[1]` to `counters[N]`.

### Optimization

A few notes:

- The number of generated triangles for maximum possible N is around 83 * 10^6^. Let this number be MAXN; O(MAXN log Q) solution will not pass (for each triangle, binary search the largest query that includes this triangle). Therefore, we need the array `counters` to answer the queries.
- If we are using the array `counters`, the array has the size of N, which is too large and caused MLE.
- The triangles generated are not in increasing order of parameters.

#### Memory Optimization

To address the MLE issue, note that it is not possible to have even perimeter (i.e. all perimeters are 1 (mod 2)). Therefore, we can prune the array to store only odd perimeters. This reduces the array size by half.

Also note that the element from counters has maximum value of 40, therefore we can use data type that requires less byte (`short`) as the array counters.

Another thing to note that the number of elements which has value >= 16 is quite small. We can hardcode these values, then we only need 4 bit to store each counter. The smallest possible size of C++ data type is 1 byte `char`. Therefore, we fit two counter values in a single element, where the last 4 bits represent a counter, and the other 4 bits represent another counter. These optimization can already fit the memory limit.

#### Time Optimization

While we have satisfied the memory requirement, the timelimit is still too strict. The line that consumes most execution time is `counters[t.perimeter()] += 1`. This happens because the principle of spatial locality is not satisfies, and therefore lot of cache miss happened.

To optimize this part, we use the loop blocking technique (I don't know whether this is the correct term). Instead of directly updating the array `counters`, we temporarily store the perimeters in a 2D array, say `a[x][y]`.  For each triangle t, add `p = t.perimeter()` to the row `floor(p >> 22)`. When the row `x` is full, update the content of `a[x]` into `counters`.

### Notes

Without the loop blocking, the execution time is around 3s. After the optimization above, the time is improved to 1.9s, barely fit the time limit.

The part of the code where the optimization is done can be found in the function `inline void add(int p)` starting from line 17.

Other small optimizations, such as avoiding repeated arithmetic operations, are also done.

