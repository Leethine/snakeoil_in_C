#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <netdb.h>

int make_socket(const char * inaddr, uint16_t port);

int send_msg(const char *msg, int sock);

char * recev_msg(int sock, int m_size);

int close_socket(int sock);


