#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <assert.h>
#include "huffman.h"

#define MAX_POOL_SIZE 32

#pragma pack(1)

typedef struct _bitpool_st
{
	uint32 data;
	uint8  len;		
}bitpool_st;

typedef struct _huff_node_st
{
	uint32 count;
	int32  lchild;
	int32  rchild;
	int32  parent;
	uint8  data;
} huff_node_st;

typedef struct _freq_node_st
{
	uint32 freq;
	uint8 data;
}freq_node_st;

typedef struct _huff_header_st
{
	char id[4] ;		//  "huff";
	uint32 node_count;	// count of freq_node_st
	uint32 offset;		// data in the offset of header 
	uint32 length;		// lengto of data
}huff_header_st;
#pragma unpack

/* initialize the pool */
static int init_bitpool(bitpool_st* pool)
{
	if(NULL == pool)
	{
		printf("ERROR: NULL pointer exception in init_bitpool().\n");
		return -1;
	}

	pool->data = 0;
	pool->len = 0;

	return 0;
}


/* set bits[pos] = 1 */
static int set_bit(bitpool_st* pool, uint8 pos)
{
	if(NULL == pool)
	{
		printf("ERROR: NULL pointer exception in push_bit_front().\n");
		return -1;
	}

	if(pos < 0 || pos > MAX_POOL_SIZE)
	{
		printf("ERROR: postion is invalid in set_bit().\n");
		return -2;
	}

	if(pos > pool->len)
	{
		printf("WARNING: position is out of pool's current length.\n");
	}

	uint32 temp = 0x01;
	temp <<= (pos - 1);
	pool->data |= temp;

	return 0;
}

/* set bits[pos] = 0 */
static int reset_bit(bitpool_st* pool, uint8 pos)
{
	if(NULL == pool)
	{
		printf("ERROR: NULL pointer exception in push_bit_front().\n");
		return -1;
	}

	if(pos < 0 || pos > MAX_POOL_SIZE)
	{
		printf("ERROR: postion is invalid in reset_bit().\n");
		return -2;
	}

	if(pos > pool->len)
	{
		printf("WARNING: position is out of pool's current length.\n");
	}

	uint32 temp = 0x01;
	temp <<= (pos - 1);
	temp = ~temp;
	pool->data &= temp;

	return 0;
}

/* push one bit to the back */
static int push_bit_back(bitpool_st* pool, uint8 bit)
{
	if(NULL == pool)
	{
		printf("ERROR: NULL pointer exception in push_bit_back().\n");
		return -1;
	}

	if(pool->len >= MAX_POOL_SIZE)
	{
		printf("ERROR: pool is full in push_bit_back().\n");
		return -2;
	}

	if(0 != bit && 1 != bit)
	{
		printf("ERROR: Invalid value, must be 0 or 1\n");
		return -3;
	}

	pool->data <<= 1;
	bit &= 0x01;
	pool->data |= bit; 
	pool->len += 1;

	return 0;
}

/* push one byte to the back */
static int push_byte_back(bitpool_st* pool, uint8 byte)
{
	if(NULL == pool)
	{
		printf("ERROR: NULL pointer exception in push_byte_back().\n");
		return -1;
	}

	if(pool->len > MAX_POOL_SIZE - 8)
	{
		printf("ERROR: pool is full in push_byte_back().\n");
		return -2;
	}

	pool->data <<= 8;
	pool->data |= byte; 
	pool->len += 8;

	return 0;
}

/* push one bit to the front */
static int push_bit_front(bitpool_st* pool, uint8 bit)
{
	if(NULL == pool)
	{
		printf("ERROR: NULL pointer exception in push_bit_front().\n");
		return -1;
	}

	if(pool->len >= MAX_POOL_SIZE)
	{
		printf("ERROR: pool is full in push_bit_front().\n");
		return -2;
	}

	if(0 != bit && 1 != bit)
	{
		printf("ERROR: Invalid value, must be 0 or 1\n");
		return -3;
	}

	pool->len += 1;
	bit ? set_bit(pool, pool->len) : reset_bit(pool, pool->len);

	return 0;
}


/* push other pool to my back */
int push_pool_back(bitpool_st* pool, const bitpool_st* sp)
{
	if(NULL == pool || NULL == sp)
	{
		printf("ERROR: Null Pointer in push_pool_back().\n");
		return -1;
	}

	pool->data <<= sp->len;
	pool->data |= sp->data;
	pool->len += sp->len;

	return 0;
}

/* fetch a byte in front */
int fetch_front_byte(bitpool_st* pool, uint8* value)
{
	if(NULL == pool)
	{
		printf("ERROR: NULL pointer exception in push_bit_front().\n");
		return -1;
	}

	if(pool->len < 8)
	{
		return -1;
	}

	uint32 temp = pool->data;
	temp >>= (pool->len - 8);
	*value = temp & 0xff;
	pool->len -= 8;	

	return 0;
}

/* fetch a bit in front */
static int fetch_front_bit(bitpool_st* pool, uint8* value)
{
	if(NULL == pool)
	{
		printf("ERROR: NULL pointer exception in push_bit_front().\n");
		return -1;
	}

	if(pool->len < 1)
	{
		return -1;
	}

	uint32 temp = pool->data;
	temp >>= (pool->len - 1);
	*value = temp & 0x01;
	pool->len -= 1;	

	return 0;
}

// select 1 node which has the smallest count and has no parent in nodes
int static select_min(huff_node_st* nodes, int count, int* pRet)
{
	if(count <= 0)
	{
		printf("ERROR: Invalid arguments.\n");
		return -1;
	}

	int index = 0;
	while(nodes[index].parent >= 0 && index < count)
	{
		++index;
	}
	*pRet = index;

	while(index < count)
	{
		if(nodes[index].parent < 0 && nodes[index].count < nodes[*pRet].count)
		{
			*pRet = index;
		}
		++index;
	}
}

// initialize huffman-tree
int static init_hfm_tree(huff_node_st *nodes, int count)
{
	int n, len, min1, min2;
	n = (count+1)/2;
	len = n;	

	huff_node_st* p = nodes;

	while(len >= 2)
	{
		select_min(nodes, n, &min1); // select from [0, n-1]
		p[n].lchild = min1;
		p[min1].parent = n; 

		select_min(nodes, n, &min2); // select from [0, n-1]
		p[n].rchild = min2;
		p[min2].parent = n; 

		p[n].count = p[min1].count + p[min2].count;

		++n;
		--len;
	}
	return 0;
}

// find the specified data(value) 's index in nodes 
int static find_index(const huff_node_st* nodes, int count, uint8 value)
{
	int i;
	for(i=0; i<count; ++i)
	{
		if(nodes[i].data == value)
			return i;
	}

	return -1;
}


// huffman-code  file
int static hfm_code_file(const huff_node_st *nodes, int count, FILE* fpRead, FILE* fpWrite)
{
	int n, k, index;
	int nRet;
	uint8 item;

	bitpool_st pool;
	init_bitpool(&pool);

	bitpool_st sp;
	init_bitpool(&sp);

	while((nRet=fread(&item, 1, 1, fpRead)))
	{	
		if(nRet != 1)
			break;

		index = find_index(nodes, count, item);
		if(index < 0)
		{
			printf("ERROR: Not find index.\n");
			return -1;
		}

		k = index;
		while( (n = nodes[k].parent) >= 0)
		{
			if(nodes[n].lchild == k)
			{
				push_bit_front(&sp, 0);
			}
			else if(nodes[n].rchild == k)
			{
				push_bit_front(&sp, 1);
			}

			k = n;
		}

		push_pool_back(&pool, &sp);
		init_bitpool(&sp);

		uint8 byteData;
		while(pool.len >= 8)
		{
			int ret = fetch_front_byte(&pool, &byteData);
			if(ret < 0)
			{
				break;
			}
			fwrite(&byteData, 1, 1,  fpWrite);
		}
	}

	int nFilling = 8 -pool.len;
	int i;
	for(i=0; i<nFilling; ++i)
	{
		push_bit_back(&pool, 0);
	}

	uint8 byteData;
	int ret = fetch_front_byte(&pool, &byteData);
	if(ret < 0)
	{
		printf("ERROR: Failed fill bits to a byte.\n");
	}

	fwrite(&byteData, 1, 1,  fpWrite);
	
	return 0;
}

// huffman-code mem 
int static hfm_code_mem(const huff_node_st *nodes, int count, const uint8* src, uint32 slen, uint8* dst, uint32* dlen)
{
	int n, k, index;
	int nRet;
	uint8 item;

	int i;
	*dlen = 0;

	bitpool_st pool;
	init_bitpool(&pool);

	bitpool_st sp;
	init_bitpool(&sp);

	for(i=0; i<slen; ++i)
	{	
		item = src[i];
		index = find_index(nodes, count, item);
		if(index < 0)
		{
			printf("ERROR: Not find index.\n");
			return -1;
		}

		k = index;
		while( (n = nodes[k].parent) >= 0)
		{
			if(nodes[n].lchild == k)
			{
				push_bit_front(&sp, 0);
			}
			else if(nodes[n].rchild == k)
			{
				push_bit_front(&sp, 1);
			}

			k = n;
		}

		push_pool_back(&pool, &sp);
		init_bitpool(&sp);

		uint8 byteData;
		while(pool.len >= 8)
		{
			int ret = fetch_front_byte(&pool, &byteData);
			if(ret < 0)
			{
				break;
			}

			memcpy(dst + *dlen, &byteData, 1);
			*dlen += 1;
		}
	}

	int nFilling = 8 -pool.len;
	for(i=0; i<nFilling; ++i)
	{
		push_bit_back(&pool, 0);
	}

	uint8 byteData;
	int ret = fetch_front_byte(&pool, &byteData);
	if(ret < 0)
	{
		printf("ERROR: Failed fill bits to a byte.\n");
	}

	memcpy(dst + *dlen, &byteData, 1);
	*dlen += 1;

	return 0;
}

// huffman-decode file
int static hfm_decode_file(const huff_node_st *nodes, int count, uint32 length, FILE* fpIn, FILE* fpOut)
{
	int nRead, n;
	uint8 byteValue;
	uint8 bit;

	int nRet;

	n = count-1; // the root node	


	bitpool_st pool;
	init_bitpool(&pool);

	while((nRead = fread(&byteValue, 1, 1, fpIn)))
	{
		if(nRead != 1)
			break;

		nRet = push_byte_back(&pool, byteValue);
		if(nRet < 0)
		{
			printf("ERROR: Failed push byte back.\n");
		}	

		while(pool.len > 0)
		{
			while(pool.len > 0 && nodes[n].lchild >= 0)
			{
				nRet = fetch_front_bit(&pool, &bit);
				if(nRet < 0)
				{
					printf("ERROR: Failed fetch_front_bit().\n");
					break;
				}

				if(bit)
				{
					n = nodes[n].rchild;
				}
				else
				{
					n = nodes[n].lchild;
				}
			}

			if(nodes[n].lchild < 0)
			{
				uint8 byteWriteData = nodes[n].data;
				fwrite(&byteWriteData, 1, 1, fpOut);
				n = count - 1;

				--length;
				if(length <= 0)
					return 0;
			}

			if(pool.len <= 0)
			{
				break;
			}
		}
	}

	return 0;
}

// huffman-decode mem
int static hfm_decode_mem(const huff_node_st *nodes, int count, const uint8* src, uint32 slen, uint32 length, uint8* dst, uint32* dlen)
{
	int nRead, n;
	uint8 byteValue;
	uint8 bit;

	int nRet;
	int i;
	*dlen = 0;

	n = count-1; // the root node	
	bitpool_st pool;
	init_bitpool(&pool);

	for(i=0; i<slen; ++i)
	{
		byteValue = src[i];
		nRet = push_byte_back(&pool, byteValue);
		if(nRet < 0)
		{
			printf("ERROR: Failed push byte back.\n");
		}	

		while(pool.len > 0)
		{
			while(pool.len > 0 && nodes[n].lchild >= 0)
			{
				nRet = fetch_front_bit(&pool, &bit);
				if(nRet < 0)
				{
					printf("ERROR: Failed fetch_front_bit().\n");
					break;
				}

				if(bit)
				{
					n = nodes[n].rchild;
				}
				else
				{
					n = nodes[n].lchild;
				}
			}

			if(nodes[n].lchild < 0)
			{
				uint8 byteWriteData = nodes[n].data;
				memcpy(dst + *dlen, &byteWriteData, 1);
				*dlen += 1;
				n = count - 1;

				if(*dlen >= length)
					return 0;
			}

			if(pool.len <= 0)
			{
				break;
			}
		}
	}

	return 0;
}

// convert array to node_st for initializing huffman-tree
int static convert2node(uint32 buff[256], huff_node_st** nodes)
{
	int i, counter = 0;

	for(i=0; i<256; ++i)
	{
		if(buff[i])
		{
			counter++;
		}
	}

	int len = 2*counter-1;
	*nodes = (huff_node_st*)malloc(len*sizeof(huff_node_st));
	if(NULL == *nodes)
	{
		printf("ERROR: Failed malloc memory\n");
		return -1;
	}

	counter = 0;
	for(i=0 ; i<256; ++i)
	{
		if(buff[i])
		{
			(*nodes+counter)->lchild = -1;
			(*nodes+counter)->rchild = -1;
			(*nodes+counter)->parent = -1;
			(*nodes+counter)->data = i;
			(*nodes+counter)->count = buff[i];
			counter++;
		}
	}

	for(i=counter; i<len; ++i)
	{
		(*nodes+i)->lchild = -1;
		(*nodes+i)->rchild = -1;
		(*nodes+i)->parent = -1;
		(*nodes+i)->data   =  0;
		(*nodes+i)->count  =  0;
	}

	return len;
}

// statistic the count of each byte
// and return the total byte
int static stat_file_byte(FILE* fp, uint32 buffer[256])
{
	uint32 length = 0;
	if(NULL == fp)
	{
		printf("ERROR: NULL pointer\n");
		return -1;
	}

	int nRet;
	uint8 byte;
	while(nRet = fread(&byte, 1, 1, fp))
	{
		if(1 != nRet)
		{
			printf("Failed fread, %s\n", strerror(errno));
			break;
		}
		++buffer[byte];	
		++length;
	}
	return length;
}

/* statistic the bytes' frequence in memory */
int static stat_mem_byte(const uint8* cp, uint32 length, uint32 buffer[256])
{
	if(NULL == cp)
	{
		printf("ERROR: NULL pointer\n");
		return -1;
	}

	int i;
	for(i=0; i<length; ++i)
	{
		++buffer[cp[i]];	
	}

	return length;
}

static int write_hfm_file_header(FILE* fp, huff_node_st* nodes, int count, uint32 length)
{
	if(NULL == fp || NULL == nodes || count <= 0 || length <= 0)
	{
		printf("ERROR: Invalid argument.\n");
		return -1;
	}

	int elementCount = (count + 1)/2;
	huff_header_st header = {0};
	strncpy(header.id, "huff", 4);
	header.node_count = elementCount;
	header.offset = sizeof(huff_header_st) + elementCount * sizeof(freq_node_st);
	header.length = length;

	int nRet = fwrite(&header, sizeof(header), 1, fp);
	if(nRet != 1)
	{
		printf("ERROR: Failed fwrite huffman file header.\n");
		return -1;
	}

	int i;
	for(i=0; i<elementCount; ++i)
	{
		freq_node_st freqnode = {0};	
		freqnode.freq = nodes[i].count;
		freqnode.data = nodes[i].data;
		nRet = fwrite(&freqnode, sizeof(freqnode), 1, fp);
		if(nRet != 1)
		{
			printf("ERROR: Failed fwrite huffman file header.\n");
			return -1;
		}
	}

	return 0;
}

static int write_hfm_mem_header(char* mem, huff_node_st* nodes, int count, uint32 length)
{
	if(NULL == mem || NULL == nodes || count <= 0 || length <= 0)
	{
		printf("ERROR: Invalid argument.\n");
		return -1;
	}

	int elementCount = (count + 1)/2;
	huff_header_st header = {0};
	strncpy(header.id, "huff", 4);
	header.node_count = elementCount;
	header.offset = sizeof(huff_header_st) + elementCount * sizeof(freq_node_st);
	header.length = length;

	memcpy(mem, &header, sizeof(header));

	freq_node_st* pfreq = (freq_node_st*)(mem + sizeof(huff_header_st));
	freq_node_st freqnode = {0};	
	int i;
	for(i=0; i<elementCount; ++i)
	{
		freqnode.freq = nodes[i].count;
		freqnode.data = nodes[i].data;
		memcpy(pfreq+i, &freqnode, sizeof(freqnode));
	}

	return 0;
}


// compress file by huffman-coding
int hfm_compress_file(const char* fnread, const char* fnwrite)
{
	uint32 buffer[256] = {0};
	FILE* fpRead = fopen(fnread, "rb");
	if(NULL == fpRead)
	{
		printf("ERROR: Failed open file %s, %s\n", fnread, strerror(errno));
		return -1;
	}

	uint32 length = stat_file_byte(fpRead, buffer);

	huff_node_st* nodes = NULL;
	int count = convert2node(buffer, &nodes);
	if(count <= 0)
	{
		printf("ERROR: Failed convert2node\n");
		return -1;
	}

	FILE* fpWrite = fopen(fnwrite, "wb");
	if(NULL == fpWrite)
	{
		printf("ERROR: Failed open file %s, %s\n", fnwrite, strerror(errno));
		exit(1);		
	}

	fseek(fpRead, 0L, SEEK_SET);

	init_hfm_tree(nodes, count);

	write_hfm_file_header(fpWrite, nodes, count, length);
	hfm_code_file(nodes, count, fpRead, fpWrite);

	free(nodes);
	nodes = NULL;
	fclose(fpRead);
	fclose(fpWrite);

	return 0;
}

static int validate_hfm_header(const huff_header_st* header)
{
	if( strncmp("huff", header->id, 4) || 
		header->node_count < 0 || 
		header->length < 0 ||
		header->offset != sizeof(huff_header_st) + sizeof(freq_node_st) * header->node_count)
	{
		return -1;
	}

	return 0;
}

int hfm_decompress_file(const char* fnread, const char* fnwrite)
{
	FILE* fpRead = fopen(fnread, "rb");
	if(NULL == fpRead)
	{
		printf("ERROR: Failed read file %s, %s\n", fnread, strerror(errno));
		return -1;
	}

	huff_header_st header = {0};
	int nRet = fread(&header, sizeof(header), 1, fpRead);
	if(1 != nRet)
	{
		printf("ERROR: Failed read huffman header,%s\n", strerror(errno));
		return -1;
	}

	if(validate_hfm_header(&header) < 0)
	{
		printf("ERROR: Invalid huffman header.\n");
		return -1;
	}

	huff_node_st* nodes = NULL;
	int count = 2 * header.node_count - 1;
	nodes = (huff_node_st*)malloc(count * sizeof(huff_node_st));
	if(NULL == nodes)
	{
		printf("ERROR: Failed malloc memory,%s\n", strerror(errno));
		return -1;
	}	

	int i;
	for(i=0; i<header.node_count; ++i)
	{
		freq_node_st fnode = {0};
		nRet = fread(&fnode, sizeof(fnode), 1, fpRead);
		if(nRet != 1)
		{
			printf("ERROR: Failed read seq_node.\n");
			return -1;
		}
		nodes[i].lchild = -1;
		nodes[i].rchild = -1;
		nodes[i].parent = -1;
		nodes[i].data   = fnode.data;
		nodes[i].count  = fnode.freq;
	}

	for( ; i<count; ++i)
	{
		nodes[i].lchild = -1;
		nodes[i].rchild = -1;
		nodes[i].parent = -1;
		nodes[i].data = 0;
		nodes[i].count= 0;
	}

	init_hfm_tree(nodes, count);


	FILE* fpWrite = fopen(fnwrite, "wb");
	if(NULL == fpWrite)
	{
		printf("ERROR: Failed open %s, %s\n", fnwrite, strerror(errno));
		return -1;
	}

	hfm_decode_file(nodes, count, header.length, fpRead, fpWrite);

	free(nodes);
	fclose(fpRead);
	fclose(fpWrite);

	return 0;
}

int hfm_compress_mem(const uint8* src, uint32 slen, uint8* dst, uint32* dlen)
{
	uint32 buffer[256] = {0};
	if(NULL == src || NULL == dst || NULL == dlen)
	{
		printf("ERROR: Null pointer exception\n");
		return -1;
	}

	stat_mem_byte(src, slen, buffer);
	huff_node_st* nodes = NULL;
	int count = convert2node(buffer, &nodes);
	if(count <= 0)
	{
		printf("ERROR: Failed convert2node\n");
		return -1;
	}

	init_hfm_tree(nodes, count);
	write_hfm_mem_header(dst, nodes, count, slen);
	int element = (count + 1) / 2;
	int offset = sizeof(huff_header_st) + element * sizeof(freq_node_st);
	hfm_code_mem(nodes, count, src, slen, dst + offset, dlen);
	*dlen += offset;

	free(nodes);
	nodes = NULL;

	return 0;
}

int hfm_decompress_mem(const uint8* src, uint32 slen, uint8* dst, uint32* dlen)
{
	if(NULL == src || NULL == dst || NULL == dlen)
	{
		printf("ERROR: NULL pointer exception.\n");
		return -1;
	}

	huff_header_st header = {0};
	memcpy(&header, src, sizeof(header));
	if(validate_hfm_header(&header)< 0)
	{
		printf("ERROR: Invalid huffman header.\n");
		return -1;
	}

	huff_node_st* nodes = NULL;
	int count = 2 * header.node_count - 1;
	nodes = (huff_node_st*)malloc(count * sizeof(huff_node_st));
	if(NULL == nodes)
	{
		printf("ERROR: Failed malloc memory,%s\n", strerror(errno));
		return -1;
	}	

	freq_node_st* pfreq = (freq_node_st*)(src + sizeof(huff_header_st));
	freq_node_st fnode = {0};
	int i;
	for(i=0; i<header.node_count; ++i)
	{
		memcpy(&fnode, pfreq+i, sizeof(fnode));
		nodes[i].lchild = -1;
		nodes[i].rchild = -1;
		nodes[i].parent = -1;
		nodes[i].data   = fnode.data;
		nodes[i].count  = fnode.freq;
	}

	for( ; i<count; ++i)
	{
		nodes[i].lchild = -1;
		nodes[i].rchild = -1;
		nodes[i].parent = -1;
		nodes[i].data = 0;
		nodes[i].count= 0;
	}

	init_hfm_tree(nodes, count);
	hfm_decode_mem(nodes, count, src+header.offset, slen, header.length, dst, dlen);
	free(nodes);

	return 0;
}
