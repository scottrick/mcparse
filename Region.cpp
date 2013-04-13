#include "Region.h"

#include "cppNBT\src\cppnbt.h"
#include "Chunk.h"
#include "minecraft_def.h"

#include <fstream>
#include <sstream>
using namespace std;

Region::Region(const string &fileName)
    : data(0)
{
    this->fileName = fileName;
    open();
}

Region::Region(const Region &region)
    : data(0)
{
    fileName = region.getFileName();
    open();
}

Region::~Region()
{
    close();
}

void Region::close()
{
    setData(0);
    
    list<Chunk *>::iterator iter = m_ChunkList.begin();
    Chunk *pChunk = 0;

    while (iter != m_ChunkList.end())
    {
        pChunk = *iter;
        pChunk->release();

        iter++;
    }

    m_ChunkList.clear();
}

void Region::open()
{
    close();

    ifstream inStream;
	inStream.open(fileName.c_str(), ios::in | ios::binary | ios::ate);

	size_t start = fileName.rfind("r.") + 2;
	size_t end = fileName.rfind(".mca");
	size_t coordLength = end - start;

	string regionCoordinates = fileName.substr(start, coordLength);

	size_t comma = regionCoordinates.rfind(".");

	string xCoord = regionCoordinates.substr(0, comma);
	string zCoord = regionCoordinates.substr(comma + 1, regionCoordinates.length() - comma - 1);

	istringstream xStream(xCoord);
	istringstream zStream(zCoord);

	xStream >> regionX;
	zStream >> regionZ;

	if (inStream.is_open())
	{
        int fileSize = (int)inStream.tellg();
		cout << "Reading \"" << fileName.c_str() << "\"  -->  " << fileSize << " bytes" << endl;

		unsigned char *newData = new unsigned char[fileSize];

		inStream.seekg(ios::beg, 0);
		inStream.read((char *)newData, fileSize);

        setData(newData);
        RegionHeader *regionHeader = (RegionHeader *)newData;

        for (int i = 0; i < CHUNKS_PER_REGION; ++i)
        {
            if (regionHeader->locations[i].isValid())
            {
                Chunk *newChunk = new Chunk(this, &(regionHeader->locations[i]));
                m_ChunkList.push_back(newChunk);
            }
        }

        inStream.close();
	}
	else
	{
		cout << "Failed to open file \"" << fileName.c_str() << "\"" << endl;
	}
}

const list<Chunk *> &Region::getChunks() const
{
	return m_ChunkList;
}

void Region::setData(unsigned char *newData)
{
    if (newData != data)
    {
        if (data)
        {
            delete data;
            data = 0;
        }

        if (newData)
        {
            data = newData;
        }
    }
}

const char *Region::getClassName() const {
    return "Region";
}