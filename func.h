 ///
 /// @file    func.h
 /// @author  haozhipeng(1152699659@qq.com)
 /// @date    2017-02-12 18:39:01
 ///
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/uio.h>
#include<sys/socket.h>
#include<string.h>
#include<sys/epoll.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#include<sys/time.h>
#include<dirent.h>
#include<time.h>
#include<pwd.h>
#include<grp.h>
#include<pthread.h>


#define FILENAME "file"
#define IP "192.168.245.128"
#define PORT "8080"

typedef struct first_send_sym{
	int num;
	char buf[100];
}Fss,*pFss;
typedef struct childdata{
	pid_t pid;
	int fdw;
	short busy;
}cdata,*pcdata;
typedef struct tdata{
	int len;
	char buf[1000];
}td,*ptd;
void set_init(int,const char*,const char*);
void send_fd(int,int);
void recv_fd(int,int*);

void make_child(pcdata,int);
void send_file(int);

void send_n(int,void*,int);
void recv_n(int,void*,int);

void printdir(char*,char*,int);

void send_train(int,int);
void recv_train(int,int);

