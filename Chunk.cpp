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
	delete m_pBuffer;
}

void Chunk::go()
{
    unsigned char *dataStart = m_pRegion->getData() + (m_pChunkLocation->getOffset() * CHUNK_OFFSET_SIZE_IN_BYTES);
    ChunkHeader *header = (ChunkHeader *)dataStart;

	m_pBuffer = new nbt::NbtBuffer(dataStart + sizeof(ChunkHeader), header->getChunkLength());
}

void Chunk::setChunkLocation(const ChunkLocation *location)
{
    m_pChunkLocation = location;
}

void Chunk::setRegion(const Region *region)
{
    m_pRegion = region;
}

nbt::NbtBuffer *Chunk::getBuffer() const
{
	return m_pBuffer;
}

void Chunk::dump() const 
{
	cout << m_pBuffer->getRoot()->toString() << endl;
}

const char *Chunk::getClassName() const {
    return "Chunk";
}