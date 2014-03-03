#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>


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
    name.sin_port = (in_port_t)htons(port);
    name.sin_addr.s_addr = htonl(INADDR_ANY);
    
    int reuse = 1;
    if (setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, (char *) &reuse, sizeof(int)) == -1) {
        puts("Cannot set reuse option");
    }
    
    int bret = bind(socket, (struct sockaddr *) &name, sizeof(name));
    if (bret == -1) {
        puts("Cannot bind socket to port 2000");
    }
    
    if (listen(socket, 10) == -1) {
        puts("Cannot listen to port 2000");
    }
    
    puts("Waiting for connection");
}

void say(int socket, char *s) {
    if (send(socket, s, strlen(s),0) == -1) {
      puts("Error sending message");
    }
}

int main(int argc, char *argv[]) {

    int listener_d = socket(PF_INET, SOCK_STREAM, 0);
    if (listener_d == -1) {
        puts("Cannot open socket");
    }
    
    listen_to_port(listener_d, 2000);
    
    char buf[255];
    
    while (1) {
        struct sockaddr_storage client_addr;
        unsigned int addr_size = sizeof(client_addr);
        int connect_d = accept(listener_d, (struct sockaddr *) &client_addr, &addr_size);
    
        if (connect_d == -1) {
            puts("Cannot open secondary socket");
        }
    
        char *msg = "Hey Ho Protocol Server\r\nVersion 1.0\r\nHey!\r\n";
    
        say(connect_d, msg);   
        
        read_in(connect_d, buf, sizeof(buf));
        printf("Did you say ? : %s \n", buf);
        
        close(connect_d);
    
    }
    
    return 0;

}
