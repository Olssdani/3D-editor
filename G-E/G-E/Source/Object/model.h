#pragma once
#ifndef MODEL_H
#define MODEL_H
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <string>
#include <vector>
#include "Object.h"
#include <Object/Mesh.h>

class shader;

class model: public Object{
public:
    /*  Model Data */
    textureHolder* texturesLoaded;
    bool gammaCorrection;
    std::string directory;

    model(std::string const& path, bool gamma = false);
    ~model();
    void Draw(Shader *shader);

private:
    void loadModel(std::string const& path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
};
#endif