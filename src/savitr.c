#include "savitr.h"

void savitr_encrypt(const u8 *in, u8 *out, const u32 *keys) {
	u32 s0, s1, s2, s3, t0, t1, t2, t3;

	assert(in && out && keys);

	/* ROUND 1 */
	s1 = GETU32(in +  8) ^ keys[ 2];
	s3 = GETU32(in     ) ^ keys[ 0];
	s0 = GETU32(in +  4) ^ keys[ 1] ^ SBOX32(s3);
	s2 = GETU32(in + 12) ^ keys[ 3] ^ SBOX32(s1);

	t0 = TE0(s0 >> 24) ^ TE1((s1 >> 16) & 0xff) ^ TE2((s2 >>  8) & 0xff) ^ TE3(s3 & 0xff);
   	t1 = TE0(s1 >> 24) ^ TE1((s2 >> 16) & 0xff) ^ TE2((s3 >>  8) & 0xff) ^ TE3(s0 & 0xff);
   	t2 = TE0(s2 >> 24) ^ TE1((s3 >> 16) & 0xff) ^ TE2((s0 >>  8) & 0xff) ^ TE3(s1 & 0xff);
   	t3 = TE0(s3 >> 24) ^ TE1((s0 >> 16) & 0xff) ^ TE2((s1 >>  8) & 0xff) ^ TE3(s2 & 0xff);
   	
   	/* ROUND 2 */
	s1 = t2 ^ keys[ 6];
	s3 = t0 ^ keys[ 4];
	s0 = t1 ^ keys[ 5] ^ SBOX32(s3);
	s2 = t3 ^ keys[ 7] ^ SBOX32(s1);

	t0 = TE0(s0 >> 24) ^ TE1((s1 >> 16) & 0xff) ^ TE2((s2 >>  8) & 0xff) ^ TE3(s3 & 0xff);
   	t1 = TE0(s1 >> 24) ^ TE1((s2 >> 16) & 0xff) ^ TE2((s3 >>  8) & 0xff) ^ TE3(s0 & 0xff);
   	t2 = TE0(s2 >> 24) ^ TE1((s3 >> 16) & 0xff) ^ TE2((s0 >>  8) & 0xff) ^ TE3(s1 & 0xff);
   	t3 = TE0(s3 >> 24) ^ TE1((s0 >> 16) & 0xff) ^ TE2((s1 >>  8) & 0xff) ^ TE3(s2 & 0xff);
   	
   	/* ROUND 3 */
	s1 = t2 ^ keys[10];
	s3 = t0 ^ keys[ 8];
	s0 = t1 ^ keys[ 9] ^ SBOX32(s3);
	s2 = t3 ^ keys[11] ^ SBOX32(s1);

	t0 = TE0(s0 >> 24) ^ TE1((s1 >> 16) & 0xff) ^ TE2((s2 >>  8) & 0xff) ^ TE3(s3 & 0xff);
   	t1 = TE0(s1 >> 24) ^ TE1((s2 >> 16) & 0xff) ^ TE2((s3 >>  8) & 0xff) ^ TE3(s0 & 0xff);
   	t2 = TE0(s2 >> 24) ^ TE1((s3 >> 16) & 0xff) ^ TE2((s0 >>  8) & 0xff) ^ TE3(s1 & 0xff);
   	t3 = TE0(s3 >> 24) ^ TE1((s0 >> 16) & 0xff) ^ TE2((s1 >>  8) & 0xff) ^ TE3(s2 & 0xff);
   	
   	/* ROUND 4 */
	s1 = t2 ^ keys[14];
	s3 = t0 ^ keys[12];
	s0 = t1 ^ keys[13] ^ SBOX32(s3);
	s2 = t3 ^ keys[15] ^ SBOX32(s1);

	t0 = TE0(s0 >> 24) ^ TE1((s1 >> 16) & 0xff) ^ TE2((s2 >>  8) & 0xff) ^ TE3(s3 & 0xff);
   	t1 = TE0(s1 >> 24) ^ TE1((s2 >> 16) & 0xff) ^ TE2((s3 >>  8) & 0xff) ^ TE3(s0 & 0xff);
   	t2 = TE0(s2 >> 24) ^ TE1((s3 >> 16) & 0xff) ^ TE2((s0 >>  8) & 0xff) ^ TE3(s1 & 0xff);
   	t3 = TE0(s3 >> 24) ^ TE1((s0 >> 16) & 0xff) ^ TE2((s1 >>  8) & 0xff) ^ TE3(s2 & 0xff);
   	
   	/* ROUND 5 */
	s1 = t2 ^ keys[18];
	s3 = t0 ^ keys[16];
	s0 = t1 ^ keys[17] ^ SBOX32(s3);
	s2 = t3 ^ keys[19] ^ SBOX32(s1);

	t0 = TE0(s0 >> 24) ^ TE1((s1 >> 16) & 0xff) ^ TE2((s2 >>  8) & 0xff) ^ TE3(s3 & 0xff);
   	t1 = TE0(s1 >> 24) ^ TE1((s2 >> 16) & 0xff) ^ TE2((s3 >>  8) & 0xff) ^ TE3(s0 & 0xff);
   	t2 = TE0(s2 >> 24) ^ TE1((s3 >> 16) & 0xff) ^ TE2((s0 >>  8) & 0xff) ^ TE3(s1 & 0xff);
   	t3 = TE0(s3 >> 24) ^ TE1((s0 >> 16) & 0xff) ^ TE2((s1 >>  8) & 0xff) ^ TE3(s2 & 0xff);
   	
   	/* ROUND 6 */
	s1 = t2 ^ keys[22];
	s3 = t0 ^ keys[20];
	s0 = t1 ^ keys[21] ^ SBOX32(s3);
	s2 = t3 ^ keys[23] ^ SBOX32(s1);

	t0 = TE0(s0 >> 24) ^ TE1((s1 >> 16) & 0xff) ^ TE2((s2 >>  8) & 0xff) ^ TE3(s3 & 0xff);
   	t1 = TE0(s1 >> 24) ^ TE1((s2 >> 16) & 0xff) ^ TE2((s3 >>  8) & 0xff) ^ TE3(s0 & 0xff);
   	t2 = TE0(s2 >> 24) ^ TE1((s3 >> 16) & 0xff) ^ TE2((s0 >>  8) & 0xff) ^ TE3(s1 & 0xff);
   	t3 = TE0(s3 >> 24) ^ TE1((s0 >> 16) & 0xff) ^ TE2((s1 >>  8) & 0xff) ^ TE3(s2 & 0xff);
   	
   	/* ROUND 7 */
	s1 = t2 ^ keys[26];
	s3 = t0 ^ keys[24];
	s0 = t1 ^ keys[25] ^ SBOX32(s3);
	s2 = t3 ^ keys[27] ^ SBOX32(s1);

	t0 = TE0(s0 >> 24) ^ TE1((s1 >> 16) & 0xff) ^ TE2((s2 >>  8) & 0xff) ^ TE3(s3 & 0xff);
   	t1 = TE0(s1 >> 24) ^ TE1((s2 >> 16) & 0xff) ^ TE2((s3 >>  8) & 0xff) ^ TE3(s0 & 0xff);
   	t2 = TE0(s2 >> 24) ^ TE1((s3 >> 16) & 0xff) ^ TE2((s0 >>  8) & 0xff) ^ TE3(s1 & 0xff);
   	t3 = TE0(s3 >> 24) ^ TE1((s0 >> 16) & 0xff) ^ TE2((s1 >>  8) & 0xff) ^ TE3(s2 & 0xff);
   	
   	/* ROUND 8 */
	s1 = t2 ^ keys[30];
	s3 = t0 ^ keys[28];
	s0 = t1 ^ keys[29] ^ SBOX32(s3);
	s2 = t3 ^ keys[31] ^ SBOX32(s1);

	t0 = TE0(s0 >> 24) ^ TE1((s1 >> 16) & 0xff) ^ TE2((s2 >>  8) & 0xff) ^ TE3(s3 & 0xff);
   	t1 = TE0(s1 >> 24) ^ TE1((s2 >> 16) & 0xff) ^ TE2((s3 >>  8) & 0xff) ^ TE3(s0 & 0xff);
   	t2 = TE0(s2 >> 24) ^ TE1((s3 >> 16) & 0xff) ^ TE2((s0 >>  8) & 0xff) ^ TE3(s1 & 0xff);
   	t3 = TE0(s3 >> 24) ^ TE1((s0 >> 16) & 0xff) ^ TE2((s1 >>  8) & 0xff) ^ TE3(s2 & 0xff);
   	
   	/* ROUND 9 */
	s1 = t2 ^ keys[34];
	s3 = t0 ^ keys[32];
	s0 = t1 ^ keys[33] ^ SBOX32(s3);
	s2 = t3 ^ keys[35] ^ SBOX32(s1);

	t0 = TE0(s0 >> 24) ^ TE1((s1 >> 16) & 0xff) ^ TE2((s2 >>  8) & 0xff) ^ TE3(s3 & 0xff);
   	t1 = TE0(s1 >> 24) ^ TE1((s2 >> 16) & 0xff) ^ TE2((s3 >>  8) & 0xff) ^ TE3(s0 & 0xff);
   	t2 = TE0(s2 >> 24) ^ TE1((s3 >> 16) & 0xff) ^ TE2((s0 >>  8) & 0xff) ^ TE3(s1 & 0xff);
   	t3 = TE0(s3 >> 24) ^ TE1((s0 >> 16) & 0xff) ^ TE2((s1 >>  8) & 0xff) ^ TE3(s2 & 0xff);
   	
   	/* ROUND 10 - FINAL */
	s1 = t2 ^ keys[38];
	s3 = t0 ^ keys[36];
	s0 = t1 ^ keys[37] ^ SBOX32(s3);
	s2 = t3 ^ keys[39] ^ SBOX32(s1);

	t0 = TE0(s0 >> 24) ^ TE1((s1 >> 16) & 0xff) ^ TE2((s2 >>  8) & 0xff) ^ TE3(s3 & 0xff);
   	t1 = TE0(s1 >> 24) ^ TE1((s2 >> 16) & 0xff) ^ TE2((s3 >>  8) & 0xff) ^ TE3(s0 & 0xff);
   	t2 = TE0(s2 >> 24) ^ TE1((s3 >> 16) & 0xff) ^ TE2((s0 >>  8) & 0xff) ^ TE3(s1 & 0xff);
   	t3 = TE0(s3 >> 24) ^ TE1((s0 >> 16) & 0xff) ^ TE2((s1 >>  8) & 0xff) ^ TE3(s2 & 0xff);
   	
   	/* all rounds over, writing to final output */
   	PUTU32(out     , t0);
   	PUTU32(out +  4, t1);
   	PUTU32(out +  8, t2);
   	PUTU32(out + 12, t3);
}

void savitr_decrypt(const u8 *in, u8 *out, const u32 *keys) {
	u32 s0, s1, s2, s3, t0, t1, t2, t3;

	assert(in && out && keys);

	// initialization
	t0 = GETU32(in     );
	t1 = GETU32(in +  4);
	t2 = GETU32(in +  8);
	t3 = GETU32(in + 12);

	/* ROUND 1 */
	s0 = TD0(t0 >> 24) ^ TD1((t3 >> 16) & 0xff) ^ TD2((t2 >>  8) & 0xff) ^ TD3(t1 & 0xff);
    s1 = TD0(t1 >> 24) ^ TD1((t0 >> 16) & 0xff) ^ TD2((t3 >>  8) & 0xff) ^ TD3(t2 & 0xff);
    s2 = TD0(t2 >> 24) ^ TD1((t1 >> 16) & 0xff) ^ TD2((t0 >>  8) & 0xff) ^ TD3(t3 & 0xff);
    s3 = TD0(t3 >> 24) ^ TD1((t2 >> 16) & 0xff) ^ TD2((t1 >>  8) & 0xff) ^ TD3(t0 & 0xff);

    t1 = s0 ^ keys[ 1] ^ SBOX32(s3);
    t3 = s2 ^ keys[ 3] ^ SBOX32(s1);
    t0 = s3 ^ keys[ 0];
    t2 = s1 ^ keys[ 2];

	/* ROUND 2 */
	s0 = TD0(t0 >> 24) ^ TD1((t3 >> 16) & 0xff) ^ TD2((t2 >>  8) & 0xff) ^ TD3(t1 & 0xff);
    s1 = TD0(t1 >> 24) ^ TD1((t0 >> 16) & 0xff) ^ TD2((t3 >>  8) & 0xff) ^ TD3(t2 & 0xff);
    s2 = TD0(t2 >> 24) ^ TD1((t1 >> 16) & 0xff) ^ TD2((t0 >>  8) & 0xff) ^ TD3(t3 & 0xff);
    s3 = TD0(t3 >> 24) ^ TD1((t2 >> 16) & 0xff) ^ TD2((t1 >>  8) & 0xff) ^ TD3(t0 & 0xff);

    t1 = s0 ^ keys[ 5] ^ SBOX32(s3);
    t3 = s2 ^ keys[ 7] ^ SBOX32(s1);
    t0 = s3 ^ keys[ 4];
    t2 = s1 ^ keys[ 6];
    
	/* ROUND 3 */
	s0 = TD0(t0 >> 24) ^ TD1((t3 >> 16) & 0xff) ^ TD2((t2 >>  8) & 0xff) ^ TD3(t1 & 0xff);
    s1 = TD0(t1 >> 24) ^ TD1((t0 >> 16) & 0xff) ^ TD2((t3 >>  8) & 0xff) ^ TD3(t2 & 0xff);
    s2 = TD0(t2 >> 24) ^ TD1((t1 >> 16) & 0xff) ^ TD2((t0 >>  8) & 0xff) ^ TD3(t3 & 0xff);
    s3 = TD0(t3 >> 24) ^ TD1((t2 >> 16) & 0xff) ^ TD2((t1 >>  8) & 0xff) ^ TD3(t0 & 0xff);

    t1 = s0 ^ keys[ 9] ^ SBOX32(s3);
    t3 = s2 ^ keys[11] ^ SBOX32(s1);
    t0 = s3 ^ keys[ 8];
    t2 = s1 ^ keys[10];
    
	/* ROUND 4 */
	s0 = TD0(t0 >> 24) ^ TD1((t3 >> 16) & 0xff) ^ TD2((t2 >>  8) & 0xff) ^ TD3(t1 & 0xff);
    s1 = TD0(t1 >> 24) ^ TD1((t0 >> 16) & 0xff) ^ TD2((t3 >>  8) & 0xff) ^ TD3(t2 & 0xff);
    s2 = TD0(t2 >> 24) ^ TD1((t1 >> 16) & 0xff) ^ TD2((t0 >>  8) & 0xff) ^ TD3(t3 & 0xff);
    s3 = TD0(t3 >> 24) ^ TD1((t2 >> 16) & 0xff) ^ TD2((t1 >>  8) & 0xff) ^ TD3(t0 & 0xff);

    t1 = s0 ^ keys[13] ^ SBOX32(s3);
    t3 = s2 ^ keys[15] ^ SBOX32(s1);
    t0 = s3 ^ keys[12];
    t2 = s1 ^ keys[14];
    
	/* ROUND 5 */
	s0 = TD0(t0 >> 24) ^ TD1((t3 >> 16) & 0xff) ^ TD2((t2 >>  8) & 0xff) ^ TD3(t1 & 0xff);
    s1 = TD0(t1 >> 24) ^ TD1((t0 >> 16) & 0xff) ^ TD2((t3 >>  8) & 0xff) ^ TD3(t2 & 0xff);
    s2 = TD0(t2 >> 24) ^ TD1((t1 >> 16) & 0xff) ^ TD2((t0 >>  8) & 0xff) ^ TD3(t3 & 0xff);
    s3 = TD0(t3 >> 24) ^ TD1((t2 >> 16) & 0xff) ^ TD2((t1 >>  8) & 0xff) ^ TD3(t0 & 0xff);

    t1 = s0 ^ keys[17] ^ SBOX32(s3);
    t3 = s2 ^ keys[19] ^ SBOX32(s1);
    t0 = s3 ^ keys[16];
    t2 = s1 ^ keys[18];
    
	/* ROUND 6 */
	s0 = TD0(t0 >> 24) ^ TD1((t3 >> 16) & 0xff) ^ TD2((t2 >>  8) & 0xff) ^ TD3(t1 & 0xff);
    s1 = TD0(t1 >> 24) ^ TD1((t0 >> 16) & 0xff) ^ TD2((t3 >>  8) & 0xff) ^ TD3(t2 & 0xff);
    s2 = TD0(t2 >> 24) ^ TD1((t1 >> 16) & 0xff) ^ TD2((t0 >>  8) & 0xff) ^ TD3(t3 & 0xff);
    s3 = TD0(t3 >> 24) ^ TD1((t2 >> 16) & 0xff) ^ TD2((t1 >>  8) & 0xff) ^ TD3(t0 & 0xff);

    t1 = s0 ^ keys[21] ^ SBOX32(s3);
    t3 = s2 ^ keys[23] ^ SBOX32(s1);
    t0 = s3 ^ keys[20];
    t2 = s1 ^ keys[22];
    
	/* ROUND 7 */
	s0 = TD0(t0 >> 24) ^ TD1((t3 >> 16) & 0xff) ^ TD2((t2 >>  8) & 0xff) ^ TD3(t1 & 0xff);
    s1 = TD0(t1 >> 24) ^ TD1((t0 >> 16) & 0xff) ^ TD2((t3 >>  8) & 0xff) ^ TD3(t2 & 0xff);
    s2 = TD0(t2 >> 24) ^ TD1((t1 >> 16) & 0xff) ^ TD2((t0 >>  8) & 0xff) ^ TD3(t3 & 0xff);
    s3 = TD0(t3 >> 24) ^ TD1((t2 >> 16) & 0xff) ^ TD2((t1 >>  8) & 0xff) ^ TD3(t0 & 0xff);

    t1 = s0 ^ keys[25] ^ SBOX32(s3);
    t3 = s2 ^ keys[27] ^ SBOX32(s1);
    t0 = s3 ^ keys[24];
    t2 = s1 ^ keys[26];
    
	/* ROUND 8 */
	s0 = TD0(t0 >> 24) ^ TD1((t3 >> 16) & 0xff) ^ TD2((t2 >>  8) & 0xff) ^ TD3(t1 & 0xff);
    s1 = TD0(t1 >> 24) ^ TD1((t0 >> 16) & 0xff) ^ TD2((t3 >>  8) & 0xff) ^ TD3(t2 & 0xff);
    s2 = TD0(t2 >> 24) ^ TD1((t1 >> 16) & 0xff) ^ TD2((t0 >>  8) & 0xff) ^ TD3(t3 & 0xff);
    s3 = TD0(t3 >> 24) ^ TD1((t2 >> 16) & 0xff) ^ TD2((t1 >>  8) & 0xff) ^ TD3(t0 & 0xff);

    t1 = s0 ^ keys[29] ^ SBOX32(s3);
    t3 = s2 ^ keys[31] ^ SBOX32(s1);
    t0 = s3 ^ keys[28];
    t2 = s1 ^ keys[30];
    
	/* ROUND 9 */
	s0 = TD0(t0 >> 24) ^ TD1((t3 >> 16) & 0xff) ^ TD2((t2 >>  8) & 0xff) ^ TD3(t1 & 0xff);
    s1 = TD0(t1 >> 24) ^ TD1((t0 >> 16) & 0xff) ^ TD2((t3 >>  8) & 0xff) ^ TD3(t2 & 0xff);
    s2 = TD0(t2 >> 24) ^ TD1((t1 >> 16) & 0xff) ^ TD2((t0 >>  8) & 0xff) ^ TD3(t3 & 0xff);
    s3 = TD0(t3 >> 24) ^ TD1((t2 >> 16) & 0xff) ^ TD2((t1 >>  8) & 0xff) ^ TD3(t0 & 0xff);

    t1 = s0 ^ keys[33] ^ SBOX32(s3);
    t3 = s2 ^ keys[35] ^ SBOX32(s1);
    t0 = s3 ^ keys[32];
    t2 = s1 ^ keys[34];
    
	/* ROUND 10 - FINAL */
	s0 = TD0(t0 >> 24) ^ TD1((t3 >> 16) & 0xff) ^ TD2((t2 >>  8) & 0xff) ^ TD3(t1 & 0xff);
    s1 = TD0(t1 >> 24) ^ TD1((t0 >> 16) & 0xff) ^ TD2((t3 >>  8) & 0xff) ^ TD3(t2 & 0xff);
    s2 = TD0(t2 >> 24) ^ TD1((t1 >> 16) & 0xff) ^ TD2((t0 >>  8) & 0xff) ^ TD3(t3 & 0xff);
    s3 = TD0(t3 >> 24) ^ TD1((t2 >> 16) & 0xff) ^ TD2((t1 >>  8) & 0xff) ^ TD3(t0 & 0xff);

    t1 = s0 ^ keys[37] ^ SBOX32(s3);
    t3 = s2 ^ keys[39] ^ SBOX32(s1);
    t0 = s3 ^ keys[36];
    t2 = s1 ^ keys[38];
    
    /* all rounds over, writing to final output */
   	PUTU32(out     , t0);
   	PUTU32(out +  4, t1);
   	PUTU32(out +  8, t2);
   	PUTU32(out + 12, t3);
}