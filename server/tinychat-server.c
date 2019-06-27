// https://stackoverflow.com/questions/28027937/cross-platform-sockets

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#ifdef WIN32
#include <winsock2.h>
#include <windows.h>
#else
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#endif 


int read_in(int socket, char *buf, int len) {
    
    char *s = buf;
    int bytes_read = 0;
    
    bytes_read = recv(socket, buf, len, 0);
    while ((bytes_read > 0) && (s[bytes_read-1] != '\n'))  {
        bytes_read = recv(socket, buf, len, 0);    
    }

    buf[bytes_read] = '\0';
    return bytes_read;
}

void listen_to_port(int socket, int port) {

    struct sockaddr_in name;
    name.sin_family = PF_INET;
    name.sin_port = (u_short)htons(port);
    name.sin_addr.s_addr = htonl(INADDR_ANY);
    
    int reuse = 1;
    if (setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, (char *) &reuse, sizeof(int)) == -1) {
        puts("Cannot set reuse option");
        exit(-2);
    }
    
    int bret = bind(socket, (struct sockaddr *) &name, sizeof(name));
    if (bret == -1) {
        puts("Cannot bind socket to port 2000");
        exit(-3);
    }
    
    if (listen(socket, 10) == -1) {
        puts("Cannot listen to port 2000");
        exit(-4);
    }
    
    puts("Waiting for connection");
}

void say(int socket, char *s) {
    if (send(socket, s, strlen(s),0) == -1) {
      puts("Error sending message");
    }
}

void print_last_error() {
#ifdef WIN32 
    int error = 0;
    error = WSAGetLastError();
    printf("Code %d\n", error);
#endif
}

int main(int argc, char *argv[]) {

#ifdef WIN32    
    WSADATA wsaData;

    if (WSAStartup(0x202, &wsaData) != 0) {
        puts("WSAStartup failed");
        exit(-5);
    }
#endif
    int listener_d = socket(PF_INET, SOCK_STREAM, 0);
    if (listener_d == -1) {
        puts("Cannot open socket");
        print_last_error();
        exit(-1);
    }
    
    listen_to_port(listener_d, 2000);
    
    char buf[255];

    int count = 1;

    while (count < 4) {
        struct sockaddr_storage client_addr;
        unsigned int addr_size = sizeof(client_addr);

#ifdef WIN32
        int connect_d = accept(listener_d, (struct sockaddr *) &client_addr, (int *) &addr_size);
        printf("Connect_d : %d", connect_d);
        if (connect_d == INVALID_SOCKET) {
            puts("Cannot open secondary socket");
            print_last_error();
            break;
        }
#else
        int connect_d = accept(listener_d, (struct sockaddr *) &client_addr, &addr_size);
        if (connect_d == -1) {
            puts("Cannot open secondary socket");
            break;
        }
#endif
   
    
        char *msg = "Hey Ho Protocol Server\r\nVersion 1.0\r\nHey!\r\n";
    
        say(connect_d, msg);   
        
        read_in(connect_d, buf, sizeof(buf));
        printf("Did you say ? : %s \n", buf);
        
        puts("Will close connection");
#ifdef WIN32 
        closesocket(connect_d);
#else
        close(connect_d);
#endif
        
        puts("Closed connection");
        
        count++;
    
    }
#ifdef WIN32 
    WSACleanup();
#endif    
    puts("Program finished");
    return 0;

}
