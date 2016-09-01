# A sassy little lucky number generator.
# @author Steven Rosendahl

from random import randint

print("Enter the low score--->")
low = int(float(input()))
print("Enter the high score--->")
high = int(float(input()))

if low > high:
    print("You daft bimbo! Your low score can't be higher than your high score!")
elif low == high:
    print("You didn't really give me much choice... take a wild guess what your lucky number is.")
else:
    print("Your lucky lottery number is %d" % randint(low,high))
