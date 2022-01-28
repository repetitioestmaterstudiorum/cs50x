import csv

# ---


def main():
    search_title = input("Title to search: ").strip().lower()

    counter = 0

    with open('favorites.csv', 'r') as file:
        reader = csv.DictReader(file)
        for row in reader:
            title = row["title"].lower().strip()
            if title == search_title:
                counter += 1
    
    print(counter)


main()