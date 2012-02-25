/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "filerpc.h"

/* Default timeout can be changed using clnt_control() */
static struct timeval TIMEOUT = { 25, 0 };

handle *
open_1(argp, clnt)
	openargs *argp;
	CLIENT *clnt;
{
	static handle clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call(clnt, OPEN, xdr_openargs, argp, xdr_handle, &clnt_res, TIMEOUT) != RPC_SUCCESS)
		return (NULL);
	return (&clnt_res);
}

bool_t *
close_1(argp, clnt)
	handle *argp;
	CLIENT *clnt;
{
	static bool_t clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call(clnt, CLOSE, xdr_handle, argp, xdr_bool, &clnt_res, TIMEOUT) != RPC_SUCCESS)
		return (NULL);
	return (&clnt_res);
}

readresults *
read_1(argp, clnt)
	readargs *argp;
	CLIENT *clnt;
{
	static readresults clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call(clnt, READ, xdr_readargs, argp, xdr_readresults, &clnt_res, TIMEOUT) != RPC_SUCCESS)
		return (NULL);
	return (&clnt_res);
}

writeresults *
write_1(argp, clnt)
	writeargs *argp;
	CLIENT *clnt;
{
	static writeresults clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call(clnt, WRITE, xdr_writeargs, argp, xdr_writeresults, &clnt_res, TIMEOUT) != RPC_SUCCESS)
		return (NULL);
	return (&clnt_res);
}
