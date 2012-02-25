/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "filerpc.h"

bool_t
xdr_filename(xdrs, objp)
	XDR *xdrs;
	filename *objp;
{

	if (!xdr_string(xdrs, objp, MAXNAME))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_handle(xdrs, objp)
	XDR *xdrs;
	handle *objp;
{

	if (!xdr_int(xdrs, objp))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_openargs(xdrs, objp)
	XDR *xdrs;
	openargs *objp;
{

	if (!xdr_filename(xdrs, &objp->file))
		return (FALSE);
	if (!xdr_int(xdrs, &objp->mode))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_readargs(xdrs, objp)
	XDR *xdrs;
	readargs *objp;
{

	if (!xdr_handle(xdrs, &objp->h))
		return (FALSE);
	if (!xdr_int(xdrs, &objp->nbytes))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_readresults(xdrs, objp)
	XDR *xdrs;
	readresults *objp;
{

	if (!xdr_int(xdrs, &objp->status))
		return (FALSE);
	switch (objp->status) {
	case 0:
		if (!xdr_bytes(xdrs, (char **)&objp->readresults_u.buf.buf_val, (u_int *)&objp->readresults_u.buf.buf_len, MAXBUF))
			return (FALSE);
		break;
	case 1:
		if (!xdr_int(xdrs, &objp->readresults_u.error))
			return (FALSE);
		break;
	default:
		return (FALSE);
	}
	return (TRUE);
}

bool_t
xdr_writeargs(xdrs, objp)
	XDR *xdrs;
	writeargs *objp;
{

	if (!xdr_handle(xdrs, &objp->h))
		return (FALSE);
	if (!xdr_bytes(xdrs, (char **)&objp->buf.buf_val, (u_int *)&objp->buf.buf_len, MAXBUF))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_writeresults(xdrs, objp)
	XDR *xdrs;
	writeresults *objp;
{

	if (!xdr_int(xdrs, &objp->status))
		return (FALSE);
	switch (objp->status) {
	case 0:
		if (!xdr_int(xdrs, &objp->writeresults_u.nbytes))
			return (FALSE);
		break;
	case 1:
		if (!xdr_int(xdrs, &objp->writeresults_u.error))
			return (FALSE);
		break;
	default:
		return (FALSE);
	}
	return (TRUE);
}