input = open("1_input.txt", "r")

max = -1
current = 0
for x in input:
    if x == "\n":
        print(current)
        if current > max:
            max = current
        current = 0
        continue
    current += int(x)

print(max)
