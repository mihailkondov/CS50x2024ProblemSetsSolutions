import csv

# print the csv file
print("Here are two columns from the csv-file:\n")
with open("favorites.csv") as file:
    reader = csv.reader(file)

    for row in reader:
        print(row[0]+"\t"+row[1])


# now let's count the number of occurances of each language
with open('favorites.csv') as file:
    reader = csv.DictReader(file)
    count = {}

    for row in reader:
        fav = row["favorite"]
        if fav in count:
            count[fav] += 1
        else:
            count[fav] = 1

# print the result of the counting
print()
print("Language:\tNumber of people who like it most")
for language in count:
    print(str(language) + "\t\t" + str(count[language]))

# same, but now sorted by key
print()
print("Language:\tNumber of people who like it most, sorted alphabetically")
for language in sorted(count): #sorts by keys alphabetically
    print(str(language) + "\t\t" + str(count[language]))

# same, but now sorted by VALUE
print()
print("Language:\tNumber of people who like it most, sorted by value")
for language in sorted(count, key=count.get): # sorts by value
    print(str(language) + "\t\t" + str(count[language]))

# same, but now sorted by VALUE DESCENDING
print()
print("Language:\tNumber of people who like it most, sorted by value")
for language in sorted(count, key=count.get, reverse = True): # sorts by value
    print(str(language) + "\t\t" + str(count[language]))
