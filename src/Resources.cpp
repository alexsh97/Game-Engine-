#include "Resources.h"
#include <fstream>
#include <sstream>
#include "SOIL.h"

std::map<std::string, Texture> Resources::allTextures;
std::map<std::string, Shader*> Resources::allShader;
std::map<std::string, Audio*> Resources::allAudios;

Shader* Resources::loadShader(const GLchar *vertexShaderFile, const GLchar *fragmentShaderFile, const GLchar *geometryShaderFile, std::string name)
{
    allShader[name] = new Shader(vertexShaderFile,fragmentShaderFile);
    return allShader[name];
}

Shader* Resources::getShader(std::string name)
{
    return allShader[name];
}
Texture Resources::loadTexture(const GLchar *imgFile, GLboolean alpha, std::string name)
{
    allTextures[name] = Texture(imgFile, alpha, name);//loadTextureFromFile(imgFile,alpha);
    return allTextures[name];
}
Texture Resources::loadTexCubeMap(std::vector<std::string> faces, std::string name)
{
    allTextures[name] = Texture(faces);
    return allTextures[name];
}
Texture Resources::getTexture(std::string name)
{
    return allTextures[name];
}

Audio* Resources::loadAudio(const char* path, std::string name)
{
    allAudios[name] = new Audio(path);
    return allAudios[name];
}
Audio* Resources::getAudio(std::string name)
{
    return allAudios[name];
}

void Resources::clearResources()
{
    for(auto shader : allShader)
        glDeleteProgram(shader.second->getID());
    for(auto texture : allTextures)
        glDeleteTextures(1, &texture.second.ID);
    for(auto audio : allAudios)
        delete audio.second;
}

