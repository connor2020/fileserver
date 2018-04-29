///
/// @file    finddir.c
/// @author  haozhipeng(1152699659@qq.com)
/// @date    2017-02-18 22:41:56
///

#include<sys/types.h>
#include<dirent.h>
#include<stdio.h>
#include<string.h>

void printdir(char* outbuf,char* path,int width){
	DIR* dir;
	dir=opendir(path);
	if(NULL==dir){
		perror("opendir");
		return;
	}
	struct dirent* p;
	char buf[200];
	while((p=readdir(dir))!=NULL){
		if(!strcmp(p->d_name,".")||!strcmp(p->d_name,"..")){
		}else{
			sprintf(&outbuf[strlen(outbuf)],"%*s%s\n",width,"",p->d_name);
			if(p->d_type==4){
				sprintf(buf,"%s%s%s",path,"/",p->d_name);
				printdir(outbuf,buf,width+4);
			}
		}
	}

//	puts("-----------------");
//	puts(path);	
//	puts(outbuf);
}


