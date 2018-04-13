## Problem

Given a simple undirected graph G = (V, E) with low number of edges (low connectivity) (say 1 ≤ |V|, |E| ≤ 64), count the number of vertex cover of graph G.

## Observations

### Simple approach

A simple solution is to consider every subset of V and check whether the set is a vertex cover or not. This approach has complexity of roughly O(|E| * 2^|V|)

### Disconnected Graph

If G is disconnected, we can consider each of its connected components, and independently count their vertex cover using the above approach. The number of vertex cover of G will be the product of each connected component's vertex cover.\
Let G_1 = (V_1, E_1), G_2 = (V_2, E_2), ..., G_k = (G_k, E_k) be the connected components of G. This approach will has complexity of around O(|E_1|\*2^|V_1| + |E_2|\*2^|V_2| + ... + |E_k|\*2^|V_k|). This might be faster than the approach from paragraph 1.

### Improved Solution

Suppose v is a vertex of G, and v belongs to a vertex cover, then the number of vertex cover of G is equivalent to the number of vertex cover of G having vertex v being cut. Similarly, if v does not belong to vertex cover, then the number of vertex cover of G is equivalent to the number of vertex cover of G having the vertex v along with its neighbours being cut. This is because all neighbours of v must belongs to a vertex cover.\
To simplify, count_vertex_cover(G) = count_vertex_cover(G \ v) + count_vertex_cover(G \ N(v)) where N(v) is closed neighbours of v including v itself.

If G became disconnected after it is cut, then we can independently compute the vertex cover of its connected components as in the explanation in 'Disconnected Graph'. Additionally, we can recursively apply the same method for every of its connected component. This method is fast enough to solve our original problem for most cases.

To further speed-up the algorithm, we have to pick a vertex such that it can disconnect the graph. One simple heuristic is to randomly pick a vertex with the highest degree.

## Example Problem

[Project Euler+ 209](https://www.hackerrank.com/contests/projecteuler/challenges/euler209)
