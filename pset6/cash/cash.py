from cs50 import get_float
import math

fChange = -1
while fChange < 0 or fChange > 23:
    fChange = get_float("Enter needed change: ")

# Calculate cash in cents
iChange = round(fChange * 100)
# Calculate number of 25 cents coins
i25Change = math.floor(iChange / 25)
# Calculate number of 10 cents coins
i10Change = math.floor((iChange - (i25Change * 25)) / 10)
# Calculate number of 5 cents coins
i5Change = math.floor((iChange - (i25Change * 25 + i10Change * 10)) / 5)
# Calculate number of 1 cent coins
i1Change = iChange - i25Change * 25 - i10Change * 10 - i5Change * 5
# Calculate total number of coins
iNumberCoins = i25Change + i10Change + i5Change + i1Change

print(f"{iNumberCoins}")
