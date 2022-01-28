def main():
    height = get_height()

    hashes = 1
    blanks = height - 1
    for i in range(height):
        # left side
        print_space(blanks)
        print_hashes(hashes)
        # separator
        print_space(2)
        # right side
        print_hashes(hashes)
        # new line
        print()
        # update variables
        blanks -= 1
        hashes += 1


def get_height():
    while True:
        try: 
            height = int(input("Height: "))
            if height > 0 and height < 9:
                break
        except:
            print("That is not a number")
            continue
    return height


def print_space(n):
    print_smth(n, ' ')


def print_hashes(n):
    print_smth(n, '#')


def print_smth(n, smth):
    print(smth * n, end='')


main()

# python mario.py
# check50 cs50/problems/2022/x/sentimental/mario/more
# submit50 cs50/problems/2022/x/sentimental/mario/more