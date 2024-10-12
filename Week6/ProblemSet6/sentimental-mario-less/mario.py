# This program prompts the user for an integer and then builds
# a pyramid that looks like this (but with the input height):
#    #
#   ##
#  ###
# ####


from cs50 import get_int


# prints a pyramid of # of given height
def print_pyramid(height, max_height):
    # base case
    if height == 0:
        return

    else:
        print_pyramid(height - 1, max_height)
    print(" " * (max_height - height) + "#" * height)


# Get user input and validate
def get_valid_height():
    while True:
        height = get_int("Heigth (1-8): ")
        if height > 0 and height < 9:
            return height


height = get_valid_height()
print_pyramid(height, height)
