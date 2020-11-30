#include <stdio.h> 
#include <netdb.h> 
#include <unistd.h>
#include <netinet/in.h> 
#include <stdlib.h> 
#include<arpa/inet.h>
#include<sys/stat.h>
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h>
#include<time.h>
#define MAX 80 
#define PORT 8888
#define SA struct sockaddr

struct mailFormat{
char * flags; char * from; char * to; char * subject; char * ctype; char * mversion;
};

void helper(int sockfd){
int c = 0; int choice[1]; int uid[1]; int flag = 1; char buffer[600]; int k1[1]; char ans[600]; char f[600];

struct mailFormat mails[3];
	 mails[0].flags = "t"; mails[0].from = "t"; mails[0].to = "t"; mails[0].subject = "N"; mails[0].ctype = "T"; mails[0].mversion = "1";

	mails[1].flags = "Answered"; mails[1].from = "bala@gmail.com"; mails[1].to = "disha@gmail.com"; mails[1].subject = "1 Subject"; mails[1].ctype = "Text/Plain"; mails[1].mversion = "1.0";

 mails[2].flags = "Deleted"; mails[2].from = "pooja@gmail.com"; mails[2].to = "sam@gmail.com"; mails[2].subject = "2 Subject"; mails[2].ctype = "Text/Plain"; mails[2].mversion = "1.0";

for(;;){
if(flag == 0) break;
bzero(&choice, sizeof(choice));
bzero(&k1, sizeof(k1));
read(sockfd, choice, sizeof(choice));
c = choice[0];
switch(c){
case 1: // fetch
bzero(&uid, sizeof(uid));
bzero(&choice, sizeof(choice));
read(sockfd, uid, sizeof(uid));
read(sockfd, choice, sizeof(choice));
bzero(&buffer, sizeof(buffer));
if(choice[0] == 1) strncpy(buffer, mails[uid[0]].flags, 200);
else if(choice[0] == 2) strncpy(buffer, mails[uid[0]].from, 300);
else if(choice[0] == 3) strncpy(buffer, mails[uid[0]].to, 300);
else if(choice[0] == 4) strncpy(buffer, mails[uid[0]].subject, 300);
else if(choice[0] == 5) strncpy(buffer, mails[uid[0]].ctype, 300);
else strncpy(buffer, mails[uid[0]].mversion, 300);
write(sockfd, buffer, sizeof(buffer));
break;

case 2: // fetch *
bzero(&uid, sizeof(uid));
read(sockfd, uid, sizeof(uid));
bzero(&buffer, sizeof(buffer));
strcat(buffer, mails[uid[0]].flags); strcat(buffer, "\n"); strcat(buffer, mails[uid[0]].from); strcat(buffer, "\n"); strcat(buffer, mails[uid[0]].to); strcat(buffer, "\n"); strcat(buffer, mails[uid[0]].subject); strcat(buffer, "\n"); strcat(buffer, mails[uid[0]].ctype); strcat(buffer, "\n"); strcat(buffer, mails[uid[0]].mversion);
write(sockfd, buffer, sizeof(buffer));
break;

case 3: sleep(2 ^ 1000); 
break;

case 4: 
break;

case 5: bzero(&k1, sizeof(k1));
k1[1]; k1[0] = 3;
write(sockfd, k1, sizeof(k1));
break;

case 6: bzero(&buffer, sizeof(buffer));
bzero(&f, sizeof(f));

read(sockfd, buffer, sizeof(buffer));
k1[0] = 3;
for(int i = 0; i < k1[0]; i++){
if(strcmp(mails[i].from, buffer) == 0){
bzero(&ans, sizeof(ans));
sprintf(ans, "%d , ", i);
strcat(f, ans); 
}
}
write(sockfd, f, sizeof(f));
break;



default: flag = 0; break;
}
}
}
int main(){
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == -1){
		printf("[Error] Socket Failed\n");
		exit(0);
	}
	else printf("[+] Socket Created\n");
	struct sockaddr_in addr, cli;
	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(PORT);
	if(bind(sockfd, (SA*)&addr, sizeof(addr)) != 0){
		printf("[Error] Bind Failed\n");
		exit(0);
	}
	else printf("[+] Bind Success\n");
	if(listen(sockfd, 5) != 0){
		printf("[Error] ListenFailed\n");
		exit(0);
	}
	else printf("[+] Listen Successful\n");
	int len = sizeof(cli);
	int confd = accept(sockfd, (SA*)&cli, &len);
	if(confd < 0){
		printf("[Error] Server Failed\n");
		exit(0);
	}
	else printf("[+] Server Success\n");
	helper(confd);
	close(sockfd);

}
