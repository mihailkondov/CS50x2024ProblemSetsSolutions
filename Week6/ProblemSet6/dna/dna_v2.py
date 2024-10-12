# This program reads a frequency table of Short Tandem Repeats (STR) of multiple people
# that looks something like this:
#
# name      AGAT    AATG    TATC
# Alice     28      42      14
# Bob       17      22      19
# Charlie   36      18      25
#
# Then the program reads a genome from a txt file that looks something like this:
# AACTTGATGTATTTGCTGCACTCCAG
# and counts the STR for the given genome
# and tries to identify the person to whom it belongs by comparing with the data from the
# table. In the end the program prints the found person's name or "No match"
#
# Usage: python dna.py databases/large.csv sequences/5.txt

import csv
import sys


def main():

    # Check for proper usage
    if len(sys.argv) != 3:
        print("Usage: ./dna database.csv DNA_sequence.txt")
        return

    # Read database file into a dictionary
    with open(file=sys.argv[1]) as data_file:
        reader = csv.DictReader(data_file)
        database = {}
        for row in reader:
            name = row['name']
            database[name] = {str_name: int(row[str_name])
                              for str_name in row if str_name != 'name'}

    # Extract the list of STR names
    str_list = list(database[next(iter(database))].keys())

    # Read DNA sequence file into a variable
    with open(file=sys.argv[2]) as sequence_file:
        sequence = sequence_file.readline().strip()

    # Find longest match of each STR in DNA sequence
    str_counts = {}
    for current_str in str_list:
        str_counts[current_str] = longest_match(sequence, current_str)

    # Check database for matching profiles
    result = "No match"
    for person, str_data in database.items():
        if all(str_counts[str_name] == str_data[str_name] for str_name in str_list):
            result = person
            break

    # Print result
    print(result)


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
