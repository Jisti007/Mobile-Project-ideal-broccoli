#include "FileHelper.h"

#include <fstream>
#include <stdexcept>

using namespace std;

FileHelper::FileHelper()
{
}

FileHelper::~FileHelper()
{
}

std::vector<char> FileHelper::ReadText(const string & filePath)
{
	ifstream file(filePath, ios::ate);
	//file.unsetf(ios::skipws);
	return Read(file);
}

std::vector<char> FileHelper::ReadBinary(const string& filePath)
{
	ifstream file(filePath, ios::ate | ios::binary);
	return Read(file);
}

std::vector<char> FileHelper::Read(ifstream& file)
{
	if (!file.is_open())
	{
		throw std::runtime_error("Failed to open file!");
	}

	size_t fileSize = (size_t)file.tellg();
	std::vector<char> buffer(fileSize);
	file.seekg(0);
	file.read(buffer.data(), fileSize);
	file.close();
	buffer.push_back('\0');

	return buffer;
}
