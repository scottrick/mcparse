#pragma once

#include "minecraft_def.h"

#include "cppNBT\src\cppnbt.h"
#include "scottbase/Unknown.h"

class Region;

class Chunk : public Unknown
{
public:
    Chunk(const Region *region, const ChunkLocation *chunkLocation); //constructor!
    Chunk(const Chunk &chunk); //copy

    const Region                *getRegion() const                                  { return m_pRegion; }
    const ChunkLocation         *getChunkLocation() const                           { return m_pChunkLocation; }

    //unknown
    const char                  *getClassName() const;

protected:
    ~Chunk();

    void                        setRegion(const Region *region);
    void                        setChunkLocation(const ChunkLocation *location);

private:
    const Region                *m_pRegion;
    const ChunkLocation         *m_pChunkLocation;

    void go();
};