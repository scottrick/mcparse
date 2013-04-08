#pragma once

#include "minecraft_def.h"

#include "cppNBT\src\cppnbt.h"
#include "scottbase/Unknown.h"

#include <vector>
using namespace std;

class ChunkSection;
class Region;

#define SECTION_HEIGHT 16
#define CHUNK_WIDTH 16
#define CHUNK_HEIGHT 256

class Chunk : public Unknown
{
public:
    Chunk(const Region *region, const ChunkLocation *chunkLocation); //constructor!
    Chunk(const Chunk &chunk); //copy

    const Region                *getRegion() const                                  { return m_pRegion; }
    const ChunkLocation			*getChunkLocation() const                           { return m_pChunkLocation; }
	const  int					getChunkX() const									{ return m_ChunkX; }
	const  int					getChunkZ() const									{ return m_ChunkZ; }

	inline unsigned int	getBlockIdAt(unsigned int x, unsigned int y, unsigned int z) const
	{
		if (x < 0 || x >= CHUNK_WIDTH || z < 0 || z >= CHUNK_WIDTH || y < 0 || y >= CHUNK_HEIGHT)
		{ //not in this chunk, so return AIR for now
			return 0;
		}

		unsigned int offset = y * CHUNK_HEIGHT + z * CHUNK_WIDTH + x;
		return m_Blocks[offset];
	}

	//unknown
    const char                  *getClassName() const;

protected:
    ~Chunk();

    void                        setRegion(const Region *region);
    void                        setChunkLocation(const ChunkLocation *location);

private:
    const Region                *m_pRegion;
    const ChunkLocation         *m_pChunkLocation;

	int							m_ChunkX;
	int							m_ChunkZ;
	unsigned char				m_Blocks[CHUNK_WIDTH * CHUNK_WIDTH * CHUNK_HEIGHT];

    void go();
};