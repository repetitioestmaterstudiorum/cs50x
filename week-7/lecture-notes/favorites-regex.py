import csv
import re

# ---


def main():
    counter = 0
    with open('favorites.csv', 'r') as file:
        reader = csv.DictReader(file)
        for row in reader:
            title = row["title"].upper().strip()
            if re.search("^(OFFICE|THE.OFFICE)$", title):
                counter += 1

    print(counter)


main()