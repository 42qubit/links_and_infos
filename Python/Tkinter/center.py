#-------------------------------------------------------------------------------
# Name:        center.py
# Purpose:     Provides a function to center a tkinter window on the desktop.
#
# Author:      Gregor Soennichsen
#
# Created:     30.07.2014
#-------------------------------------------------------------------------------

def center(win):

    win.update_idletasks()

    width  = win.winfo_width()
    height = win.winfo_height()

    frm_width = win.winfo_rootx() - win.winfo_x()
    win_width =  width + 2 * frm_width

    titlebar_height = win.winfo_rooty() - win.winfo_y()
    win_height = height + titlebar_height + frm_width

    x = win.winfo_screenwidth() // 2 - win_width // 2
    y = win.winfo_screenheight() // 2 - win_height // 2

    win.geometry('{}x{}+{}+{}'.format(width, height, x, y))

    if win.attributes('-alpha') == 0:
        win.attributes('-alpha', 1.0)
    win.deiconify()