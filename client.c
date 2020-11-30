#include <stdio.h> 
#include <unistd.h>
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h>
#include<time.h>
#include<arpa/inet.h>
#include<sys/stat.h>
#define MAX 80
#define PORT 8888
#define SA struct sockaddr
void helper(int sockfd){
int choice[1], i, c; int uid[1], id; char buffer[600]; char f[600];
for(;;){
bzero(&choice, sizeof(choice));
bzero(&uid, sizeof(uid));
printf("\nEnter Choice");
printf("\n 1. FETCH UID 2. FETCH * 3. IDLE 4. NOOP 5. STATUS 6. SEARCH FROM");
scanf("%d", &i);
choice[0] = i;
write(sockfd, choice, sizeof(choice));
switch(i){
case 1: //fetch
printf("\nEnter UID of your mail");
scanf("%d", &id);
uid[0] = id;
write(sockfd, uid, sizeof(uid));
printf("\n Enter the Choice");
printf("\n 1. FLAG 2. FROM 3. TO 4. SUBJECT 5.CONTENT_TYPE 6. MIME - VERSION");
scanf("%d", &c);
bzero(&choice, sizeof(choice));
choice[0] = c;
write(sockfd, choice, sizeof(choice));
bzero(buffer, sizeof(buffer));
read(sockfd, buffer, sizeof(buffer));
printf("\n%s", buffer);
break;

case 2: //fetch *
printf("\nEnter UID of your mail");
scanf("%d", &id);
uid[0] = id;
bzero(&buffer, sizeof(buffer));
write(sockfd, uid, sizeof(uid));
read(sockfd, buffer, sizeof(buffer));
printf("\n%s", buffer);
break;

case 3: 
break;

case 4: printf("\n Success"); break;

case 5: bzero(&choice, sizeof(choice));
read(sockfd, choice, sizeof(choice));
printf("%d FETCHs", choice[0]);
break;

case 6: printf("\nSearch Mail from?");
bzero(&buffer, sizeof(buffer));
scanf("%s", buffer);
write(sockfd, buffer, sizeof(buffer));
bzero(&f, sizeof(f));
read(sockfd, f, sizeof(f));
printf("\n %s",f);
break;

default: break;
}
}
}
int main(){
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == -1){
		printf("[Error] Socket not created\n");
		exit(0);
	}
	else 
		printf("[+] Socket created\n");
	struct sockaddr_in addr;
	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	if(connect(sockfd, (SA*)&addr, sizeof(addr)) < 0){
		exit(0);
			}
	helper(sockfd);
close(sockfd);
}
