#include "IOManager.h"
#include <fstream>

bool IOManager::ReadFileToBuffer(const std::string& filePath, std::vector<unsigned char>& buffer)
{
	std::ifstream file(filePath, std::ios::binary);
	if (file.fail())
	{
		perror(filePath.c_str());
		return false;
	}

	// seek file end
	file.seekg(0, std::ios::end);

	// get the file size
	int fileSize = file.tellg();

	// back to the begining
	file.seekg(0, std::ios::beg);

	// reduce the size of any header from file size
	fileSize -= file.tellg();

	buffer.resize(fileSize);
	file.read((char*)(&(buffer[0])), fileSize);
	file.close();

	return true;
}