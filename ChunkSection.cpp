#include "ChunkSection.h"

#include "Chunk.h"

#include <iostream>
#include <cassert>
using namespace std;

ChunkSection::ChunkSection(nbt::TagCompound *section)
	: m_pSection(section)
{

}

ChunkSection::~ChunkSection()
{

}

void ChunkSection::dump() const
{
	cout << m_pSection->toString() << endl;
}

unsigned int ChunkSection::getBlockIdAt(unsigned int x, unsigned int y, unsigned int z) const
{
	if (x >= CHUNK_WIDTH || y >= CHUNK_HEIGHT || z >= CHUNK_WIDTH) 
	{
		return 0;
	}

	int blockPosition = y * CHUNK_HEIGHT + z * CHUNK_WIDTH + x;

	nbt::TagByteArray *blocks = (nbt::TagByteArray *)m_pSection->getValueAt("Blocks");
	unsigned char blockId = blocks->getValue().at(blockPosition);

	return blockId;
}
const char *ChunkSection::getClassName() const
{
	return "ChunkSection";
}

unsigned int ChunkSection::getSectionY() const
{
	nbt::TagByte *tag = (nbt::TagByte *)m_pSection->getValueAt("Y");
	return tag->getValue();
}