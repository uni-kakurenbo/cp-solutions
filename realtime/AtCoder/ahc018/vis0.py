from itertools import product
from PIL import Image, ImageDraw

with open(".pred") as f:
    l = int(f.readline())
    val = [[*map(int, f.readline().split())] for _ in [0] * l]

mx = max(max(v for v in row) for row in val)


img = Image.new("RGB", [l, l])
draw = ImageDraw.Draw(img)

for i, j in product(range(l), range(l)):
    color = (255 * (mx - val[i][j]) // mx, 255 * (mx - val[i][j]) // mx, 255 * (mx - val[i][j]) // mx);
    # if val[i][j] < 200: color = (0, 0, 250)
    draw.point((j, i), fill = color)

img.save("./vis0.png")
