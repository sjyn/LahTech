# A program that calculates your GPA
# @author Steven Rosendahl

print("This program calculates grade point average.")
i = 0
avg = 0.0
while(i < 5):
    print("Enter course %d grade->" % (i+1))
    avg = avg + float(input())
    i = i + 1
print("Your GPA for last semester was: %.2f" % (avg / 5))
