/*
 *  File name:      savitr.h
 *  Author(s):      Team ApBash [Aravind S (EE14B012), Aditya Pradeep (EE14B068)]
 *  Synopsis:       Declaration of all Savitr encryption/decryption functions and some useful macros
 */

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

// Encryption and decryption of one block, given round keys.
void savitr_encrypt(const u8 *in, u8 *out, const u32 *keys);
void savitr_decrypt(const u8 *in, u8 *out, const u32 *keys);

// Full ECB mode encryption/decryption.
void savitr_ecb_encrypt(u8 *in, u8 *out, const u32 *keys, u32 size);
void savitr_ecb_decrypt(u8 *in, u8 *out, const u32 *keys, u32 size);

/*
 *	Platform-dependent utility macro definitions.
 *
 *	SWAP(x)			:	helper for correct implementation of GETU32() and PUTU32() on Windows-based platforms.
 *	GETU32(p)		:	reads one u32 stored at starting address "p".
 *	PUTU32(ct, st)	:	stores the u32 "st" in the location starting at address "ct"
 *
 *	ROT_R8(x)		:	1-byte right-rotation of "x"
 *	ROT_16(x)		:	2-byte rotation of "x" (assumed 32-bit, otherwise it's a 2-byte *right* rotation)
 *	ROT_L8(x)		:	1-byte left-rotation of "x" (if 32-bit, same as 3-byte right-rotation)
 */
#if defined(_MSC_VER)
// Windows-based platform
# include <windows.h>	// for malloc()
# define SWAP(x) (_lrotl(x, 8) & 0x00ff00ff | _lrotr(x, 8) & 0xff00ff00)
# define GETU32(p) SWAP(*((u32 *)(p)))
# define PUTU32(ct, st) { *((u32 *)(ct)) = SWAP((st)); }
# define ROT_R8(x)	_lrotr(x, 8)
# define ROT_16(x)	_lrotr(x, 16)
# define ROT_L8(x)	_lrotl(x, 8)

#else
// Linux-based platform
# define GETU32(pt) (((u32)(pt)[0] << 24) ^ ((u32)(pt)[1] << 16) ^ ((u32)(pt)[2] <<  8) ^ ((u32)(pt)[3]))
# define PUTU32(ct, st) { (ct)[0] = (u8)((st) >> 24); (ct)[1] = (u8)((st) >> 16); (ct)[2] = (u8)((st) >>  8); (ct)[3] = (u8)(st); }
# define ROT_R8(x)	( (0x00ffffff & ((x) >>  8)) | (0xff000000 & ((x) << 24)) )
# define ROT_16(x)	( (0x0000ffff & ((x) >> 16)) | (0xffff0000 & ((x) << 16)) )
# define ROT_L8(x)	( (0xffffff00 & ((x) <<  8)) | (0x000000ff & ((x) >> 24)) )

#endif

#ifdef __cplusplus
}
#endif

#endif	/* HEADER_SAVITR */