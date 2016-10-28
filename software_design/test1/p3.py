csvFile = open('mid2prob3_results.csv',"r")
lc = 0

colnames = []
finalArray = []
tmpNameArray = []

# for line in csvFile:
    # print line

lc = 0

for line in csvFile:
    if lc < 2:
        lc = lc + 1
        continue
    csved = line.split(',')
    mArray = []
    for val in csved:
        mArray.append(val.strip())
    finalArray.append(mArray)

currRow = 0
for array in finalArray:
    count = 0
    avg = 0.0
    total = 0.0
    wStr = ""
    # if currRow < 2:
    #     currRow = currRow + 1
    #     continue
    for val in array:
        if count == 0 or count == 1:
            wStr = wStr + " " + val
        else:
            if val != '':
                total = total + float(val)
            else:
                total = total + 0
        count = count + 1
    print (wStr + " average: " + str(total / (count - 2))).strip()
# print finalArray
print("")
print("Column Averages:")
numRows = len(finalArray)
numCols = len(finalArray[0])

currRow = 0
count = 0
for i in range(2,numCols - 1):
    total = 0.0
    avg = 0.0
    cName = "G" + str(i - 1)
    for array in finalArray:
        if array[i] != '':
            total = total + float(array[i])
        count = count + 1
    print(cName + " " +str(total / count))
