import re

def solve(inpts: list) -> int:
    result = 0
    pattern = r"mul\(\d+,\d+\)"
    x = []
    for txt in inpts:
        x += re.findall(pattern, txt)


    for mul in x:
        tmp = mul.split(',')
        a = int(tmp[0].split('(')[1])
        b = int(tmp[1].split(')')[0])

        result += a * b
    
    print(len(x))
    return result


def main():
    inpts = []
    while True:
        txt = input()
        if txt == "":
            break
        inpts.append(txt)
    
    print(solve(inpts))


if __name__ == '__main__':
    main()