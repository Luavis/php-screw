#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>

#define OUTBUFSIZ  100000

z_stream z;
char outbuf[OUTBUFSIZ];

char *zcodecom(int mode, char *inbuf, int inbuf_len, int *resultbuf_len)
{
    int count, status;
    char *resultbuf;
    int total_count = 0;

    z.zalloc = Z_NULL;
    z.zfree = Z_NULL;
    z.opaque = Z_NULL;

    z.next_in = Z_NULL;
    z.avail_in = 0;
    if (mode == 0) {
	deflateInit(&z, 1);
    } else {
	inflateInit(&z);
    }

    z.next_out = outbuf;
    z.avail_out = OUTBUFSIZ;
    z.next_in = inbuf;
    z.avail_in = inbuf_len;

    resultbuf = malloc(OUTBUFSIZ);

    while (1) {
	if (mode == 0) {
		status = deflate(&z, Z_FINISH);
	} else {
		status = inflate(&z, Z_NO_FLUSH);
	}
        if (status == Z_STREAM_END) break;
        if (status != Z_OK) {
	    if (mode == 0) {
		deflateEnd(&z);
	    } else {
		inflateEnd(&z);
	    }
	    *resultbuf_len = 0;
	    return(resultbuf);
	}
        if (z.avail_out == 0) {
	    resultbuf = realloc(resultbuf, total_count + OUTBUFSIZ);
	    memcpy(resultbuf + total_count, outbuf, OUTBUFSIZ);
	    total_count += OUTBUFSIZ;
            z.next_out = outbuf;
            z.avail_out = OUTBUFSIZ;
        }
    }
    if ((count = OUTBUFSIZ - z.avail_out) != 0) {
	resultbuf = realloc(resultbuf, total_count + OUTBUFSIZ);
	memcpy(resultbuf + total_count, outbuf, count);
	total_count += count;
    }
    if (mode == 0) {
	deflateEnd(&z);
    } else {
	inflateEnd(&z);
    }
    *resultbuf_len = total_count;
    return(resultbuf);
}

char *zencode(char *inbuf, int inbuf_len, int *resultbuf_len)
{
	return zcodecom(0, inbuf, inbuf_len, resultbuf_len);
}

char *zdecode(char *inbuf, int inbuf_len, int *resultbuf_len)
{
	return zcodecom(1, inbuf, inbuf_len, resultbuf_len);
}
