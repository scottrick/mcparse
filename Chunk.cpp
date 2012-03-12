#include "Chunk.h"

#include "def.h"
#include "Region.h"

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
    char *dataStart = m_pRegion->getData() + (m_pChunkLocation->getOffset() * CHUNK_OFFSET_SIZE_IN_BYTES);

    ChunkHeader *header = (ChunkHeader *)dataStart;

    //cout << "dataStart " << hex << (unsigned int)dataStart[0] << " " << (unsigned int)dataStart[1] << " " << (unsigned int)dataStart[2] << " " << (unsigned int)dataStart[3] << " " << (unsigned int)dataStart[4] << dec << endl;

    m_pChunkLocation->dump();
    cout << endl << "  Chunk Length " << header->getChunkLength() << ", Compression Scheme " << (unsigned int)header->getCompressionScheme() << endl;

    //ChunkHeader *header = ChunkLocation
}

void Chunk::setChunkLocation(const ChunkLocation *location)
{
    m_pChunkLocation = location;
}

void Chunk::setRegion(const Region *region)
{
    m_pRegion = region;
}