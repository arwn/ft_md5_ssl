/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awindham <awindham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 13:09:23 by zfaria            #+#    #+#             */
/*   Updated: 2019/03/12 13:34:39 by awindham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_H
#define MD5_H

typedef struct
{
	unsigned int count[2];
	unsigned int state[4];
	unsigned char buffer[64];   
} MD5_CTX;


#define F(x,y,z) ((x & y) | (~x & z))
#define G(x,y,z) ((x & z) | (y & ~z))
#define H(x,y,z) (x^y^z)
#define I(x,y,z) (y ^ (x | ~z))
#define ROTATE_LEFT(x,n) ((x << n) | (x >> (32-n)))

#define FF(a,b,c,d,x,s,ac) \
{ \
	a += F(b,c,d) + x + ac; \
	a = ROTATE_LEFT(a,s); \
	a += b; \
}
#define GG(a,b,c,d,x,s,ac) \
{ \
	a += G(b,c,d) + x + ac; \
	a = ROTATE_LEFT(a,s); \
	a += b; \
}
#define HH(a,b,c,d,x,s,ac) \
{ \
	a += H(b,c,d) + x + ac; \
	a = ROTATE_LEFT(a,s); \
	a += b; \
}
#define II(a,b,c,d,x,s,ac) \
{ \
	a += I(b,c,d) + x + ac; \
	a = ROTATE_LEFT(a,s); \
	a += b; \
}

# define F0	FF(a, b, c, d, x[0], 7, 0xd76aa478);
# define F1	F0; FF(d, a, b, c, x[1], 12, 0xe8c7b756);
# define F2	F1; FF(c, d, a, b, x[2], 17, 0x242070db);
# define F3	F2; FF(b, c, d, a, x[3], 22, 0xc1bdceee);
# define F4	F3; FF(a, b, c, d, x[4], 7, 0xf57c0faf);
# define F5	F4; FF(d, a, b, c, x[5], 12, 0x4787c62a);
# define F6	F5; FF(c, d, a, b, x[6], 17, 0xa8304613);
# define F7	F6; FF(b, c, d, a, x[7], 22, 0xfd469501);
# define F8	F7; FF(a, b, c, d, x[8], 7, 0x698098d8);
# define F9	F8; FF(d, a, b, c, x[9], 12, 0x8b44f7af);
# define F10 F9; FF(c, d, a, b, x[10], 17, 0xffff5bb1);
# define F11 F10; FF(b, c, d, a, x[11], 22, 0x895cd7be);
# define F12 F11; FF(a, b, c, d, x[12], 7, 0x6b901122);
# define F13 F12; FF(d, a, b, c, x[13], 12, 0xfd987193);
# define F14 F13; FF(c, d, a, b, x[14], 17, 0xa679438e);
# define F15 F14; FF(b, c, d, a, x[15], 22, 0x49b40821);
# define G0	F15; GG(a, b, c, d, x[1], 5, 0xf61e2562);
# define G1	G0; GG(d, a, b, c, x[6], 9, 0xc040b340);
# define G2	G1; GG(c, d, a, b, x[11], 14, 0x265e5a51);
# define G3	G2; GG(b, c, d, a, x[0], 20, 0xe9b6c7aa);
# define G4	G3; GG(a, b, c, d, x[5], 5, 0xd62f105d);
# define G5	G4; GG(d, a, b, c, x[10], 9, 0x2441453);
# define G6	G5; GG(c, d, a, b, x[15], 14, 0xd8a1e681);
# define G7	G6; GG(b, c, d, a, x[4], 20, 0xe7d3fbc8);
# define G8	G7; GG(a, b, c, d, x[9], 5, 0x21e1cde6);
# define G9	G8; GG(d, a, b, c, x[14], 9, 0xc33707d6);
# define G10 G9; GG(c, d, a, b, x[3], 14, 0xf4d50d87);
# define G11 G10; GG(b, c, d, a, x[8], 20, 0x455a14ed);
# define G12 G11; GG(a, b, c, d, x[13], 5, 0xa9e3e905);
# define G13 G12; GG(d, a, b, c, x[2], 9, 0xfcefa3f8);
# define G14 G13; GG(c, d, a, b, x[7], 14, 0x676f02d9);
# define G15 G14; GG(b, c, d, a, x[12], 20, 0x8d2a4c8a);
# define H0	G15; HH(a, b, c, d, x[5], 4, 0xfffa3942);
# define H1	H0; HH(d, a, b, c, x[8], 11, 0x8771f681);
# define H2	H1; HH(c, d, a, b, x[11], 16, 0x6d9d6122);
# define H3	H2; HH(b, c, d, a, x[14], 23, 0xfde5380c);
# define H4	H3; HH(a, b, c, d, x[1], 4, 0xa4beea44);
# define H5	H4; HH(d, a, b, c, x[4], 11, 0x4bdecfa9);
# define H6	H5; HH(c, d, a, b, x[7], 16, 0xf6bb4b60);
# define H7	H6; HH(b, c, d, a, x[10], 23, 0xbebfbc70);
# define H8	H7; HH(a, b, c, d, x[13], 4, 0x289b7ec6);
# define H9	H8; HH(d, a, b, c, x[0], 11, 0xeaa127fa);
# define H10 H9; HH(c, d, a, b, x[3], 16, 0xd4ef3085);
# define H11 H10; HH(b, c, d, a, x[6], 23, 0x4881d05);
# define H12 H11; HH(a, b, c, d, x[9], 4, 0xd9d4d039);
# define H13 H12; HH(d, a, b, c, x[12], 11, 0xe6db99e5);
# define H14 H13; HH(c, d, a, b, x[15], 16, 0x1fa27cf8);
# define H15 H14; HH(b, c, d, a, x[2], 23, 0xc4ac5665);
# define I0	H15; II(a, b, c, d, x[0], 6, 0xf4292244);
# define I1	I0; II(d, a, b, c, x[7], 10, 0x432aff97);
# define I2	I1; II(c, d, a, b, x[14], 15, 0xab9423a7);
# define I3	I2; II(b, c, d, a, x[5], 21, 0xfc93a039);
# define I4	I3; II(a, b, c, d, x[12], 6, 0x655b59c3);
# define I5	I4; II(d, a, b, c, x[3], 10, 0x8f0ccc92);
# define I6	I5; II(c, d, a, b, x[10], 15, 0xffeff47d);
# define I7	I6; II(b, c, d, a, x[1], 21, 0x85845dd1);
# define I8	I7; II(a, b, c, d, x[8], 6, 0x6fa87e4f);
# define I9	I8; II(d, a, b, c, x[15], 10, 0xfe2ce6e0);
# define I10 I9; II(c, d, a, b, x[6], 15, 0xa3014314);
# define I11 I10; II(b, c, d, a, x[13], 21, 0x4e0811a1);
# define I12 I11; II(a, b, c, d, x[4], 6, 0xf7537e82);
# define I13 I12; II(d, a, b, c, x[11], 10, 0xbd3af235);
# define I14 I13; II(c, d, a, b, x[2], 15, 0x2ad7d2bb);
# define I15 I14; II(b, c, d, a, x[9], 21, 0xeb86d391);
# define FUN I15;

void md5_init(MD5_CTX *context);
void md5_update(MD5_CTX *context, unsigned char *input, unsigned int inputlen);
void md5_final(MD5_CTX *context, unsigned char digest[16]);
void md5_transform(unsigned int state[4], unsigned char block[64]);
void md5_encode(unsigned char *output, unsigned int *input, unsigned int len);
void md5_decode(unsigned int *output, unsigned char *input, unsigned int len);

#endif

