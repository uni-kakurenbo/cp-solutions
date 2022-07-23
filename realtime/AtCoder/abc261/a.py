from sys import setrecursionlimit, stderr, argv;
# setrecursionlimit(10**5)
def debug(*args, **opts):
    if argv[-1] == "LOCAL_JUDGE": print(*args, **opts, file=stderr);

l1, r1, l2, r2 = map(int, input().split())
cnt = 0;
for i in range(0, 101):
    cnt += l1 <= i < r1 and l2 <= i < r2
print(cnt)
