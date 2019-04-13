import random


def solve(n, m):
    ls = []
    
    def valid(p, q):
        r, c = p
        rr, cc = q
        
        if r == rr or c == cc or r+c == rr+cc or r-c == rr-cc:
            return False
              
        return True
        
    for i in range(50):
        ls = [(i, j) for j in range(m) for i in range(n)]
        cur = random.choice(ls)
        ls.remove(cur)
        
        ans = [cur]

        while len(ls) > 0:
            found = False
            for j in range(50):
                nxt = random.choice(ls)
                if valid(cur, nxt):
                    cur = nxt
                    ls.remove(cur)
                    found = True
                    ans.append(cur)
                    break
                
            if not found:
                break
                
        if len(ls) == 0:
            print('POSSIBLE')
            for i, j in ans:
                print(i+1, j+1)
            return
            
    print('IMPOSSIBLE')


def main():
    for tc in range(int(input())):
        n, m = input().split()
        print('Case #{}: '.format(tc+1), end='')
        solve(int(n), int(m))


if __name__ == '__main__':
    main()
