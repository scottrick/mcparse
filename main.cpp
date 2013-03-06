#include "zlib.h"

#pragma comment(lib, "zdll")

#include <fstream>
#include <iostream>
#include "cppNBT\src\cppnbt.h"

#include "opengl\GLContext.h"
#include "opengl\GLCameraScene.h"
#include "MCScene.h"
#include "Region.h"

using namespace std;
using namespace nbt;

#define DEFAULT_WORLD_DIRECTORY "MCParseTest"

int main(int numArgs, char **args)
{
	cout << "MCParse\nWritten by Scott Atkins\nMarch 2012\n" << endl;

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

    //{
    //    string testMcaString("");
    //    testMcaString += DEFAULT_WORLD_DIRECTORY;
    //    testMcaString += "\\region\\r.0.0.mca";
    //    Region *region = new Region(testMcaString);
    //    region->Release();
    //}

    //{
    //    string testMcaString("");
    //    testMcaString += DEFAULT_WORLD_DIRECTORY;
    //    testMcaString += "\\region\\r.-1.0.mca";
    //    Region *region = new Region(testMcaString);
    //    region->Release();
    //}

	GLContext::create(numArgs, args, 0, 800, 600);

    GLScene *scene = new GLCameraScene();
	GLContext::setScene(scene);
	GLContext::go();

    scene->Release();

    return 0;
}