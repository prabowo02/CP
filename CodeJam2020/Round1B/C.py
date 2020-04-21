def solve(r, s):
    cards = [j for i in range(s) for j in range(r)]
    sorted_cards = [j for j in range(r) for i in range(s)]

    ans = []
    while cards != sorted_cards:
        i = 0
        while cards[i] == cards[0]:
            i += 1
        j = i
        while cards[j] == cards[i]:
            j += 1

        k = j
        while cards[k] != cards[0]:
            k += 1
        l = k
        while l < len(cards) and cards[l] == cards[0]:
            l += 1

        if l == len(cards):
            ans.append((i, k-i))
            cards = cards[i:k] + cards[:i] + cards[k:]
        else:
            ans.append((j, l-j))
            cards = cards[j:l] + cards[:j] + cards[l:]

    print(len(ans))
    for a, b in ans:
        print(a, b)


if __name__ == '__main__':
    for tc in range(int(input())):
        print('Case #{}: '.format(tc+1), end='')
        solve(*[int(s) for s in input().split()])
