import csv

from collections import Counter

with open("favorites.csv", "r") as file:
    reader = csv.DictReader(file)
    count = Counter()

    for row in reader:
        favorite = row["favorite"]
        count[favorite] += 1

for language, c in count.most_common():
    print(f"{language}\t\t{count[language]}")
