#include "zlib.h"

#include <fstream>
#include <iostream>
using namespace std;

#define DEFAULT_WORLD_DIRECTORY "MCParseTest"

int main(int numArgs, char **args)
{
	cout << "MCParse\nWritten by Scott Atkins\nMarch 2012\n" << endl;

	for (int i = 0; i < numArgs; ++i)
	{
		cout << "arg[" << i << "]=" << args[i] << endl;
	}

	string levelString("..\\"); 
	levelString += DEFAULT_WORLD_DIRECTORY;
	levelString += "\\level.dat";

	ifstream inStream;
	inStream.open(levelString.c_str(), ios::in | ios::binary | ios::ate);
	
	if (inStream.is_open())
	{
		int fileSize = inStream.tellg();
		char *data = new char[fileSize];

		inStream.seekg(ios::beg, 0);
		inStream.read(data, fileSize);

		cout << "Reading \"" << levelString.c_str() << "\"  -->  " << fileSize << " bytes" << endl;

		inStream.close();
	}
	else
	{
		cout << "Failed to open file \"" << levelString.c_str() << "\"" << endl;
	}

	return 0;
}