class RowData:

    def __init__(self, line):
        self.vector = line.split(',"')
        self.crn = self.vector[0].strip().replace('"','')
        self.course = self.vector[1].strip().replace('"','')
        self.section = self.vector[2].strip().replace('"','')
        self.title = self.vector[3].strip().replace('"','')
        self.hours = self.vector[4].strip().replace('"','')
        self.area = self.vector[5].strip().replace('"','')
        self.type = self.vector[6].strip().replace('"','')
        self.days = self.vector[7].strip().replace('"','')
        self.time = self.vector[8].strip().replace('"','')
        self.loc = self.vector[9].strip().replace('"','')
        self.instructor = self.vector[10].strip().replace('"','')
        self.seats = self.vector[11].strip().replace('"','')
        self.status = self.vector[12].strip().replace('"','').replace(",","")

    def __str__(self):
        return '{:<4}|{:<10}|{:<3}|{:<35}|{:<7}|{:<10}|{:<8}|{:<6}|{:<10}|{:<14}|{:<45}|{:<3}|{:<8}'.format(self.crn,self.course,self.section,self.title,self.hours,self.area,self.type,self.days,self.time,self.loc,self.instructor,self.seats,self.status)

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
        print("What would you like to do?")
        print("P - print all rows")
        print("S - search by class")
        print("N - search by number")
        print("O - print all open courses")
        print("D - search by days")
        print("L - search by building")
        print("E - exit")
        yn = input().upper()
        if yn == "P":
            for val in classes:
                print(val)
        elif yn == "L":
            print("Enter building name (i.e FORBES)")
            build = input()
            for val in classes:
                if val[9].find(build.upper()) != -1:
                    print(val)
        elif yn == "D":
            print("Enter days (i.e MWF)")
            days = input()
            for val in classes:
                if val[7].find(days) != -1:
                    print(val)
        elif yn == "S":
            print("Enter course name (i.e. CPSC)")
            cname = input()
            for val in classes:
                if val[1].find(cname.upper().strip()) != -1:
                    print(val)
        elif yn == "N":
            print("Enter course number (i.e 150)")
            cname = input()
            for val in classes:
                if val[1].find(cname.upper().strip()) != -1:
                    print(val)
        elif yn == "O":
            for val in classes:
                if val[12].upper() == "OPEN":
                    print(val)
        elif yn == "E":
            break
        print("(press enter to continue)")
        input()

main()
