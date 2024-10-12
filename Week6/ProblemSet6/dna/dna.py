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

# TODO: currentry the program works with lists of lists, but it might be nicer to make it
# work with a dictionary of dictionaries instead.

import csv
import sys


def main():

    if len(sys.argv) != 3:
        print("Usage: ./dna database.csv DNA_sequence.txt")

    # Read database file into a variable
    with open(file=sys.argv[1]) as data:
        reader = csv.reader(data)
        database = []
        for row in reader:
            database.append(row)  # this is a list of lists

    str_list = database[0][1:]  # a list of all STR-s

    # Read DNA sequence file into a variable
    with open(file=sys.argv[2]) as sequence:
        sequence = sequence.readline()  # a simple string

    # Find longest match of each STR in DNA sequence
    str_gene = []
    for current_str in str_list:
        str_gene.append(longest_match(sequence, current_str))

    # Check database for matching profiles
    result = "No match"
    for person in database[1:]:
        matches = 0
        for i in range(len(person[1:])):
            if str_gene[i] == int(person[i + 1]):
                matches += 1
        if matches == len(person[1:]):
            result = person[0]
            break

    print(result)

    return


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
