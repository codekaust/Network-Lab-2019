#include <arpa/inet.h> 
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <string.h> 

#define PORT 8080

int main(int argc, char const *argv[]) 
{ 
    int sock = 0, valread; 
    struct sockaddr_in serv_addr; 
    char *request = "Client Request"; 
    char buffer[1024] = {0}; 

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Error in socket creation. \n"); 
        return -1; 
    } 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 
    
    send(sock , request , strlen(request) , 0 ); 
    printf("Request message sent\n"); 
    valread = read( sock , buffer, 1024); 
    printf("%s\n",buffer ); 
    return 0; 
} 