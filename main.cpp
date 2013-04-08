#include "zlib.h"

#pragma comment(lib, "zdll")

#include <fstream>
#include <iostream>
#include "cppNBT\src\cppnbt.h"

#include "opengl\GLContext.h"
#include "opengl\GLCameraScene.h"
#include "MCScene.h"
#include "Chunk.h"
#include "ChunkRenderable.h"
#include "Region.h"

using namespace std;
using namespace nbt;

#define DEFAULT_WORLD_DIRECTORY "MCParseTest"

int main(int numArgs, char **args)
{
	cout << "MCParse\nWritten by Scott Atkins\nMarch 2012\n" << endl;
	GLContext::create(numArgs, args, 0, 800, 600);

	string levelString(""); 
	levelString += DEFAULT_WORLD_DIRECTORY;
	levelString += "\\level.dat";

	try
	{
		nbt::NbtFile nbtFile;
		nbtFile.open(levelString, "rb");
		nbtFile.read();
		Tag *rootTag = nbtFile.getRoot();
		cout << rootTag->toString() << endl;
		nbtFile.close();
	}
	catch (GzipIOException &exception)
	{
		cout << "Failed to open NBT file.  Error: " << exception.what() << endl;
	}

	GLScene *scene = new GLCameraScene();

	vector<std::string> regionFiles;
	//regionFiles.push_back("\\region\\r.0.0.mca");
	regionFiles.push_back("\\region\\oldserver.r.0.0.mca");

	vector<std::string>::iterator iter;

	for (iter = regionFiles.begin(); iter != regionFiles.end(); iter++)
	{
		string testMcaString("");
		testMcaString += DEFAULT_WORLD_DIRECTORY;
		testMcaString += *iter;
		Region *region = new Region(testMcaString);

		const list<Chunk *> chunks = region->getChunks();
		list<Chunk *>::const_iterator iter;

		for (iter = chunks.begin(); iter != chunks.end(); iter++)
		{
			Chunk *pChunk = *iter;
			ChunkRenderable *pChunkRenderable = new ChunkRenderable(pChunk);
			scene->addRenderable(pChunkRenderable);
			pChunkRenderable->release();
		}

	    region->release();
	}

	GLContext::setScene(scene);
	GLContext::go();

    scene->release();

    return 0;
}