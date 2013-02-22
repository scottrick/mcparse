#include "Chunk.h"

#include "minecraft_def.h"
#include "Region.h"
#include "cppNBT\src\cppnbt.h"

#define CHUNK_OFFSET_SIZE_IN_BYTES 4096

Chunk::Chunk(const Region *region, const ChunkLocation *chunkLocation)
{
    setRegion(region);
    setChunkLocation(chunkLocation);
    go();
}

Chunk::Chunk(const Chunk &chunk)
{
    setRegion(chunk.getRegion());
    setChunkLocation(chunk.getChunkLocation());
    go();
}

Chunk::~Chunk()
{
    setRegion(0);
    setChunkLocation(0);
}

void Chunk::go()
{
    unsigned char *dataStart = m_pRegion->getData() + (m_pChunkLocation->getOffset() * CHUNK_OFFSET_SIZE_IN_BYTES);
    ChunkHeader *header = (ChunkHeader *)dataStart;

    nbt::NbtBuffer nbtBuffer(dataStart + sizeof(ChunkHeader), header->getChunkLength());

    static bool debug = false;

    if (debug)
    { //print out one chunk for now :)
        cout << nbtBuffer.getRoot()->toString() << endl;
        debug = false;
    }
}

void Chunk::setChunkLocation(const ChunkLocation *location)
{
    m_pChunkLocation = location;
}

void Chunk::setRegion(const Region *region)
{
    m_pRegion = region;
}