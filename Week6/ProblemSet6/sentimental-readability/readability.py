# This program computes the Coleman-Liau index as 0.0588 * L - 0.296 * S - 15.8
# where L is the average number of letters per 100 words in the text,
# and S is the average number of sentences per 100 words in the text.
# The output is the school grade level of difficulty to read a text given as input.
import re
from cs50 import get_string

# Get user input
ui = get_string("Text: ")

# Calculate Coleman-Liau index
words_count = ui.count(" ") + 1
sentences_count = ui.count(".") + ui.count("!") + ui.count("?")
letters_count = len(re.sub("[^A-Za-z]", "", ui))
S = 100 * sentences_count / words_count
L = 100 * letters_count / words_count
coleman_liau_index = 0.0588 * L - 0.296 * S - 15.8

# Determine grade based on index
grade = round(coleman_liau_index, 0)

if grade < 1:
    print("Before Grade 1")
elif grade <= 16:
    print(f"Grade {grade:.0f}")
else:
    print("Grade 16+")
