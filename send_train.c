 ///
 /// @file    send.c
 /// @author  haozhipeng(1152699659@qq.com)
 /// @date    2017-02-17 20:16:26
 ///

#include"func.h"

void send_train(int new_fd,int fd){
	td t;
	while(memset(&t,0,sizeof(t)),(t.len=read(fd,t.buf,sizeof(t.buf)))>0){
		send_n(new_fd,&t,4+t.len);
	}
}
void recv_train(int sfd,int fd){

	char buf[1000];
	int len;

	while(1){
		recv_n(sfd,&len,4);
		memset(buf,0,1000);
		if(len>0){
			recv_n(sfd,buf,len);
			write(fd,buf,len);
		}else{
			break;
		}
	}
}
