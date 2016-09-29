from tkinter import Tk, RIGHT, BOTH, RAISED
from tkinter.ttk import Frame, Style, Button

class GPACalc(Frame):

    def __init__(self, parent):
        Frame.__init__(self, parent)
        self.parent = parent
        self.initUI()

    def onPressCalc():
        print("Hello world")

    def initUI(self):
        self.parent.title("GPA Calculator")
        self.style = Style()
        self.style.theme_use("default")

        frame = Frame(self, relief=RAISED, borderwidth=1)
        frame.pack(fill=BOTH, expand=True)
        self.pack(fill=BOTH, expand=True)

        calculateButton = Button(self, text="Calculate", command=lambda: self.onPressCalc)
        calculateButton.pack(side=RIGHT, padx=5, pady=5)

def main():
    root = Tk()
    root.geometry("300x200+300+300")
    app = GPACalc(root)
    root.mainloop()
main()
