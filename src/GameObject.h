#ifndef GameObject_H
#define GameObject_H

#include <glad\glad.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <string>
//#include "Shaders.h"
#include "Texture.h"
#include "Rendering.h"

//Klasa obiektów w grze
class GameObject
{
protected:

    unsigned int VAO,VBO;
    glm::mat4 _model;//Model określający transformacje, skalowanie, rotacje obiektu
    Texture _texture;//Tekstura obiektu

public:
    std::string _name;//Nazwa obiektu
    glm::vec3 _position;//Wektor położenia
    glm::vec3 _size;//Wektor rozmiaru
    glm::vec3 _rotation;//Wektot rotacji
    GLfloat _angel;//Kąt obrotu
    //Konstrukotr domyślny
    GameObject();
    /**
        Tworzenie obiektu.

        @param name nazwa tego objektu
        @param position wektor położenia
        @param objsize wektór zmiany rozmiaru objektu
        @param angel kąt obrotu
        @param rotation wektor obrotu
        @param texture tekstura objektu
    */
    GameObject(std::string name, glm::vec3 position, glm::vec3 objsize, GLfloat angel, glm::vec3 rotation, Texture texture);
    GameObject(std::string name, glm::vec3 position, glm::vec3 objsize, GLfloat angel, glm::vec3 rotation);
    /**
        Ustawienie nowego położenia obiektu

        @param position wektor położenia
    */
    void setPosition(glm::vec3 position);
    /**
        Rotacja obiektu

        @param angle kąt obrotu
        @param rotation wektor obrotu
    */

    void setRotation(GLfloat angle, glm::vec3 rotation);
    /**
        Rysowanie obiektu

        @param render wskazuje jak będzie narysowany objekt, za wykorzystaniem jakiego shaderu
    */
    virtual void drawObject(Rendering &render);

};

#endif // GameObject_H
