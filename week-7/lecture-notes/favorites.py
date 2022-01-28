import csv

# ---


titles = {}


def main():

    with open('favorites.csv', 'r') as file:
        # reader = csv.reader(file)
        # next(reader) # skip first line
        # for row in reader:
        #     print(row[1])
        reader = csv.DictReader(file)
        for row in reader:
            title = row["title"].upper().strip()
            if not title in titles:
                titles[title] = 0
            titles[title] += 1

        for title in sorted(titles, key=value_from_key, reverse=True):
            print(f"{title}: {titles[title]}")


def value_from_key(key):
    return titles[key]


main()