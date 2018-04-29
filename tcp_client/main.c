///
/// @file    pro_pool_client.c
/// @author  haozhipeng(1152699659@qq.com)
/// @date    2017-02-12 19:10:01
///
#include"func.h"

int main(int argc,char** argv){
	if(argc!=1){
		printf("error args\n");
		return -1;
	}
	puts(argv[0]);
	int sfd=socket(AF_INET,SOCK_STREAM,0);
	if(-1==sfd){
		perror("socket");
		return -1;
	}
	struct sockaddr_in ser;
	memset(&ser,0,sizeof(ser));
	ser.sin_family=AF_INET;
	ser.sin_port=htons(atoi(PORT));
	ser.sin_addr.s_addr=inet_addr(IP);
	int ret=connect(sfd,(struct sockaddr*)&ser,sizeof(ser));
	if(-1==ret){
		perror("connect");
		return -1;
	}
	char buf[1000]={0};
	int len;
	//	recv_n(sfd,&len,4);
	//	recv_n(sfd,buf,len);
	//	int fd;
	//	fd=open(buf,O_RDWR|O_CREAT,0666);
	//	if(-1==fd){
	//		perror("open");
	//		return -1;
	//	}
	while(1){
		puts("please input command:");
		scanf("%s",buf);
		//		if(buf[0]=='c'){
		//			len=3;
		//			send_n(sfd,&len,4);
		//			send_n(sfd,buf,len);
		//			len=strlen(buf)-3;
		//			send_n(sfd,&len,4);
		//			send_n(sfd,&buf[3],len);
		//		}else{
		len=strlen(buf);
		printf("buf=%s,len=%d\n",buf,len);
		send_n(sfd,&len,4);
		send_n(sfd,buf,len);
		//		}
		printf("command committed:buf=%s\n",buf);

		if(buf[0]=='g'){
			scanf("%s",buf);
			len=strlen(buf)+1;
			printf("buf=%s,len=%d\n",buf,len);
			send_n(sfd,&len,4);
			send_n(sfd,buf,len);
			printf("command committed:buf=%s\n",buf);
			
			int fd=open(buf,O_RDWR|O_CREAT,0666);
			if(fd==-1){
				perror("open");
				continue;
			}
			recv_train(sfd,fd);
			continue;
		}

		if(buf[1]=='u'){
			scanf("%s",buf);
			len=strlen(buf)+1;
			printf("buf=%s,len=%d\n",buf,len);
			send_n(sfd,&len,4);
			send_n(sfd,buf,len);
			printf("command committed:buf=%s\n",buf);

			int fd=open(buf,O_RDWR,0666);
			send_train(sfd,fd);

			len=0;
			send_n(sfd,&len,4);
			continue;
		}


		while(1){
			recv_n(sfd,&len,4);
			memset(buf,0,sizeof(buf));
			if(len>0){
				recv_n(sfd,buf,len);
				write(STDOUT_FILENO,buf,len);
			}else{break;}
		}
	}





	//	close(fd);
	close(sfd);
}
