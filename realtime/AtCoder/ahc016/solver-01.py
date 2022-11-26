from math import ceil

M, eps = input().split()

M = int(M)
eps = float(eps)

V = ceil((1 + (1 + 8*M) ** 0.5) / 2)

E = V*(V-1) // 2
assert(E >= M)

print(V)
for k in range(M):
    print("1" * k + "0" * (E - k))

for q in range(100):
    H = input()
    t = min(H.count('1'), M - 1)
    print(t)
