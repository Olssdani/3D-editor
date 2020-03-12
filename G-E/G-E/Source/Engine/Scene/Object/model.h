#pragma once
#include "object.h"
class shader;

class model : public object {
public:
	/*  Model Data */
	textureHolder* texturesLoaded;
	bool gammaCorrection;
	std::string directory;

	model(std::string const& path, bool gamma = false);
	~model();
	void Draw(shader* shader);

private:
	void loadModel(std::string const& path);
	void processNode(aiNode* node, const aiScene* scene);
	mesh processMesh(aiMesh* aimesh, const aiScene* scene);
};
