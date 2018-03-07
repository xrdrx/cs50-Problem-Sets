from cs50 import get_int

# Promt for pyramin height between 1 and 23
nPHeight = -1
while nPHeight < 0 or nPHeight > 23:
    nPHeight = get_int("Enter positive number no greater than 23: ")

# For each line
for i in range(nPHeight):
    # White space and blocks
    print(" " * - (i + 1 - nPHeight), "#" * (i + 2), sep='', end='')
    print('')