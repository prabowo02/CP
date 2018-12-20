def C(n, k):
    if n-k < k:
        k = n - k
        
    result = 1
    for i in range(k):
        result = result * (n-i) // (i+1)
        
    return result


def hofstadter_conway_10000(n):
    if n < 1:
        return None
    
    if n == 1 or n == 2:
        return 1
        
    n -= 2
        
    log_n = 1
    while 2**log_n < n:
        n -= 2**log_n
        log_n += 1
    
    if n == 2**log_n:
        return 2**log_n
    
    result = 2**(log_n - 1) + 1
    
    log_n -= 1
    
    dimension = 1
    while n > 0 and log_n > 0:
        if C(log_n + dimension, dimension) - 1 < n:
            n -= C(log_n + dimension, dimension) - 1
            result += C(log_n + dimension - 1, dimension)
            
            log_n -= 1
            dimension += 1
        
        elif C(log_n + dimension - 1, dimension - 1) < n:
            n -= C(log_n + dimension - 1, dimension - 1)
            result += C(log_n + dimension - 2, dimension - 1)
            
            log_n -= 1
            
        else:
            n -= 1
            dimension -= 1
            
    return result
        
    
def test(N=10000):
    a = [None, 1, 1]
    for i in range(3, N):
        a.append(a[a[i-1]] + a[i - a[i-1]])
    
    for i in range(1, N):
        assert hofstadter_conway_10000(i) == a[i]
    

def main():
    import argparse
    
    parser = argparse.ArgumentParser(description='Compute the Hofstadter-Conway $10,000 sequence')
    
    parser.add_argument('N', type=int, help='find the N-th value of the sequence')
    
    N = parser.parse_args().N
    
    print(hofstadter_conway_10000(N))


if __name__ == '__main__':
    main()
