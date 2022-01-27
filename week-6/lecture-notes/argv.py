from sys import argv

# ---

if len(argv) == 2:
    print(f"hello, {argv[1]}")
else:
    print("hello, world")

# python argv.py thomas -> hello, thomas
# python argv.py -> hello, world