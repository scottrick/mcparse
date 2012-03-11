#include "Region.h"

#include "cppNBT\src\cppnbt.h"
#include <fstream>

Region::Region(const string &fileName)
{
    this->fileName = fileName;
}

Region::Region(const Region &region)
{
    this->fileName = region.getFileName();
}

Region::~Region()
{

}

void Region::go()
{
    ifstream inStream;
	inStream.open(fileName.c_str(), ios::in | ios::binary | ios::ate);
	
	if (inStream.is_open())
	{
		int fileSize = inStream.tellg();
		char *data = new char[fileSize];

		inStream.seekg(ios::beg, 0);
		inStream.read(data, fileSize);

        RegionHeader *regionHeader = new RegionHeader();

        memcpy(regionHeader, data, sizeof(RegionHeader));

        for (int i = 0; i < 1024; ++i)
        {
            if (regionHeader->locations[i].isValid())
            {
                cout << "[" << i << "] ";
                regionHeader->locations[i].dump();
            }
        }

		cout << "Reading \"" << fileName.c_str() << "\"  -->  " << fileSize << " bytes" << endl;

		inStream.close();
	}
	else
	{
		cout << "Failed to open file \"" << fileName.c_str() << "\"" << endl;
	}
}