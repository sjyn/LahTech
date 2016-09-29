#Steven Rosendahl
#Partner: python.org

diction = {'A':4.0, 'A-':3.7, 'B+':3.3, 'B':3.0, 'B-':2.7, 'C+':2.3, 'C':2.0, 'C-':1.7, 'D+':1.3, 'D':1.0, 'D-':0.7, 'F':0.3}

scores = []
i = 0
total = 0
while i < 5:
    print("Enter your letter grade:")
    scores.append(input())
    i = i + 1
for score in scores:
    total = total + diction[score.upper()]
print("Your GPA is %.2f" % (total / (i)))
