import csv

# ---


titles = {}


def main():

    with open('favorites.csv', 'r') as file:
        reader = csv.DictReader(file)
        for row in reader:
            title = row["title"].upper().strip()
            if not title in titles:
                titles[title] = 0
            titles[title] += 1

        for title in sorted(titles, key=lambda arg: titles[arg], reverse=True):
            print(f"{title}: {titles[title]}")


main()