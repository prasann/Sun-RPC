#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>
#include "filerpc.h"

static int O_RDONLY = 1;
static int O_WRONLY = 2;

handle rput( CLIENT *client,char *local_file_name,char *remote_file_name){
	openargs open_args;
	open_args.file=remote_file_name;
	open_args.mode=O_WRONLY;
	handle *result;
	result = open_1(&open_args,client);
	FILE *file;
	file = fopen(local_file_name,"r+");
	writeargs write_args;
	write_args.h = *result;
	write_args.buf.buf_val = (char*) malloc (sizeof(char)*MAXBUF );
	write_args.buf.buf_len = fread (write_args.buf.buf_val,1,MAXBUF,file);
	fclose(file);
	writeresults *write_results = write_1(&write_args, client);
	if(write_results->status==0){
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
	    printf("You must enter: ./client remote-host local-filename remote-filename\n"); 
	    exit(1); 
	}
	
	
	if( strlen(argv[2]) > MAXNAME  || strlen(argv[3]) > MAXNAME ){
		printf("Error\n"); 
		exit(1); 
	} 
	
	CLIENT *client;
	client = clnt_create(argv[1], FRPC_PROG, FRPC_VERS, "tcp");
	
	if (client == (CLIENT *) NULL) {
		clnt_pcreateerror(argv[1]);
		exit(1);
	}            
	
	int fileCount=rput(client,argv[2],argv[3]);
	
	if(fileCount>=10){
		printf("Error\n");
		exit(1);
	}
	
	return 0;
}