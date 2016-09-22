class RowData:

    def __init__(self, line):
        self.vector = line.split(',"')

    def __str__(self):
        formatString = "%-4s|%-10s|%-3s|%-35s|%-7s|%-10s|%-8s|%-6s|%-10s|%-14s|%-45s|%-3s|%-8s"
        return formatString % (self[0],self[1],self[2],self[3],self[4],self[5],self[6],self[7],self[8],self[9],self[10],self[11],self[12])

    def __getitem__(self, index):
        return self.vector[index].strip().replace('"',"").replace(",","")

def main():
    f = open('sched.csv','r')
    lines = f.readlines()
    classes = []
    i = 0;
    for item in lines:
        if i == 0:
            i = i + 1
            continue
        classes.append(RowData(item))
    while True:
        print "What would you like to do?"
        print "P - print all rows"
        print "S - search by class"
        print "N - search by number"
        print "O - print all open courses"
        print "D - search by days"
        print "L - search by building"
        print "E - exit"
        yn = raw_input().upper()
        if yn == "P":
            for val in classes:
                print val
        elif yn == "L":
            print "Enter building name (i.e FORBES)"
            build = raw_input()
            for val in classes:
                if val[9].find(build.upper()) != -1:
                    print val
        elif yn == "D":
            print "Enter days (i.e MWF)"
            days = raw_input()
            for val in classes:
                if val[7].find(days) != -1:
                    print val
        elif yn == "S":
            print "Enter course name (i.e. CPSC)"
            cname = raw_input()
            for val in classes:
                if val[1].find(cname.upper().strip()) != -1:
                    print val
        elif yn == "N":
            print "Enter course number (i.e 150)"
            cname = raw_input()
            for val in classes:
                if val[1].find(cname.upper().strip()) != -1:
                    print val
        elif yn == "O":
            for val in classes:
                if val[12].upper() == "OPEN":
                    print val
        elif yn == "E":
            return
        print "(press enter to continue)"
        raw_input()

main()
