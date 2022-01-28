from cs50 import get_float

# ---

clg_on = False


def main():
    # print minimum amount of coins needed to repay debt
    # only coins available: quarters (25¢), dimes (10¢), nickels (5¢), and pennies (1¢)
    dollars_owed = get_owed_dollars()
    coins = 0
    while (dollars_owed >= .25):
        clg('0.25')
        dollars_owed = subtract_and_round(dollars_owed, .25)
        coins += 1
    while (dollars_owed >= .1):
        clg('0.1')
        dollars_owed = subtract_and_round(dollars_owed, .1)
        coins += 1
    while (dollars_owed >= .05):
        clg('0.05')
        dollars_owed = subtract_and_round(dollars_owed, .05)
        coins += 1
    while (dollars_owed >= .01):
        clg('0.01')
        dollars_owed = subtract_and_round(dollars_owed, .01)
        coins += 1
    print(coins)


def get_owed_dollars():
    while True:
        dollars_owed = get_float("Change owed: ")
        if dollars_owed > 0:
            break
    return dollars_owed


def subtract_and_round(init_v, subtract):
    return round(init_v - subtract, 2)


def clg(str):
    if clg_on:
        print(str)


main()

# check50 cs50/problems/2022/x/sentimental/cash
# submit50 cs50/problems/2022/x/sentimental/cash