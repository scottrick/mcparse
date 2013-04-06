#pragma once

#include "minecraft_def.h"

#include "cppNBT\src\cppnbt.h"
#include "scottbase/Unknown.h"

#include <vector>
using namespace std;

class ChunkSection;
class Region;

#define CHUNK_WIDTH 16
#define CHUNK_HEIGHT 256

class Chunk : public Unknown
{
public:
    Chunk(const Region *region, const ChunkLocation *chunkLocation); //constructor!
    Chunk(const Chunk &chunk); //copy

    const Region                *getRegion() const                                  { return m_pRegion; }
    const ChunkLocation			*getChunkLocation() const                           { return m_pChunkLocation; }

	unsigned int				getBlockIdAt(unsigned int x, unsigned int y, unsigned int z) const;
	nbt::NbtBuffer				*getBuffer() const;
	ChunkSection				*getSection(unsigned int sectionY) const;

	void						dump() const;

    //unknown
    const char                  *getClassName() const;

protected:
    ~Chunk();

    void                        setRegion(const Region *region);
    void                        setChunkLocation(const ChunkLocation *location);

private:
    const Region                *m_pRegion;
    const ChunkLocation         *m_pChunkLocation;

	nbt::NbtBuffer				*m_pBuffer;

	vector<ChunkSection *>		m_Sections;

    void go();
};