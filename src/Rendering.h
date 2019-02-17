#ifndef Rendering_H
#define Rendering_H

#include "Shader.h"
#include "Light.h"
#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Klasa opisująca sposum renderowania
class Rendering
{
public:
    Shader *_shader;//Shader używany do renderowania
    Light *_dirLight;//Kierunkowe światło
    Light *_spotLight;//Strumień światła
    std::vector<Light*> _pointLight;//Punktowe światło
    Camera _camera;//Kamera

    /**
        Tworzenie renderu, wskazywanie jaki shader należy użyć, z jakiej kamery korzystać się.

        @param shader Shader
        @param camera Kamera
    */
    Rendering(Shader *shader, Camera camera)
    {
        this->_camera = camera;
        this->_shader = shader;
    }
    //Destruktor
    ~Rendering()
    {
        delete this->_dirLight;
        delete this->_spotLight;
        delete this->_shader;
    }
    /**
        Ustawienie parametrów dla światła kierunkowego.

        @param direction kierunek
        @param ambient otaczające
        @param diffuse roproszenie
        @param specular wziernikowe
    */
    void setDirLight(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
    {
        this->_dirLight = new Light("Sun", glm::vec3(0.0f,0.0f,0.0f), ambient, diffuse, specular);
        this->_dirLight->setDirection(direction);
    }
    /**
        Dodawanie prostego punktowego źródła światła

        @param point światło
    */
    void addPointLight(Light* point)
    {
        this->_pointLight.push_back(point);
    }
    /**
        Ustawienie parametrów dla światła kierunkowego.

        @param direction kierunek
        @param spot światło

    */
    void setSpotLight(glm::vec3 direction, Light* spot)
    {
        this->_spotLight = spot;
        this->_spotLight->setDirection(direction);
        this->_spotLight->cutOff = 12.5f;
        this->_spotLight->outerCutOff = 15.0f;
    }

};

#endif // Rendering_H
