import csv

from collections import Counter

with open("favorites.csv", "r") as file:
    reader = csv.DictReader(file)
    count = Counter()

    for row in reader:
        favorite = row["favorite"]
        count[favorite] += 1

language = input("Enter language: ")
print(f"Favorite language {language}: {count[language]}")
