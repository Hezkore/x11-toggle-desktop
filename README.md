# X11 Toggle Desktop Visibility

A very simple C program that allows you to toggle the visibility of your desktop on a Linux machine running an X11-based window system.\
Should work on all desktop environments, but tested only on XFCE.

## What does the code do?

The code uses the X11 library to interact with the X server and send a client message event to toggle the visibility of the desktop. It first opens a connection to the X server and gets the root window. It then retrieves the current state of the desktop visibility using the `_NET_SHOWING_DESKTOP` atom. Finally, it sends a client message event to the X server to toggle the visibility of the desktop.

## What is it good for?

* You can bind it to a keyboard shortcut.
* You can use it in a launcher application.
* You can use it in your own program to toggle the desktop visibility.
* You can use it as a desktop widget or action to toggle the desktop visibility.

Or just as a starting point for your own X11 program.

## Prerequisites

* libx11-dev

## How to build

```bash
gcc -o toggle_desktop toggle_desktop.c -lX11
```
Test it with:
```bash
./toggle_desktop; sleep 1; ./toggle_desktop
```