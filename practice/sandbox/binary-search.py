left = 0
right = 1001
cnt = 0  # 質問回数

while right - left > 1:
    print("(" + str(left) + ", " + str(right) + ")")
    middle = (left + right) // 2
    cnt += 1
    print(str(middle) + "以上？ (" + str(cnt) + ")")
    res = input()
    if res == "Yes":
        left = middle
    else:  # res == "No"
        right = middle

print("答え：" + str(left))
