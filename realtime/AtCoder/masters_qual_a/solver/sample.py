N = int(input())
h = [input() for _ in range(N-1)]
v = [input() for _ in range(N)]
d = [list(map(int, input().split())) for _ in range(N)]
visited = [[False for _ in range(N)] for _ in range(N)]
dij = [(0, 1), (1, 0), (0, -1), (-1, 0)]
dir = "RDLU"
def dfs(i, j):
    visited[i][j] = True
    for d in range(4):
        di, dj = dij[d]
        i2 = i + di
        j2 = j + dj
        if 0 <= i2 < N and 0 <= j2 < N and not visited[i2][j2]:
            if di == 0 and v[i][min(j, j2)] == '0' or dj == 0 and h[min(i, i2)][j] == '0':
                print(dir[d], end='')
                dfs(i2, j2)
                print(dir[(d + 2) % 4], end='')
dfs(0, 0)
print()
