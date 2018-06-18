/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sding <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 18:16:31 by sding             #+#    #+#             */
/*   Updated: 2018/03/03 18:16:34 by sding            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    int                 sock; 
    struct sockaddr_in  server_addr;
    int                 port_nb;
    int                 n;
    char                buffer[1024];

    if (argc == 3)
    {
        port_nb = atoi(argv[2]);
        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            printf("\n Socket creation failed \n");
            return (-1);
        }
  
        memset(&server_addr, 0, sizeof(server_addr));
    
        /* specify an address for the socket */
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(port_nb);
        /* server_addr.sin_addr.s_addr = inet_addr(argv[1]); */
    
        /* 
        ** Convert IPv4 and IPv6 addresses from text to binary form
        ** sb. write server_addr.sin_addr.s_addr = inet_addr(argv[1]), 
        ** inet_addr() converts the internet host address cp from IIPV4 numbers-and-dots notation into binary data
        **   return (-1) if the input is invalid, but -1 is vaild address (255.255.255.255) so to avoid it, use inet_pton 
        */

        if(inet_pton(AF_INET, argv[1], &server_addr.sin_addr) <= 0) 
        {
            printf("\nInvalid address/ Address not supported \n");
            return (-1);
        }
        
        /*
        ** int connect(int socket, const struct sockaddr *address, socklen_t address_len)
        ** -> upon successful completion, a value 0 is returned
        ** -> otherwise, a value of -1 is return.
        */

        if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
        {
            printf("\nConnection Failed \n");
            return (-1);
        }
        printf("Enter your message here: ");
        /* clear the buffer to get the value from client */
        bzero(buffer, 1024);
        /* getting the user input */
        fgets(buffer, 1023, stdin);
        /* call the write method */
        n = write(sock, buffer, strlen(buffer));
        /* if something goes wrong with write method */
        if (n < 0)
        {
            perror("Error writting in socket");
            exit(EXIT_FAILURE);
        }
        /* to clear to buffer to send the values to client */
        bzero(buffer, 1024);
        /* calling the read method, reading the data */
        n = read(sock , buffer, 1023);
        /* if something goes wrong with read method */
        if (n < 0)
        {
            perror("Error reading on socket");
            exit(EXIT_FAILURE);
        }
        printf("%s\n", buffer);
        printf("%s\n", "<Socket connection closed>");
        return (0);
    }
}
