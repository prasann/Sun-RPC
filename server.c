#include <stdio.h>
#include "filerpc.h"
struct file_handler_table{
	handle handler_index;
	FILE *file_pointer ;
	}handler_array[10]; 
	
typedef struct file_handler_table HANDLERS; 
   
handle *open_1_svc(openargs *open_args, struct svc_req *rqstp)
{   
	int index = get_next_free_handler();
	if(index == -1){
		return (handle*)-1;
	}
	HANDLERS handler;
	handler.handler_index = index; 
	if((open_args->mode)==2){
		handler.file_pointer  = fopen(open_args -> file,"w+") ; 
	}else if((open_args->mode)==1){
		handler.file_pointer  = fopen(open_args -> file,"a+") ; 
	} 
	handler_array[index] = handler; 
	return &handler_array[index].handler_index;
}  

bool_t *close_1_svc(handle *index, struct svc_req *rqstp)
{   
	FILE *fp = handler_array[*index].file_pointer; 
	handler_array[*index].file_pointer = NULL;
	if (fclose(fp) != -1){
		return (bool_t *)(FALSE);
	}
	return (bool_t *)(TRUE);	
}

readresults *read_1_svc(readargs *read_args, struct svc_req *svc_req)
{   
	handle read_handler_index = read_args -> h;
	FILE *file;
	file = handler_array[read_handler_index].file_pointer;  
	readresults read_results;
	read_results.status=-1;
	if(file != NULL){
		read_results.readresults_u.buf.buf_val = (char*) malloc (sizeof(char)*MAXBUF );
		read_results.readresults_u.buf.buf_len = fread(read_results.readresults_u.buf.buf_val,1,MAXBUF,file);
		read_results.status=0;
		fclose(file);  
	}
	return (&read_results);	
}

writeresults *write_1_svc(writeargs *write_args, struct svc_req *svc_req){
	handle write_handler_index = write_args -> h;
	FILE *file = handler_array[write_handler_index].file_pointer;  
	writeresults write_results;
	write_results.status=-1;
	if(file != NULL){
		fwrite((write_args -> buf.buf_val),(write_args -> buf.buf_len),1,file);
		write_results.status=0;
	}
	return &write_results;
}

int get_next_free_handler(){
	int i=0;
	for(i=0;i<10;i++){
		if((&handler_array[i]) -> file_pointer == NULL){
		  return i;
		}	
	}
	return -1; 
}