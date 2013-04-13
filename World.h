#pragma once

#include "Region.h"
#include "scottbase/Unknown.h"

struct ChunkLoc;

#include <map>
using namespace std;

class World : public Unknown
{
public:
	World();
	~World();

	void								addRegion(Region *pRegion);

	Chunk								*getChunk(ChunkLoc &loc);

	map<ChunkLoc, Chunk *>				getChunks() const;

	void								dump() const;

	//unknown
    const char							*getClassName() const;

protected:

	map<ChunkLoc, Chunk *> m_Chunks;

	void								deleteChunks();
};

