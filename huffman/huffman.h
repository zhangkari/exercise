#ifndef __HUFFMAN__H__
#define __HUFFMAN__H__

typedef int int32;
typedef unsigned char uint8;
typedef unsigned int uint32;

int hfm_compress_file(const char* fnread, const char* fnwrite);
int hfm_decompress_file(const char* fnread, const char* fnwrite);
int hfm_compress_mem(const uint8* src, uint32 slen, uint8* dst, uint32* dlen);
int hfm_decompress_mem(const uint8* src, uint32 slen, uint8* dst, uint32* dlen);

#endif
