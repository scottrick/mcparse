#include "Chunk.h"

#include "minecraft_def.h"
#include "ChunkSection.h"
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

	nbt::TagCompound *root = (nbt::TagCompound *)m_pBuffer->getRoot();
	nbt::TagCompound *level = (nbt::TagCompound *)root->getValueAt("Level");
	nbt::TagList *sections = (nbt::TagList *)level->getValueAt("Sections");

	for (size_t i = 0; i < sections->size(); ++i)
	{
		nbt::TagCompound *section = (nbt::TagCompound *)sections->at(i);
		ChunkSection *pSection = new ChunkSection(section);
		m_Sections.push_back(pSection);
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

unsigned int Chunk::getBlockIdAt(unsigned int x, unsigned int y, unsigned int z) const
{
	unsigned int sectionY = y / SECTION_HEIGHT;
	ChunkSection *pSection = getSection(sectionY);

	if (pSection)
	{
		return pSection->getBlockIdAt(x, y % CHUNK_WIDTH, z);
	}

	return 0; //no section, so return 0 for AIR
}

nbt::NbtBuffer *Chunk::getBuffer() const
{
	return m_pBuffer;
}

ChunkSection *Chunk::getSection(unsigned int sectionY) const
{
	vector<ChunkSection *>::const_iterator iter;
	for (iter = m_Sections.begin(); iter != m_Sections.end(); iter++)
	{
		if ((*iter)->getSectionY() == sectionY) 
		{
			return *iter;
		}
	}

	return 0;
}

void Chunk::dump() const 
{
	cout << m_pBuffer->getRoot()->toString() << endl;
}

const char *Chunk::getClassName() const {
    return "Chunk";
}