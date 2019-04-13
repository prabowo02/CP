import random


def solve(n, ls):
    trie = [[None for i in range(26)]]
    val = [0]
    
    def chr_to_idx(c):
        return ord(c) - ord('A')
    
    def insert(s):
        cur = 0
        for c in s:
            idx = chr_to_idx(c)
            if trie[cur][idx] is not None:
                cur = trie[cur][idx]
            else:
                trie[cur][idx] = len(trie)
                trie.append([None for i in range(26)])
                val.append(0)
                cur = trie[cur][idx]

            val[cur] += 1
    
    def count(u):
        if val[u] <= 1:
            return 0

        ret = 0
        for i in range(26):
            if trie[u][i] is not None:
                ret += count(trie[u][i])
                
        return ret + (2 if val[u] - ret >= 2 else 0)
        
    
    for s in ls:
        insert(s[::-1])
        
    ans = 0
    for i in range(26):
        if trie[0][i] is not None:
            ans += count(trie[0][i])
            
    print(ans)
        


def main():
    for tc in range(int(input())):
        n = int(input())
        s = [input() for i in range(n)]
        print('Case #{}: '.format(tc+1), end='')
        solve(n, s)


if __name__ == '__main__':
    main()
