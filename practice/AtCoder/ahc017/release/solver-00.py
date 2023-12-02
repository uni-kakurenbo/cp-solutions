from random import randint


n, m, d, k = map(int, input().split())

print(*(randint(1, d) for _ in range(m)))
