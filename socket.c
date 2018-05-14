#include <stddef.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <netdb.h>

int make_socket(const char * inaddr, uint16_t port) {
    int sock = 0;
    if((sock = socket(AF_INET, SOCK_DGRAM, 0))< 0) {
      fprintf(stderr,"\n Error : Could not create socket \n");
      return 1;
    }
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr.s_addr = inet_addr(inaddr);

    if(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0) {
        fprintf(stderr,"\n Error : Connect Failed \n");
        return 1;
    }
    return sock;
}

int send_msg(const char *msg, int sock) {
// Send message to TORCS
    if (send(sock, msg, sizeof(msg), 0) < 0){
	fprintf(stderr,"\n Error : Message cannot be sent\n");
	return -1;
	}

    printf("Message sent to Client ...\n");
/***
    printf("############ Message ############\n");
    printf("%s", msg);
    printf("\n#################################\n");
***/
    return 0;
}

char * recev_msg(int sock, int m_size) {
    char * buffer = (char *) malloc(m_size*sizeof(char));
    if ((n = read(sock, buffer, sizeof(recvBuff)-1))) {
        fprintf(stderr,"\n Error : Could not receive from socket \n");
	return NULL;
    }

    printf("Received Message from Client ...\n");
/***
    printf("############ Message ############\n");
    printf("%s", msgbuffer);
    printf("\n#################################\n");
 ***/
    return buffer;
}

int close_socket(int sock) {
    if ((shutdown(sock, STOP_RW)) < 0) {
        fprintf(stderr,"\n Error : Shutdown failed \n");
	return -1;
    }
    return 0;
}

