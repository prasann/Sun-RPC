#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>
#include "filerpc.h"

static int O_RDONLY = 1;
static int O_WRONLY = 2;

handle rget( CLIENT *client,char *remote_file_name,char *local_file_name){
	openargs open_args;
	open_args.file=remote_file_name;
	open_args.mode=O_RDONLY;
	handle *result; 
	result = open_1(&open_args,client); 
	readargs read_args;     
	read_args.h = *result;
	read_args.nbytes=MAXBUF;   
	readresults *read_results;
	read_results = read_1(&read_args, client);
	if(read_results->status==0){
		FILE *file;
		file = fopen(local_file_name,"w+");
		fwrite((read_results -> readresults_u.buf.buf_val),(read_results -> readresults_u.buf.buf_len),1,file);
		printf("Success");
    }else{
		printf("Failure");
		exit(1);
    } 
	close_1(result,client);
	return(*result);
}

int main(int argc, char *argv[]){
	if (argc != 4){ 
	    printf("You must enter: ./rget remote-host remote-filename local-filename \n"); 
	    exit(1); 
	}
	
	if(strlen(argv[2]) > MAXNAME  || strlen(argv[3]) > MAXNAME ){
		exit(1); 
	} 
	
	CLIENT *client;                                                 
	client = clnt_create(argv[1], FRPC_PROG, FRPC_VERS, "udp");
	
	if (client == (CLIENT *) NULL) {
		clnt_pcreateerror(argv[1]);
		exit(1);
	}
	int fileCount=rget(client,argv[2],argv[3]);
	if(fileCount>=10){
		fprintf(stderr,"Maximum Number File Opened\n");	
		exit(1);
	}
	return 0;
}