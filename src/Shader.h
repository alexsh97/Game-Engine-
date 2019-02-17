#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

//Klasa opisująca shader
class Shader
{
    unsigned int ID;//ID shaderu
public:
    //Konstruktor domyślny
    Shader (){}
    /**
        Tworzenie shaderu. Tzn. odczytywanie kodu w plikach *.vs, *.fs , a następnie tworzenie programu shaderu

        @param vertexPath plik opisujący shader wierzchołków
        @param fragmentPath plik opisujący shader fragmentowy
        @param geometryPath plik opisujący shader geometryczny, domyślnie go nie ma
    */
    Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
    /**
        @return ID shaderu
    */
    unsigned int getID();
    //Używanie shader programu
    void use()
    {
        glUseProgram(ID);
    }

    void setMat4(const std::string &name, const glm::mat4 &mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void setInt(const std::string &name, int value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }

    void setFloat(const std::string &name, float value) const
    {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }

    void setVec3(const std::string &name, const glm::vec3 &value) const
    {
        glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }
    void setVec3(const std::string &name, float x, float y, float z) const
    {
        glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
    }

    void setVec4(const std::string &name, const glm::vec4 &value) const
    {
        glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }
    void setVec4(const std::string &name, float x, float y, float z, float w)
    {
        glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
    }


private:
    /**
        Sprawdzienie shadera, czy są jakiekolwiek błedy w programie.
        Jeżeli jakikolwiek błąd wystąpił podczas kompilacji shadera, wtedy w konsoli będzie napisany powód.

        @param shader ID shaderu
        @param type typ program czy vertex/fragment/geometry
    */
    void checkCompileErrors(GLuint shader, std::string type);

};
#endif
