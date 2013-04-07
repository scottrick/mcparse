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

	nbt::NbtBuffer *pBuffer = new nbt::NbtBuffer(dataStart + sizeof(ChunkHeader), header->getChunkLength());

	nbt::TagCompound *root = (nbt::TagCompound *)pBuffer->getRoot();
	nbt::TagCompound *level = (nbt::TagCompound *)root->getValueAt("Level");
	nbt::TagList *sections = (nbt::TagList *)level->getValueAt("Sections");

	//fill our blocks byte array
	memset(m_Blocks, 0, CHUNK_WIDTH * CHUNK_WIDTH * CHUNK_HEIGHT);
	for (size_t i = 0; i < sections->size(); ++i)
	{
		nbt::TagCompound *section = (nbt::TagCompound *)sections->at(i);
		nbt::TagByte *tag = (nbt::TagByte *)section->getValueAt("Y");
		unsigned int sectionY = tag->getValue();

		nbt::TagByteArray *blocks = (nbt::TagByteArray *)section->getValueAt("Blocks");

		memcpy(m_Blocks + sectionY * CHUNK_WIDTH * CHUNK_WIDTH * SECTION_HEIGHT, blocks->getValues(), blocks->getSize());
	}

	//all done reading in the chunk, so delete the NBT buffer
	delete pBuffer;
}

void Chunk::setChunkLocation(const ChunkLocation *location)
{
    m_pChunkLocation = location;
}

void Chunk::setRegion(const Region *region)
{
    m_pRegion = region;
}

const char *Chunk::getClassName() const {
    return "Chunk";
}