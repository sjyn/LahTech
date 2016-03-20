# Getting C Running on Your Machine

Here is a guid on how to get C running on your machine. The installation steps differ based on
whether or not you have a Windows OS or a Mac OS.

## OS X
If you're running OS X, you probably have everything you need already. To test this, you can open
up the Terminal application. If you can't find that, simply press `Cmd + Space`, type "Terminal",
and press enter. If you've never opened your Terminal before, you will most likely be presented
with a white screen and black text. You will see something similar to  

`computername:~ username$ _`  

From here, you have access to the majority of your operating system. You can run commands which will
do various things. The one that we are interested in is `which`, which tells you where another
command is installed, or nothing if the command is installed. In the Terminal, type

`which gcc`

and press enter. You should see something akin to `/usr/bin/gcc`, which indicates that you have `gcc`
installed.

## Windows
If you have Windows, you probably don't have a readily available version of C. You have serveral
options available to you, but you probably want to install Cygwin. Cygwin is a Terminal-like
application that allows you to run commands that Linux/Mac users will be familiar with. One such
command is `gcc`, which will allow you to create and ultimately run C code. To get started, go to
http://cygwin.com/install.html, and select the correct `setup-x86` link. If you don't know if you
have a 32 or 64 bit OS, you can open up Control Panel, choose System and Security, and click on
System. Under the System subsection, you will see System Type, which will tell you what kind of
OS you have.

Once you have downloaded the `setup-x86` for your OS, run the program. You will be presented with
several windows about selecting packages and such. Continue through these windows until the installer
is done. You should now see the Cygwin program on your desktop. What Cygwin has done is created what's
called a Terminal. From the Terminal, you can execute many different programs. The one you will want
is called `gcc`, but it's not installed yet. To install it, type the following into the Terminal
and press enter.

`setup-x86_64.exe -q -P wget -P gcc-g++ -P make -P diffutils -P libmpfr-devel -P libgmp-devel -P libmpc-devel`

What you have done is installed `gcc`, which you can use to compile your C programs, and all the
other packaged that `gcc` needed.

## Testing C

### OS X
To test your C installtion, return to the Terminal and type

`cd Desktop ; touch test.c`

This line tells the terminal to change its current directory into the Desktop, and to create a file
called `test.c`.

### Windows
Navigate to any folder you want, and create a new text document called `test`. You will want to
press `Ctrl + Shift + S`, and re-save the file with the name `test.c`. Before you continue, make
sure you choose `all files` from the dropdown menu below the name where it says `text file`. If you
do now, you cannot compile the file correctly.

### A Simple C Program

You can now open up `test.c`, and type
```c
#include <stdio.h>

int main(int argc, const char* argv[]){
    printf("%s\n", "Hello, world!");
    return 0;
}
```
This creates a simple program that will print "Hello, world!", but we need to compile it. In your
Terminal, type `gcc test.c`. This compiles the code you just wrote, and produces a file called
`a` or `a.exe` on Windows or `a.out` on OS X. To run this program, simply type `./a` or `./a.exe` on
Windows, or `./a.out` on OS X, and press enter. You should see the "Hello, world!" pop up, and then
the program ends. Congrats, you successfully ran a C program.
