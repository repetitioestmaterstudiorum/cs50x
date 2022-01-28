from cs50 import SQL

# ---

# load data from favorites.csv file into favorites.db file:
# `sqlite3 favorites.db`
# `.mode csv`
# `.import favorites.csv favorites`

db = SQL("sqlite:///favorites.db")

def main():
    search_title = input("Title to search: ").strip()

    count = db.execute("SELECT COUNT(*) AS count FROM favorites WHERE title LIKE ?", search_title)
    print("Found items:", count[0]["count"])

    rows = db.execute("SELECT * FROM favorites WHERE title LIKE ?", search_title)
    for row in rows:
        print(row["title"], "-", row["genres"])
        print("raw data:", row)

# Title to search: avatar
# Found items: 2
# Avatar - Crime
# raw data: {'Timestamp': '10/25/2021 11:22:16', 'title': 'Avatar', 'genres': 'Crime'}
# Avatar - Crime
# raw data: {'Timestamp': '10/25/2021 11:22:17', 'title': 'Avatar', 'genres': 'Crime'}

main()