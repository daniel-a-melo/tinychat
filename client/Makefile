GTK_HEADERS = `pkg-config --cflags gtk+-3.0`
GTK_LIBS = `pkg-config --libs gtk+-3.0`

all: tinychat

gui.o: gui.h gui.c
	gcc $(GTK_HEADERS) -c gui.c $(GTK_LIBS)
tinychat: tinychat.c gui.o
	gcc $(GTK_HEADERS) -o tinychat tinychat.c gui.o $(GTK_LIBS)
