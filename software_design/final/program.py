from tkinter import *
from csv import reader

window = Tk()
window.title("CSV First Line")

f = open("./ScheduleOfClasses_sp17.csv")
i = 0

lines = []

for line in reader(f):
    if i == 2:
        break
    else:
        lines.append(line)
    i = i + 1
fl = lines[0]
sl = lines[1]

rc = 0
for val in fl:
    label = Label(window, text=val, justify=LEFT)
    label.grid(row=rc, column=0,sticky=W)
    entry = Entry(window, text=sl[rc])
    entry.grid(row=rc, column=1)
    entry.insert(0,sl[rc])
    rc = rc + 1
    
window.mainloop()
