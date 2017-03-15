#include "savitr.h"

static const u8 S[256] =
{
    0xfdU,0x6aU,0x92U,0x48U,0x4aU,0xa9U,0x27U,0x91U,0x82U,0xd9U,0x73U,0x8fU,0x90U,0xc0U,0x6fU,0x09U,
    0x42U,0x96U,0x4bU,0x5cU,0x1eU,0xe9U,0x60U,0x2eU,0xefU,0x93U,0xc7U,0xe1U,0xb4U,0x2cU,0x87U,0x40U,
    0x86U,0x69U,0xecU,0x37U,0x02U,0xb8U,0x89U,0x4dU,0x0cU,0x65U,0x53U,0xe0U,0x33U,0x31U,0x14U,0x3aU,
    0x50U,0x80U,0xcaU,0xe3U,0x44U,0xa5U,0x57U,0x1fU,0x59U,0x74U,0xb1U,0xdbU,0x64U,0x81U,0x23U,0xf1U,
    0xe4U,0xf9U,0xb7U,0x7bU,0x75U,0x79U,0x98U,0x11U,0xa6U,0xedU,0xfbU,0xbdU,0x63U,0xd8U,0x01U,0x84U,
    0xa1U,0xe6U,0x15U,0xd6U,0x0eU,0x08U,0xd7U,0x49U,0x3eU,0xa3U,0x9bU,0x24U,0xadU,0xc2U,0xbaU,0x0dU,
    0x2bU,0x0aU,0xe7U,0xb6U,0x66U,0xbbU,0xf2U,0xb3U,0x85U,0xaaU,0xd1U,0xe2U,0xa8U,0x99U,0x8cU,0x06U,
    0xafU,0x78U,0x9dU,0xeaU,0x7fU,0x29U,0xeeU,0x46U,0x95U,0xc6U,0x67U,0xb2U,0x36U,0xf6U,0x5fU,0x58U,
    0x71U,0x61U,0x5bU,0x22U,0x7cU,0x43U,0x1aU,0xc3U,0x1dU,0x8aU,0xbfU,0xd3U,0xebU,0xffU,0x8bU,0x2aU,
    0xf4U,0x6dU,0xf5U,0xb9U,0xfeU,0x0fU,0xddU,0x34U,0x16U,0x94U,0xcbU,0xabU,0x83U,0x55U,0x41U,0x4eU,
    0x77U,0x9cU,0xd4U,0x68U,0x2dU,0x3bU,0xccU,0x8eU,0x04U,0x38U,0x07U,0x88U,0x4cU,0xe5U,0xa7U,0xf8U,
    0x1cU,0x6cU,0xd2U,0xdfU,0xceU,0x5dU,0xb5U,0x19U,0xd5U,0x13U,0x62U,0xf7U,0x5eU,0xcfU,0x21U,0xc5U,
    0x32U,0x28U,0xa2U,0x39U,0x54U,0x47U,0xfcU,0xaeU,0x30U,0x9eU,0xdeU,0x10U,0x7aU,0xa4U,0xdaU,0x7eU,
    0xc1U,0x12U,0x56U,0x3dU,0x4fU,0xfaU,0x72U,0x26U,0xf3U,0x03U,0x6bU,0x35U,0x45U,0x05U,0x00U,0x25U,
    0x70U,0x52U,0x3fU,0x9fU,0xcdU,0xbeU,0x76U,0x17U,0xbcU,0x7dU,0x97U,0xf0U,0xd0U,0x8dU,0x20U,0xa0U,
    0xc9U,0xc8U,0xc4U,0x0bU,0xb0U,0x1bU,0x5aU,0xe8U,0x18U,0x6eU,0xdcU,0x3cU,0xacU,0x9aU,0x2fU,0x51U
};

// static const u32 Te[256]
// static const u32 Td[256]

void savitr_encrypt(const u8 *in, u8 *out, const u32 *keys)
{
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

void savitr_decrypt(const u8 *in, u8 *out, const u32 *keys)
{
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