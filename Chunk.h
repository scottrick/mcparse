#include "minecraft_def.h"

#include "cppNBT\src\cppnbt.h"

class Region;

class Chunk
{
public:
    Chunk(const Region *region, const ChunkLocation *chunkLocation); //constructor!
    Chunk(const Chunk &chunk); //copy

    ~Chunk();

    const Region                *getRegion() const                                  { return m_pRegion; }
    const ChunkLocation         *getChunkLocation() const                           { return m_pChunkLocation; }

protected:

    void                        setRegion(const Region *region);
    void                        setChunkLocation(const ChunkLocation *location);

private:
    const Region                *m_pRegion;
    const ChunkLocation         *m_pChunkLocation;

    void go();
};