#ifndef HEADER_SAVITR
#define HEADER_SAVITR

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned long u32;
typedef unsigned short u16;
typedef unsigned char u8;

#ifdef __cplusplus
extern "C" {
#endif

void savitr_encrypt(const u8 *in, u8 *out, const u32 *keys);
void savitr_decrypt(const u8 *in, u8 *out, const u32 *keys);

// util functions, copied from aes_locl.h
#if defined(_MSC_VER)
# define SWAP(x) (_lrotl(x, 8) & 0x00ff00ff | _lrotr(x, 8) & 0xff00ff00)
# define GETU32(p) SWAP(*((u32 *)(p)))
# define PUTU32(ct, st) { *((u32 *)(ct)) = SWAP((st)); }
/*# define ROT_R(x, n)	_lrotr((x), (n))
# define ROT_L(x, n)	_lrotl((x), (n))*/
# define ROT_R8(x)	_lrotr(x, 8)
# define ROT_R16(x)	_lrotr(x, 16)
# define ROT_L8(x)	_lrotl(x, 8)
# define ROT_L16(x)	_lrotl(x, 16)
#else
# define GETU32(pt) (((u32)(pt)[0] << 24) ^ ((u32)(pt)[1] << 16) ^ ((u32)(pt)[2] <<  8) ^ ((u32)(pt)[3]))
# define PUTU32(ct, st) { (ct)[0] = (u8)((st) >> 24); (ct)[1] = (u8)((st) >> 16); (ct)[2] = (u8)((st) >>  8); (ct)[3] = (u8)(st); }
# define ROT_R8(x)	( (0x00ffffff & ((x) >>  8)) | (0xff000000 & ((x) << 24)) )
# define ROT_16(x)	( (0x0000ffff & ((x) >> 16)) | (0xffff0000 & ((x) << 16)) )
# define ROT_L8(x)	( (0xffffff00 & ((x) <<  8)) | (0x000000ff & ((x) >> 24)) )
#endif

/*#ifndef __linux__
# define ROT_R(x, n)	(( (x) >> (n) ) | ( (x) << (32 - (n)) ))
# define ROT_L(x, n)	(( (x) << (n) ) | ( (x) >> (32 - (n)) ))
#else
# define ROT_R(x, n)	_lrotr((x), (n))
# define ROT_L(x, n)	_lrotl((x), (n))
#endif*/

#ifdef __cplusplus
}
#endif

#endif	/* HEADER_SAVITR */