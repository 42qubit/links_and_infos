#-------------------------------------------------------------------------------
# Name:        fullscreen.py
# Purpose:     Demonstrates how to implement a fullscreen functionality for a
#              tkinter window.
#
# Author:      Gregor Soennichsen
#
# Created:     23.07.2014
#-------------------------------------------------------------------------------

from Tkinter import *

class Application:

    def __init__(self):
        self.root = Tk()
        self.root.bind("<F11>",self.full)
        #root.wm_attributes("-fullscreen", True)
        self.root.mainloop()

    def full(self,event):
        self.root.wm_attributes("-fullscreen",True)
        self.root.unbind_all("<F11>")
        self.root.bind("<F11>",self.unfull)

    def unfull(self,event):
        self.root.wm_attributes("-fullscreen",False)
        self.root.unbind_all("<F11>")
        self.root.bind("<F11>",self.full)

Application()

