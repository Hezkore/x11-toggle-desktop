#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <stdlib.h>

void exit_on_null(void *ptr, Display *disp) { // Graceful exit utility
	if (!ptr) {
		if (disp) XCloseDisplay(disp);
		exit(EXIT_FAILURE);
	}
}

int main() {
	Display *disp = XOpenDisplay(NULL); // Open X display
	exit_on_null(disp, NULL);
	
	Window root = DefaultRootWindow(disp);
	Atom desktopAtom = XInternAtom(disp, "_NET_SHOWING_DESKTOP", False);
	
	Atom type;
	int format, state = 0;
	unsigned long nitems, bytes_after;
	unsigned char *prop = NULL;
	
	// Get desktop visibility state
	if (XGetWindowProperty(disp, root, desktopAtom, 0, 1, False, XA_CARDINAL, &type, &format, &nitems, &bytes_after, &prop) == Success) {
		if (prop) {
			state = *prop;
			XFree(prop);
		}
	}
	
	XEvent event = {
		.xclient = {
			.type = ClientMessage,
			.send_event = True,
			.display = disp,
			.window = root,
			.message_type = desktopAtom,
			.format = 32,
			.data.l[0] = !state // Toggle visibility
		}
	};
	
	XSendEvent(disp, root, False, SubstructureRedirectMask | SubstructureNotifyMask, &event); // Send event
	XCloseDisplay(disp); // Clean up
	
	return EXIT_SUCCESS;
}