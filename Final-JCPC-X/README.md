## Final Junior Competitive Programming Contest 10

This is an annual Indonesian high school programming contest held by Universitas Indonesia.
As far as I know, there is no English statement :( and no editorial.

Contest: https://tlx.toki.id/contests/tmoc-compfest-x-jcpc-final/

### A. Kocok

DP. Notice that if for each character from the string taken has even number, palindrome is possible. The same also goes when there is only one character that has odd number.
Therefore, our dp can maintain which character is currently having even number using bitmask.
This has to be solved using flying table due to small memory limit.

### B. Malam Keakraban

Let division 1 has the most member of it (if it is not, swap it). From i = 1, assign division i to odd positions (from left to right). If odd positions is full, assign to even positions (from left to right).

### C. Tabel Pak Chanek

For each query, notice that the rectangle ABCD, actually covers the integers from P_min(C, D) to P_max(A, B). Therefore each query can be answered by maintaining a prefix xor. Becareful with the case when min > max as the answer to this should be 0.

### D. Chanek Jones

I was quite surprised to see this problem appeared as it uses SCC (Strongly Connected Components) which, at this point of time, (afaik) only few Indonesian high schoolers know about this algorithm. Maybe they were taught during the coder class (?), which is part of the CPC where contestants do some practice.

Basically when box_i is opened and box_j is affected by it, add a directed edge from i to j to the graph. For each SCC, takes the box with maximum value within that component. Lastly, simply takes K largest value from the SCCs.

### E. Karakter Unik.

Maintain a BIT (Binary Indexed Tree) where the i-th index denote number of substring with unique characters ending at index i. Notice that the substring can only has length at most 26. Therefore, when doing update at index i, iterate through i-26 to find the new value of the BIT, and for each query, find the sum from range l+26..r using BIT; the rest should be evaluated carefully as the string can only start from index l.

### F. Alien vs Pak Chanek

Maintain a prefix sum, and consider all possible squares, then output the max. 
