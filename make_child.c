 ///
 /// @file    make_child.c
 /// @author  haozhipeng(1152699659@qq.com)
 /// @date    2017-02-12 22:15:26
 ///
#include"func.h"

void handle_request(int fdr){
	int new_fd;
	short flag=1;
	
	int len;
	char com[100]={0};
	char outbuf[1000]={0};
	while(1){
		recv_fd(fdr,&new_fd);
		printf("new_fd recived by child,fdNO.:%d\n",new_fd);
//		send_file(new_fd);

		while(1){
//			memset(com,0,sizeof(com));
			memset(com,0,100);
			memset(outbuf,0,1000);
			if(0==recv(new_fd,&len,4,0))
				break;
//			recv_n(new_fd,&len,4);
			recv_n(new_fd,com,len);
			printf("com=%s\n",com);
			switch(com[0]){
				case 'l':{
							 
							 printdir(outbuf,getcwd(NULL,0),0);
							 len=strlen(outbuf);
							 send_n(new_fd,&len,4);
							 send_n(new_fd,outbuf,len);
							 len=0;
							 send_n(new_fd,&len,4);
							 break;
						 }
				case 'p':{
							if(com[1]=='u'){

							recv_n(new_fd,&len,4);
							recv_n(new_fd,com,len);

							printf("puts:len=%d\n",len);
							printf("puts:%s\n",com);
							//rmdir(com);

							int fd=open(com,O_RDWR|O_CREAT,0666);

							recv_train(new_fd,fd);

					//		len=0;
					//		send_n(new_fd,&len,4);
							break;
							}
						}


			//pwd				 
							 {
							 sprintf(outbuf,"%s\n",getcwd(NULL,0));
							 len=strlen(outbuf);
							 send_n(new_fd,&len,4);
							 send_n(new_fd,outbuf,len);
							 len=0;
							 send_n(new_fd,&len,4);
							 break;
							 }
							 
				case 'c':{
							len=0;
							send_n(new_fd,&len,4);

							recv_n(new_fd,&len,4);
							printf("chdir:len=%d\n",len);
							memset(com,0,sizeof(com));
							recv_n(new_fd,com,len);
							printf("chdir:%s\n",com);
							chdir(com);
							len=0;
							send_n(new_fd,&len,4);
							break;
						 }
				case 'r':{
							 len=0;
							 send_n(new_fd,&len,4);

							recv_n(new_fd,&len,4);
							printf("remove:len=%d\n",len);
							memset(com,0,sizeof(com));
							recv_n(new_fd,com,len);
							printf("remove:%s\n",com);
							if(-1==remove(com)){
								perror("remove");
								strcpy(outbuf,"error remove");
								send_n(new_fd,outbuf,strlen(outbuf));
							}
							
							len=0;
							send_n(new_fd,&len,4);
							break;
						 }
				case 'g':{

							recv_n(new_fd,&len,4);
							recv_n(new_fd,com,len);

							printf("gets:len=%d\n",len);
							printf("gets:%s\n",com);
						//	rmdir(com);
							int fd=open(com,O_RDWR,0666);

							send_train(new_fd,fd);

							len=0;
							send_n(new_fd,&len,4);
							break;
						 }
		}
	}
		write(fdr,&flag,sizeof(flag));
		close(new_fd);
}
}

void make_child(pcdata p,int count){
	int fds[2];
	int i;
	pid_t pid;
	for(i=0;i<count;i++){
		socketpair(AF_LOCAL,SOCK_STREAM,0,fds);
		pid=fork();
		if(!pid){
			close(fds[1]);
			handle_request(fds[0]);
		}
		p[i].pid=pid;
		p[i].fdw=fds[1];
		p[i].busy=0;
		close(fds[0]);
	}
}
