#pragma once

#include "scottbase/Unknown.h"

#include <iostream>
#include <list>
using namespace std;

class Chunk;

class Region : public Unknown
{
public:
    Region(const string &fileName);
    Region(const Region &region);

    unsigned char *getData() const                          { return data; }
    string getFileName() const                              { return fileName; }

	int getRegionX() const									{ return regionX; }
	int getRegionZ() const									{ return regionZ; }

    void open(); //open the region file and keep the data in memory
    void close(); //remove the region file from memory

	const list<Chunk *> &getChunks() const;

    //unknown
    const char *getClassName() const;

protected:
    ~Region();

    void setData(unsigned char *newData);

private:
    string fileName;
    unsigned char *data;

	int regionX, regionZ;

    list<Chunk *> m_ChunkList;
};