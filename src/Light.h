#ifndef Light_H
#define Light_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

//Klasa opisująca światło w grze
class Light
{
    glm::vec3 _direction;//Kierunek światła
    glm::vec3 _position;//Położenie źródła światła
    glm::vec3 _ambient;//Światło otaczające
    glm::vec3 _diffuse;//Światło rozproszone
    glm::vec3 _specular;//Światło wziernikowy
public:

    float cutOff;
    float outerCutOff;
    std::string _name;//Nazwa źródła światła
    float radius = 5.0f;
    /**
        Tworzenie źródła światła

        @param name nazwa
        @param position położenie
        @param ambient otaczające
        @param diffuse roproszenie
        @param specular wziernikowe
    */
    Light(std::string name, glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
    {
        this->_direction = glm::vec3(0.0f,0.0f,0.0f);
        this->_position = position;
        this->_ambient = ambient;
        this->_diffuse = diffuse;
        this->_specular = specular;
    }
    /**
        Ustawienie położenia dla źródła światła

        @param position położenie
    */
    void setPosition(glm::vec3 position)
    {
        this->_position = position;
    }
    glm::vec3 getPosition()
    {
        return this->_position;
    }
    /**
        Ustawienie kierunku dla źródła światła

        @param direction wektor kierunku
    */

    void setDirection(glm::vec3 direction)
    {
        this->_direction = direction;
    }
    glm::vec3 getDirection()
    {
        return this->_direction;
    }

    void setAmbient(glm::vec3 ambient)
    {
        this->_ambient = ambient;
    }
    glm::vec3 getAmbient()
    {
        return this->_ambient;
    }

    void setDiffuse(glm::vec3 diffuse)
    {
        this->_diffuse = diffuse;
    }
    glm::vec3 getDiffuse()
    {
        return this->_diffuse;
    }

    void setSpecular(glm::vec3 specular)
    {
        this->_specular = specular;
    }
    glm::vec3 getSpecular()
    {
        return this->_specular;
    }
};
#endif // Light_H
