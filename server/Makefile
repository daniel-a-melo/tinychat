UNAME := $(shell uname)

ifneq ($(UNAME), Linux)
LIB_SOCKET = -lws2_32
endif

all: tinychat-server

tinychat-server: tinychat-server.c
	gcc -Wall -g -o tinychat-server tinychat-server.c $(LIB_SOCKET)

clean:
	rm -f tinychat-server.exe tinychat-server