from cs50 import get_string
import sys

if len(sys.argv) != 2:
    print("Wrong number of arguments!")
    sys.exit(1)

# Convert string to int key
iKey = int(sys.argv[1])

# Promt for plain text
sPlainText = get_string("plaintext: ")

print("ciphertext: ", end='')

# Print ciphertext
for c in sPlainText:
    if str.islower(c):
        print(chr(97 + (ord(c) + iKey - 97) % 26), end='')
    elif str.isupper(c):
        print(chr(65 + (ord(c) + iKey - 65) % 26), end='')
    else:
        print(c, end='')
print()