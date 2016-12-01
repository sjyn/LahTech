#Steven rosendahl
#Donnie Darko Simulator

from clint.textui import colored
from csv import reader

CRASH_LOCATION_INDEX = 2

homs = open('./crashes.csv','r')
table = []
lc = 0
for line in reader(homs):
    if lc == 0:
        lc = lc + 1
        continue
    table.append(line)

def mostPopular():
    undoc = "undocumented"
    crashSites = {}
    crashSites[undoc] = 0
    for array in table:
        placeOfCrash = array[CRASH_LOCATION_INDEX].strip().lower()
        actualPlace = placeOfCrash
        if not placeOfCrash == "x":
            if not actualPlace in crashSites:
                crashSites[actualPlace] = 1
            else:
                crashSites[actualPlace] = crashSites[actualPlace] + 1
        else:
            crashSites[undoc] = crashSites[undoc] + 1
    sortedList = sorted(crashSites, key=crashSites.__getitem__)
    tenBestVals = sortedList[-10:]
    for place in tenBestVals:
        pstrA = ""
        amnt = crashSites[place]
        for i in range(0,amnt):
            pstrA = pstrA + colored.red("[]")
        print("%-20s\t%s" % (place, pstrA))

def amIAtRisk():
    totalCrashes = len(table)
    print("What country/state do you live in?")
    location = input().lower().strip()
    myChance = 0
    for array in table:
        placeOfCrash = array[CRASH_LOCATION_INDEX].strip().lower()
        if placeOfCrash != "x":
            if (location in placeOfCrash) or ((location + '"') in placeOfCrash):
                myChance = myChance + 1
    avg = myChance / totalCrashes
    print("There have been an average of " + str(avg) + " crashes in you area.")
    print("The total number of crashes in " + location + " since 1929 is " + str(myChance))
    if(avg > 0.03):
        print(colored.red("You are gonna get Donnie-Darkoed"))
    else:
        print(colored.green("You are not at risk"))

while True:
    print("What would you like to know?")
    print("1. Am I at risk for being hit by an airplane?")
    print("2. Most popular places for crashes")
    print("Q: Exit")
    choice = input().strip().lower()

    if choice == "q":
        break
    elif choice == "1":
        amIAtRisk()
    elif choice == "2":
        mostPopular()
    else:
        print("Unknown Choice")
    print("Press Enter to continue...")
    input()
