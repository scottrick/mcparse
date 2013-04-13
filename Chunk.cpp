#include "Chunk.h"

#include "minecraft_def.h"
#include "Region.h"
#include "cppNBT\src\cppnbt.h"

#define CHUNK_OFFSET_SIZE_IN_BYTES 4096

bool operator < (const ChunkLoc &l, const ChunkLoc &r)
{
	if (l.x != r.x) 
	{
		return l.x < r.x; 
	}

	return l.z < r.z;
}

Chunk::Chunk(const Region *region, const ChunkLocation *chunkLocation)
{
	m_ChunkMode = eNoChunkBorders;

	go(region, chunkLocation);
}

Chunk::Chunk(const Chunk &chunk)
{
	setWorld(chunk.getWorld());
	setLoc(chunk.getLoc());
	const unsigned char *blocks = chunk.getBlocks();
	memcpy(m_Blocks, blocks, CHUNK_WIDTH * CHUNK_WIDTH * CHUNK_HEIGHT);
}

Chunk::~Chunk()
{
	setWorld(0);
}

void Chunk::go(const Region *region, const ChunkLocation *chunkLocation)
{
    unsigned char *dataStart = region->getData() + (chunkLocation->getOffset() * CHUNK_OFFSET_SIZE_IN_BYTES);
    ChunkHeader *header = (ChunkHeader *)dataStart;

	nbt::NbtBuffer *pBuffer = new nbt::NbtBuffer(dataStart + sizeof(ChunkHeader), header->getChunkLength());

	nbt::TagCompound *root = (nbt::TagCompound *)pBuffer->getRoot();
	nbt::TagCompound *level = (nbt::TagCompound *)root->getValueAt("Level");
	nbt::TagList *sections = (nbt::TagList *)level->getValueAt("Sections");

	nbt::TagInt *xPos = (nbt::TagInt *)level->getValueAt("xPos");
	nbt::TagInt *zPos = (nbt::TagInt *)level->getValueAt("zPos");
	m_Loc.x = xPos->getValue();
	m_Loc.z = zPos->getValue();

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

void Chunk::setWorld(World *world) 
{
	m_pWorld = world;
}

const char *Chunk::getClassName() const {
    return "Chunk";
}