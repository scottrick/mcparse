#pragma once

#include <cassert>
#include <iostream>
using namespace std;

#define CHUNKS_PER_REGION 1024

typedef enum ChunkCompressionScheme
{
    e_UNKNOWN,
    e_GZIP,
    e_ZLIB,
} ChunkCompressionScheme;

typedef struct ChunkHeader
{
    unsigned char data[5];

    int getChunkLength() const
    {
        unsigned int length = 0;
        length |= (data[0] << 24);
        length |= (data[1] << 16);
        length |= (data[2] << 8);
        length |= (data[3] << 0);
        return length;
    }

    ChunkCompressionScheme getCompressionScheme() const
    {
        return (ChunkCompressionScheme) data[4];
    }

} ChunkHeader;

typedef struct ChunkLocation
{
    unsigned char data[4];

    unsigned int getOffset() const
    {
        unsigned int offset = 0;
        offset |= (data[0] << 16);
        offset |= (data[1] << 8);
        offset |= (data[2] << 0);
        return offset;
    }

    unsigned int getSize() const    { return data[3]; }
    void dump() const               { cout << "ChunkLocation raw 0x" << hex << *((int *)data) << dec << ", offset " << this->getOffset() << ", size " << this->getSize() << endl; }
    bool isValid() const            { return data[0] || data[1] || data[2] || data[3]; }

} ChunkLocation;

typedef struct RegionHeader
{
    struct ChunkLocation locations[CHUNKS_PER_REGION];
    unsigned int timeStamp[CHUNKS_PER_REGION];

    void dump()
    {
        for (int i = 0; i < CHUNKS_PER_REGION; ++i)
        {
            if (locations[i].isValid())
            {
                cout << "[" << i << "] ";
                locations[i].dump();
                cout << endl;
                //cout << ", time " << timeStamp[i] << endl; 
            }
        }
    }
    
} RegionHeader;
