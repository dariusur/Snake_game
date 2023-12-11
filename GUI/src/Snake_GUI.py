from tkinter import *
import serial

'''
COMMENTS ABOUT tkinter MODULE

The tkinter package is a Python interface to the Tcl/Tk (pronounced "tickle teak") GUI toolkit.
Tcl/Tk enables building a graphical user interface (GUI) natively in Tcl (Tk was developed as an extension to Tcl scripting language)
Tcl/Tk is included in the standard Python installation in the form of Tkinter.
It is cross platform with support for Linux, Mac OS, Unix, and Microsoft Windows operating systems.

Tcl - dynamic interpreted programming language, just like Python.
      Though it can be used on its own as a general-purpose programming language,
      it is most commonly embedded into C applications as a scripting engine or an interface to the Tk toolkit. 
Tk - Tcl package implemented in C that adds custom commands to create and manipulate GUI widgets.
     Each Tk object embeds its own Tcl interpreter instance with Tk loaded into it.
Ttk - Themed Tk (Ttk) is a newer family of Tk widgets that provide a much better
      appearance on different platforms than many of the classic Tk widgets.
'''

com = input("COM port: ")
arduino = serial.Serial('COM'+str(com), 115200)

# Creates an instance of the Tk class, which initializes Tk and creates its associated Tcl interpreter.
# It also creates a toplevel window, known as the root window, which serves as the main window of the application.
root = Tk()
# geometry method is used to set the dimensions and position of the Tkinter window on the user’s desktop.
root.geometry("306x205+500+300")
# Creates a frame widget, which can accomodate other widgets. The frame is fit inside the root window.
frame = Frame(root)
# Creates a grid than allows positioning of widgets with columns and rows
frame.grid()

# Some widgets can display an image such as Label and Button.
# These widgets take an image argument that allows them to display an image.
# However, you can’t just simply pass the path to an image file to the image argument.
# Instead, you need to create a PhotoImage object and pass it the image argument.
UPimg = PhotoImage(file="images/UP.png")
DOWNimg = PhotoImage(file="images/DOWN.png")
LEFTimg = PhotoImage(file="images/LEFT.png")
RIGHTimg = PhotoImage(file="images/RIGHT.png")

# Button constructs a button widget in the specified frame
UP_key = Button(frame, image=UPimg, borderwidth=0)
DOWN_key = Button(frame, image=DOWNimg, borderwidth=0)
LEFT_key = Button(frame, image=LEFTimg, borderwidth=0)
RIGHT_key = Button(frame, image=RIGHTimg, borderwidth=0)

# Calling grid directly on Button causes an error because it returns None
UP_key.grid(column=1, row=0)
DOWN_key.grid(column=1, row=1)
LEFT_key.grid(column=0, row=1)
RIGHT_key.grid(column=2, row=1)

# Callback functions send data to arduino and changes the appearance of the button to look like it has been pressed.
def press_up(event):
   arduino.write("0".encode())
   UP_key.config(relief=SUNKEN)
   UP_key.after(100, raise_up)

def press_down(event):
   arduino.write("1".encode())
   DOWN_key.config(relief=SUNKEN)
   DOWN_key.after(100, raise_down)

def press_left(event):
   arduino.write("2".encode())
   LEFT_key.config(relief=SUNKEN)
   LEFT_key.after(100, raise_left)

def press_right(event):
   arduino.write("3".encode())
   RIGHT_key.config(relief=SUNKEN)
   RIGHT_key.after(100, raise_right)

# Functions that are called after 100ms from the callback functions
def raise_up():
   UP_key.config(relief=RAISED)

def raise_down():
   DOWN_key.config(relief=RAISED)

def raise_left():
   LEFT_key.config(relief=RAISED)

def raise_right():
   RIGHT_key.config(relief=RAISED)

# Triggers a callback function when an event occurs. An event instance is passed as the argument to the function.
root.bind('<Up>', press_up)
root.bind('<Down>', press_down)
root.bind('<Left>', press_left)
root.bind('<Right>', press_right)

# Puts everything on the display, and responds to user input until the program terminates.
root.mainloop()