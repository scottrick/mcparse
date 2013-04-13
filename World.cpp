#include "World.h"

#include "Chunk.h"

#include <iostream>
using namespace std;

World::World(void)
{

}

World::~World(void)
{
	deleteChunks();
}

void World::addRegion(Region *pRegion) 
{
	const list<Chunk *> chunks = pRegion->getChunks();
	list<Chunk *>::const_iterator iter;

	unsigned int MAX = 50000;

	for (iter = chunks.begin(); iter != chunks.end(); iter++)
	{
		Chunk *pChunk = *iter;
		pChunk->addRef();
		pChunk->setWorld(this);
		m_Chunks[pChunk->getLoc()] = pChunk;

		if (m_Chunks.size() >= MAX)
		{
			break;
		}
	}
}

void World::deleteChunks()
{
	map<const ChunkLoc, Chunk *>::const_iterator iter;
	for (iter = m_Chunks.begin(); iter != m_Chunks.end(); iter++)
	{
		pair<const ChunkLoc, Chunk*> item = *iter;
		Chunk *pChunk = item.second;
		pChunk->release();
	}

	m_Chunks.clear();
}

void World::dump() const
{
	map<const ChunkLoc, Chunk *>::const_iterator iter;
	for (iter = m_Chunks.begin(); iter != m_Chunks.end(); iter++)
	{
		pair<const ChunkLoc, Chunk*> item = *iter;
		ChunkLoc loc = item.first;
		Chunk *pChunk = item.second;
		cout << "(" << loc.x << ", " << loc.z << ")" << endl;
	}
}

Chunk *World::getChunk(ChunkLoc &loc)
{
	return m_Chunks[loc];
}


map<ChunkLoc, Chunk *> World::getChunks() const
{
	return m_Chunks;
}

const char *World::getClassName() const 
{
	return "World";
}