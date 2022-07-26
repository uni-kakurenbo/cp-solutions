from sys import setrecursionlimit, stderr, argv;
# setrecursionlimit(10**5)
def debug(*args, **opts):
    if argv[-1] == "LOCAL_JUDGE": print(*args, **opts, file=stderr);

a, b, c = map(int, input().split());
if c%2 == 0:
    a = abs(a)
    b = abs(b)
print("=" if a == b else "<" if a < b else ">")
