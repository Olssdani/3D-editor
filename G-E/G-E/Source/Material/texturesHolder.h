#ifndef TEXTUREHOLDER_H
#define TEXTUREHOLDER_H

#include <string>
#include <vector>
#include "texture.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class textureHolder{
private:
    std::vector<texture> textures;


public:

    std::vector<texture>& getTextures() {
        return textures;
    }

    void addTexture(texture tex) {
        textures.push_back(tex);
    }

    void loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName, textureHolder *loadedTextureHolder){
        
        std::vector<texture> loadedTextures = loadedTextureHolder->getTextures();
        
        for (unsigned int i = 0; i < mat->GetTextureCount(type); ++i){
           
            aiString str;
            mat->GetTexture(type, i, &str);
            // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
            bool skip = false;
            for (unsigned int j = 0; j < loadedTextures.size(); j++){
                if (std::strcmp(loadedTextures[j].getPath().data(), str.C_Str()) == 0){
                    textures.push_back(loadedTextures[j]);
                    skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
                    break;
                }
            }
            if (!skip){   // if texture hasn't been loaded already, load it             
                texture tex = texture(str.C_Str(), typeName);
                textures.push_back(tex);
                loadedTextures.push_back(tex);  // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
            }
        }
    }
};

#endif
