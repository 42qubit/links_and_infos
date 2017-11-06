#-------------------------------------------------------------------------------
# Name:        eliminate_border.py
# Purpose:     Demonstrates how to implement remove the border of a tkinter
#              window.
#
# Author:      Gregor Soennichsen
#
# Created:     02.06.2014
#-------------------------------------------------------------------------------

from Tkinter import *

root = Tk()
root.minsize(100, 100)
root.overrideredirect(2)

def destr():root.destroy()
Button(root,command=destr,text="Destroy").pack()

root.mainloop()