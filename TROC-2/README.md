## TOKI Regular Open Contest 2

Contest Link: https://tlx.toki.id/contests/troc-2

Problems: https://training.ia-toki.org/problemsets/118/problems/

Editorial: https://docs.google.com/document/d/196SfM9y36uGuRhPkTG5aqFZY2YX26alwAB-LV0cMj7o/edit

## My Solutions

### A

Just consider the 2 orientations, and output the max as per editorial

### B

Find smallest k > 2 such that n % k > 0, then output floor(n/k) for the first few elements, and floor(n/k)+1 for the rest.

### C

It is easier when you consider the truck as a point.
The truck has to maintain a height of at most H_i at the segment X_i to X_i + P. After that, just do line sweeping

### D

If N is small, this is a classic greedy problem (sort A ascending, and B descending, then do element-wise product)

But N is large and it is generated in a particular way. Notice that M_1 and M_2 is quite small, and we can use these to find the count of each number, by doing cycle finding.
The approach is the same as editorial

### E

Fix the number of villagers that exchage gift between A_1 and A_N, then the number of other adjacent pairs can be determined. From this, apply some combinatorics, then we can find the answer by summing all possible cases (number of pairs between A_1 and A_N). Beware of case N=2.
More details can be found from editorial, as it has the same approach.

### F

Solved during the last minute!
I brute-forced how long a person has to do action, and each of this time, there are 3 cases:
- Do not walk full circle (and stop at the minimum node along this path)
- Walk one full circle (and stop at the minimum node along the graph)
- Walk as many circle as possible (and stop at the minimum node along the graph)

Find the minimum, and output it.
