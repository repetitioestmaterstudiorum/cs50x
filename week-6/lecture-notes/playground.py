from cs50 import get_float, get_int, get_string
# or `import cs50` and then `cs50.get_int` etc.

# ---

words = dict()
print(words)
# words.add('hi') // doesn't exist

words = set()
print(words)
words.add('hi')
print(words)

# input instead of get_string
name = input("your name: ")
print(f"so your name is really {name}? cool")

# cs50 functions
f = get_float("Input a floating-point number: ")
i = get_int("Input an integer: ")
s = get_string("Input a string: ")

print(f"f: {f}, i: {i}, s: {s}")
