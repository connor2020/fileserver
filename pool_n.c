 ///
 /// @file    pool_n.c
 /// @author  haozhipeng(1152699659@qq.com)
 /// @date    2017-02-12 19:51:21
 ///
#include"func.h"

void send_n(int fd,void* buf0,int len){
	char* buf=(char*)buf0;
	int total=0;
	int pos;
	while(total<len){
		pos=send(fd,buf+total,len-total,0);
		total+=pos;
	}
}

void recv_n(int fd,void* buf0,int len){
	char* buf=(char*)buf0;
	int total=0;
	int pos;
	while(total<len){
		pos=recv(fd,buf+total,len-total,0);
		total+=pos;
	}
}
