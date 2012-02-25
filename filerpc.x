const MAXNAME = 128;              	 	/* max length of file name */
const MAXBUF = 512;                		/* max size of read/write buffer */

typedef string filename<MAXNAME>;  	/* filename type */
typedef int handle;               			/* remote file handle type */

struct openargs {      			/* parameters for open */
	filename file;
	int mode;
};

struct readargs {       			/* parameters for read */
	handle h;
	int nbytes;
};

union readresults switch(int status) {     	/* return values from read */
	case 0: opaque buf<MAXBUF>;
	case 1: int error; 
};

struct writeargs {     			/* parameters for write */
	handle h;
	opaque buf<MAXBUF>;
};

union writeresults switch(int status) {    	/* return values from write */
	case 0: int nbytes;
	case 1: int error;
};


program FRPC_PROG {
	version FRPC_VERS {
		handle OPEN(openargs)  = 1;        	/* open file */
		bool CLOSE(handle)  = 2;          	 /* close file */
		readresults READ(readargs) = 3;   	 /* read bytes */
		writeresults WRITE(writeargs) = 4;	 /* write bytes */
	} = 1;
} = 0x13451111;
