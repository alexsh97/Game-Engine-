#ifndef MODEL_H
#define MODEL_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <SOIL.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"
#include "Resources.h"
#include "Rendering.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

//Klasa opisująca załadowany model
class Model : public GameObject
{
public:

    vector<Textura> textures_loaded;//Wektor wszystkich tekstur obiektu
    vector<Mesh> meshes;//Wektor wszystkich meshej obiektu
    string directory;//Ścieżka do pliku z obiektem
    bool gammaCorrection;

    /**
        Tworzenie obiektu.

        @param name nazwa tego objektu
        @param position wektor położenia
        @param objsize wektór zmiany rozmiaru objektu
        @param angel kąt obrotu
        @param rotation wektor obrotu
        @param texture tekstura objektu
    */
    Model(string const &path, string name, glm::vec3 position, glm::vec3 objsize, GLfloat angel, glm::vec3 rotation, bool gamma = false) : GameObject(name, position, objsize, angel, rotation)
    {
        this->gammaCorrection = gamma;
        loadModel(path);
    }

    /**
        Rysowanie obiektu

        @param render wskazuje jak będzie narysowany objekt, za wykorzystaniem jakiego shaderu
    */
    void drawObject(Rendering &render)
    {

        render._shader->use();
        //Oświetlenie obiektu
        render._shader->setVec3("viewPos", render._camera._position);

        render._shader->setVec3("dirLight.direction", render._dirLight->getDirection());
        render._shader->setVec3("dirLight.ambient", render._dirLight->getAmbient());
        render._shader->setVec3("dirLight.diffuse", render._dirLight->getDiffuse());
        render._shader->setVec3("dirLight.diffuse", render._dirLight->getSpecular());

        render._shader->setInt("lightSize", render._pointLight.size());

        for(unsigned int i=0; i < render._pointLight.size(); i++)
        {
            std::string str = "pointLight[" + std::to_string(i);
            render._shader->setVec3(str + "].position", render._pointLight[i]->getPosition());
            render._shader->setVec3(str + "].ambient", render._pointLight[i]->getAmbient());
            render._shader->setVec3(str + "].diffuse", render._pointLight[i]->getDiffuse());
            render._shader->setVec3(str + "].specular", render._pointLight[i]->getSpecular());
        }

        render._shader->setVec3("spotLight.position", render._spotLight->getPosition());
        render._shader->setVec3("spotLight.direction", render._spotLight->getDirection());
        render._shader->setVec3("spotLight.ambient", render._spotLight->getAmbient());
        render._shader->setVec3("spotLight.diffuse", render._spotLight->getDiffuse());
        render._shader->setVec3("spotLight.specular", render._spotLight->getSpecular());
        render._shader->setFloat("spotLight.cutOff", glm::cos(glm::radians(render._spotLight->cutOff)));
        render._shader->setFloat("spotLight.outerCutOff", glm::cos(glm::radians(render._spotLight->outerCutOff)));

        render._shader->setVec3("material.specular", 0.5f, 0.5f, 0.5f);
        render._shader->setFloat("material.shininess", 64.0f);


        glm::mat4 model;

        //Określenie jak obiekt będzie wyświetlony
        render._shader->setMat4("projection", render._camera._projection);
        render._shader->setMat4("view", render._camera._view);

        //Transformacja, rotacja, skalowanie obiektu
        model = glm::translate(model, this->_position);
        model = glm::scale(model, this->_size);
        model = glm::rotate(model,glm::radians(this->_angel), this->_rotation);
        this->_model = model;

        glUniformMatrix4fv(glGetUniformLocation(render._shader->getID(),"model"),1,GL_FALSE, glm::value_ptr(this->_model));
        for(unsigned int i = 0; i < meshes.size(); i++)
            meshes[i].Draw(*render._shader);
    }

private:
    /**
        Ładowanie modelu do gry.

        @param path ścieżka do pliku *.obj
    */
    void loadModel(string const &path)
    {

        Assimp::Importer importer;

        const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate |
                        aiProcess_FlipUVs  | aiProcess_GenNormals | aiProcess_CalcTangentSpace);

        if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
            return;
        }

        directory = path.substr(0, path.find_last_of('\\'));

        processNode(scene->mRootNode, scene);
    }

	/**
		Opracowanie wszystkich meshy chodząc po strukturze Assimp w sposób rekurencyjny
	*/
    void processNode(aiNode *node, const aiScene *scene)
    {

        for(unsigned int i = 0; i < node->mNumMeshes; i++)
        {

            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            meshes.push_back(processMesh(mesh, scene));
        }

        for(unsigned int i = 0; i < node->mNumChildren; i++)
        {
            processNode(node->mChildren[i], scene);
        }

    }
	/**
		Opracowanie meshu, konwetacja struktury Assimp na postać zrozumiałą dla OpenGL
	*/
    Mesh processMesh(aiMesh *mesh, const aiScene *scene)
    {

        vector<Vertex> vertices;
        vector<unsigned int> indices;
        vector<Textura> textures;


        for(unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            Vertex vertex;
            glm::vec3 vector;

            vector.x = mesh->mVertices[i].x;
            vector.y = mesh->mVertices[i].y;
            vector.z = mesh->mVertices[i].z;
            vertex.Position = vector;

            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.Normal = vector;


            if(mesh->mTextureCoords[0])
            {
                glm::vec2 vec;

                vec.x = mesh->mTextureCoords[0][i].x;
                vec.y = mesh->mTextureCoords[0][i].y;
                vertex.TexCoords = vec;
            }
            else
                vertex.TexCoords = glm::vec2(0.0f, 0.0f);

            vector.x = mesh->mTangents[i].x;
            vector.y = mesh->mTangents[i].y;
            vector.z = mesh->mTangents[i].z;
            vertex.Tangent = vector;


            vector.x = mesh->mBitangents[i].x;
            vector.y = mesh->mBitangents[i].y;
            vector.z = mesh->mBitangents[i].z;
            vertex.Bitangent = vector;
            vertices.push_back(vertex);
        }


        for(unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];

            for(unsigned int j = 0; j < face.mNumIndices; j++)
                indices.push_back(face.mIndices[j]);
        }


        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

        vector<Textura> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

        vector<Textura> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

        std::vector<Textura> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
        textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

        std::vector<Textura> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
        textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());


        return Mesh(vertices, indices, textures);
    }

    /**
        Ładowanie tekstur meterialu do aplikacji.
    */
    vector<Textura> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName)
    {
        vector<Textura> textures;

        for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
        {

            aiString str;
            mat->GetTexture(type, i, &str);

            bool skip = false;
            for(unsigned int j = 0; j < textures_loaded.size(); j++)
            {
                if(std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
                {

                    textures.push_back(textures_loaded[j]);
                    skip = true;
                    break;
                }
            }
            if(!skip)
            {
                std::cout<<"dont loaded"<<std::endl;
                Textura texture;
                texture.id = TextureFromFile(str.C_Str(), this->directory);
                texture.type = typeName;
                texture.path = str.C_Str();
                textures.push_back(texture);
                textures_loaded.push_back(texture);
            }
        }
        return textures;
    }
	/**
	Ładowanie tekstur z pliku do aplikacji

	@param path ścieżka do pliku
	@param directory
	@param gamma
	*/
unsigned int TextureFromFile(const char *path, const string &directory, bool gamma = false)
{
    string filename = string(path);

    filename = directory + '\\' + filename;

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height;

    unsigned char *data = SOIL_load_image(filename.c_str(),&width, &height, 0, SOIL_LOAD_RGBA);
    std::cout<<filename.c_str()<<std::endl;
    if (data)
    {
        GLenum format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


        SOIL_free_image_data(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;

        SOIL_free_image_data(data);
    }

    return textureID;
}
};



#endif
