import re

def solve(inpts: list) -> int:
    result = 0
    pattern = r"mul\(\d+,\d+\)|do\(\)|don\'t\(\)"
    x = []
    for txt in inpts:
        x += re.findall(pattern, txt)

    do = "do()"
    dont = "don't()"
    enabled = True
    for operation in x:
        if enabled:
            if operation != do and operation != dont:
                tmp = operation.split(',')
                a = int(tmp[0].split('(')[1])
                b = int(tmp[1].split(')')[0])
                result += (a * b)
            
            if operation == dont:
                enabled = False
        else:
            if operation == do:
                enabled = True

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