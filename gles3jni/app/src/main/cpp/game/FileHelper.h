//
// Created by K1533 on 18.9.2017.
//

#ifndef GLES3JNI_FILEHELPER_H
#define GLES3JNI_FILEHELPER_H

#include <vector>
#include <string>

class FileHelper
{
public:
	FileHelper();
	virtual ~FileHelper();

	static std::vector<char> ReadText(const std::string& filePath);
	static std::vector<char> ReadBinary(const std::string& filePath);

private:
	static std::vector<char> Read(std::ifstream& file);
};

#endif //GLES3JNI_FILEHELPER_H
