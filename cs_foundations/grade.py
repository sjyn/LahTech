#Steven Rosendahl

def getGrade(num):
    if num <= 50:
        return 'F'
    else:
        letter = 'F'
        for x in range(50,num):
            if x % 10 == 0:
                letter = chr(ord(letter) - 1)
        return letter
print("Enter your number grade:")
print("Your Grade is %s" % getGrade(int(input())))
