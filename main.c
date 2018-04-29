 ///
 /// @file    main.c
 /// @author  haozhipeng(1152699659@qq.com)
 /// @date    2017-02-12 20:15:28
 ///
#include"func.h"

int main(int argc,char** argv){
	if(argc!=1){
		printf("error args\n");
		return -1;
	}
	puts(argv[0]);
	int count=atoi("2");
	pcdata p=(pcdata)calloc(count,sizeof(cdata));
	make_child(p,count);
	int sfd=socket(AF_INET,SOCK_STREAM,0);
	if(-1==sfd){
		perror("socket");
		return -1;
	}  
	set_init(sfd,IP,PORT);
	listen(sfd,count);
	int epfd=epoll_create(1);
	struct epoll_event event,*evs;
	evs=(struct epoll_event*)calloc(count+1,sizeof(event));
	memset(&event,0,sizeof(event));
	event.events=EPOLLIN;
	event.data.fd=sfd;
	int ret=epoll_ctl(epfd,EPOLL_CTL_ADD,sfd,&event);
	if(-1==ret){
		perror("epoll_ctl");
		return -1;
	}
	int i;
	for(i=0;i<count;i++){
		event.events=EPOLLIN;
		event.data.fd=p[i].fdw;
		epoll_ctl(epfd,EPOLL_CTL_ADD,p[i].fdw,&event);
	}
	int j,ret1,new_fd;
	short flag;

	struct sockaddr_in cli;
	socklen_t addrlen=sizeof(struct sockaddr);;
	while(1){
//		memset(evs,0,(count+1)*sizeof(event));
		ret1=epoll_wait(epfd,evs,count+1,-1);
		if(ret1>0){
			for(i=0;i<ret1;i++){
				if(evs[i].data.fd==sfd){
					memset(&cli,0,sizeof(cli));
					new_fd=accept(sfd,(struct sockaddr*)&cli,&addrlen);
//					puts("sleep");
//					sleep(1);
					printf("client connected:%s:%d\n",inet_ntoa(cli.sin_addr),ntohs(cli.sin_port));
					for(j=0;j<count;j++){
						if(p[j].busy==0){
							send_fd(p[j].fdw,new_fd);
							p[j].busy=1;
							break;
						}
					}
					close(new_fd);
				}
				for(j=0;j<count;j++){
					if(evs[i].data.fd==p[j].fdw){
						read(p[j].fdw,&flag,sizeof(flag));
						p[j].busy=0;
						printf("misson complete\n");
						break;
					}
				}
			}
		}
	}
	close(sfd);
	close(epfd);
	return 0;
}
