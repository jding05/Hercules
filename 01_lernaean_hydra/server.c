/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sding <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 18:16:22 by sding             #+#    #+#             */
/*   Updated: 2018/03/03 18:16:24 by sding            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>      
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int                 server_fd; 
    int                 client_fd; 
    struct sockaddr_in  address;
    int                 opt;
    int                 addrlen;
    char                buffer[1024];
    int                 port_nb;

    opt = 1;
    addrlen = sizeof(address);
    port_nb = atoi(argv[1]);
    if (argc != 2 || (argc == 2 && (port_nb < 0 || port_nb > 65535)))
        return (-1);
    
    /*
    ** Creating socket file descriptor
    ** socket(domain, type, protocol) -> -1 if an error occurs, otherwise a descriptor referencing the socket
    ** !!!here we run two function, 1. server_fd = socket(), 2. if (server_fd == 0) 
    ** -> if the result sever_fd == 1, just don't run this function, don't affect any other function 
    ** #define PF_INET  AF_INET (in source code), so Protocol families, same as address family
    */

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    /*
    ** Forcefully attaching socket to the port 4200
    ** this helps in manipulating options for the socket referrred by the file descriptor sockfd.
    ** this is completely optional, but it helps in reuse of address and port. 
    ** prevents error such as: "address already in use"
    ** int setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen);
    ** ->return: 0 is successful, otherwise -1
    ** So_reuseaddr -> specifies that the rules used in validating addresses supplied to bind()
    **      should allow reuse of local address.
    */

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    memset(&address, 0, sizeof(address)); 

    /*
    ** bind() of INADDR_ANY doesn't "generate a random IP", it binds the socket to all available interfaces
    ** to bind socket w/ localhost, before you invoke the bind function, sin_addr.s_addr field of
    **      the sockaddr_in structure should be set properly, like:
    **      -> my_sockaddress.sin_addr.s_addr = inet_addr("127.0.0.1")
    ** or   -> my_sockaddress.sin_addr.s_addr = htonl(INADDR_LOOPBACK)
    ** htonl() converts the unsigned integer hostlong from host byte order to network byte order
    ** htons() function converts the unsigned short integer hostshort from the host byte order to network byte order
    */
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(port_nb);

    /*
    ** Forcefully attaching socket to the port 4200
    ** int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
    ** bind the socket to our secified IP and port
    */
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    /*listen() -> return 0 is successful, otherwise -1 */
    if (listen(server_fd, 3) < 0)
    {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    /*
    ** accept connection between client and server
    ** int new_socket = accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen)
    **                                      sockaddr *addr ->client's adress information, if its local, set it to NULL
    ** return: on success, these system calls return a nonnegatie integer that is a file descriptor
    **      for the accepted socket. on error, -1 is returned
    ** client_fd -> is a file descriptor
    */ 
    if ((client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0)
    {
        perror("accept failed");
        exit(EXIT_FAILURE);
    }

    /*
    ** ssize_t read(int fildes, void *buf, size_t nbytes)
    ** return: the umber of bytes that were read. If value is negative, 
    ** then the system call returned an error
    ** flides -> teh file descriptor of where to read the input. U can either use a file descriptor 
    ** obtained from the open system call, or 0,1,2 for STDIN, STDOUT,STDERR
    ** buf -> a char array where the read content will be stored
    */
    while (1)
    {
        bzero(buffer, 1024);
        read(client_fd, buffer, 1024);
        if (!strncmp("ping", buffer, 4))
            write(client_fd, "pong\npong\n", sizeof("pong\npong\n"));
        else
            write(client_fd, "\nMessage you sent is not 'ping'\nMessage you sent is not 'ping'\n", 65);
        /* close(client_fd); */
        break;
    }
    return (0);
}

/* 
** to test you can either use 1. client.c or 2. echo server
** for echo server
** type echo -n "ping" | nc localhost 6001 (<- this is port number)
*/
