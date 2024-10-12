# This program takes a credit card number as input and
# tries to identify it as American Express, Visa or Mastercard
# using the length of the number entered, the starting digits
# and Luhn's algorithm. Possible outputs: AMEX, MASTERCARD, VISA
# or INVALID if the number corresponds to none of the criteria.

# some numbers to test:    should return:
# 378282246310005          AMEX
# 371449635398431          AMEX
# 5555555555554444         MASTERCARD
# 5105105105105100         MASTERCARD
# 4003600000000014         VISA
# 4111111111111111         VISA
# 4012888888881881         VISA
# 4222222222222            VISA
# 1234567890               INVALID
# 369421438430814          INVALID
# 4062901840               INVALID
# 5673598276138003         INVALID


def main():
    ui = input("Number: ")

    # check if the user input is a number
    try:
        int(ui)
    except ValueError:
        print("INVALID")
        exit()

    # validate card type (VISA/MASTERCARD/AMEX or INVALID)
    type = get_card_type(ui)

    # if not invalid already, do the luhn check and if it rejects the number assign type = INVALID:
    if type != "INVALID" and not luhn_valid(ui):
        type = "INVALID"

    # print result
    print(type)


# determines VISA/MASTERCARD/AMEX
# based first two digits and total number of digits
def get_card_type(ui):
    type = "INVALID"
    length = len(ui)
    match length:
        case 13:
            if ui[0] == '4':
                type = "VISA"

        case 16:
            if ui[0] == '4':
                type = "VISA"
            elif ui[0] == '5' and ui[1] in '12345':
                type = "MASTERCARD"

        case 15:
            if ui[:2] in ('34', '37'):
                type = "AMEX"

    return type


# Validates a card number. Returns True if Valid, False if not.
def luhn_valid(ui):
    l = [char for char in ui]
    l1 = []
    l2 = []
    first = True
    for c in reversed(l):
        if first:
            l1.append(int(c))
        else:
            c = int(c)
            c = c * 2
            if c > 9:
                c = 1 + c % 10
            l2.append(c)
        first = not first
    luhn_sum = sum(l1) + sum(l2)
    if luhn_sum % 10 == 0:
        return True
    else:
        return False


main()
