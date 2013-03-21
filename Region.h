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

    void open(); //open the region file and keep the data in memory
    void close(); //remove the region file from memory

	Chunk *getFirstChunk() const; //easy getter for now

    //unknown
    const char *getClassName() const;

protected:
    ~Region();

    void setData(unsigned char *newData);

private:
    string fileName;
    unsigned char *data;

    list<Chunk *> m_ChunkList;
};