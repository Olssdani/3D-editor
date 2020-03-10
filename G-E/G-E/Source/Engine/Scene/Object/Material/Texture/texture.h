#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H 
#include <string>

class texture {

private:
	unsigned int id;
	std::string type;
	std::string path;

public:

	texture() = delete;
	texture(const std::string& inPath, const std::string& inType);
	texture(const char* inPath, const std::string& inType);

	unsigned int getId();
	std::string& getType();

	std::string& getPath();


private:
	unsigned int textureFromFile(const std::string& path, bool gamma);
};

#endif // !TEXTURE_H
