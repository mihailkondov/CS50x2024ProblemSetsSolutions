# This program prompts the user to enter a value in dollars
# representing the change a vending machine must return.
# The program and will calculate the minimum number of coins
# that can represent this change and return that number.

# US coins: 1¢, 5¢, 10¢, 25¢,
# also 50¢, but our machine won't be using 50¢ coins per specification

from cs50 import get_float


while True:
    change = get_float("Enter change: ")
    if change > 0:
        break

denominations = [.25, .1, .05, .01]
coins = 0

for coin in denominations:
    while change >= coin:
        coins += 1
        change = round(change - coin, 2)
print(coins)
