 ///
 /// @file    set_init.c
 /// @author  haozhipeng(1152699659@qq.com)
 /// @date    2017-02-12 20:01:21
 ///
#include"func.h"

void set_init(int sfd,const char* ip,const char* port){
	struct sockaddr_in ser;
	memset(&ser,0,sizeof(ser));
	ser.sin_family=AF_INET;
	ser.sin_port=htons(atoi(port));
	ser.sin_addr.s_addr=inet_addr(ip);
	int ret=bind(sfd,(struct sockaddr*)&ser,sizeof(ser));
	if(-1==ret){
		perror("bind");
		return;
	}
}
