﻿#ifndef MESH_H
#define MESH_H

#include <glad/glad.h> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
using namespace std;

struct Vertex {
    
    glm::vec3 Position;//Położenie  
    glm::vec3 Normal; //Wektor normali
    glm::vec2 TexCoords;//Współrzędne tekstury
    glm::vec3 Tangent;//Styczna
    glm::vec3 Bitangent;//
};

struct Textura {
    unsigned int id;
    string type;
    string path;
};

class Mesh {
public:
    
    vector<Vertex> vertices;//Zbiór wierzchołków meshu
    vector<unsigned int> indices;//Zbór indeksów dla trójkątów
    vector<Textura> textures;//Zbiór tekstur tego meshu
    unsigned int VAO;

    /**
		Tworzenie meshu

		@param vertices zbiór wierzchołków 
		@param indices zbiór indeksów dla trójkątów
		@param textures zbiór tekstur
	*/
    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Textura> textures)
    {
        this->vertices = vertices;
        this->indices = indices;
        this->textures = textures;

        //Inicjalizacja VAO i VBO
		setupMesh();
    }

    /**
		Rysowanie meshu

		@param shader program cieniujący używany do rysowania tego mesha
	*/
    void Draw(Shader shader)
    {
        //Ustawienie odpowiednich tekstur jako obecnie używanych
        unsigned int diffuseNr  = 1;
        unsigned int specularNr = 1;
        unsigned int normalNr   = 1;
        unsigned int heightNr   = 1;
        for(unsigned int i = 0; i < textures.size(); i++)
        {
			//Aktywacja kolejne tekstury dla używania(rysowania)
            glActiveTexture(GL_TEXTURE0 + i); 
            
            string number;
            string name = textures[i].type;
            if(name == "texture_diffuse")
				number = std::to_string(diffuseNr++);
			else if(name == "texture_specular")
				number = std::to_string(specularNr++); 
            else if(name == "texture_normal")
				number = std::to_string(normalNr++); 
             else if(name == "texture_height")
			    number = std::to_string(heightNr++); 

			//Shader otrzymuje teksture do rysowania
            glUniform1i(glGetUniformLocation(shader.getID(), (name + number).c_str()), i);
            glBindTexture(GL_TEXTURE_2D, textures[i].id);
        }

        //Ruswanie trójkątów z których składa się ten mesh
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        glActiveTexture(GL_TEXTURE0);
    }

private:
    
    unsigned int VBO, EBO;
	/**
		Inicjalizacja VAO i VBO
	*/
    void setupMesh()
    {
		//Generowanie VAO, VBO, EBO   
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);
		//Kopiowanie danych do bufora
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

        //Ustawienie atrybutów wierzchołków
		//Położenie 
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        //Wektor normali
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
        //Współrzędne tekstur
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
        //Wektor stycznej
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
        //Wektor bitangent
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));

        glBindVertexArray(0);
    }
};
#endif
