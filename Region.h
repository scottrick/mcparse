#include <iostream>
using namespace std;

typedef struct ChunkLocation
{
    unsigned char data[4];

    unsigned int getOffset()
    {
        unsigned int offset = 0;
        offset |= (data[0] << 16);
        offset |= (data[1] << 8);
        offset |= (data[2] << 0);
        return offset;
    }

    unsigned int getSize()  { return data[3]; }
    void dump()             { cout << "ChunkLocation raw 0x" << hex << *((int *)data) << dec << " offset " << this->getOffset() << ", size " << this->getSize() << endl; }
    bool isValid()          { return data[0] || data[1] || data[2] || data[3]; }

} ChunkLocation;

typedef struct RegionHeader
{
    struct ChunkLocation locations[1024];
    int timeStamp[1024];
} RegionHeader;

class Region
{
public:

    Region(const string &fileName);
    Region(const Region &region);

    virtual ~Region();

    string getFileName() const                              { return fileName; }

    void go();

protected:


private:
    string fileName;

};