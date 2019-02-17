#ifndef Plane_H
#define Plane_H
#include <glad/glad.h>

#include "GameObject.h"
#include "Rendering.h"

class Plane: public GameObject
{
public:
    /**
        Tworzenie obiektu.

        @param name nazwa tego objektu
        @param position wektor położenia
        @param objsize wektór zmiany rozmiaru objektu
        @param angel kąt obrotu
        @param rotation wektor obrotu
        @param texture tekstura objektu
    */
    Plane(std::string name, glm::vec3 position, glm::vec3 objsize, GLfloat angel, glm::vec3 rotation, Texture texture);//: GameObject(name, position, objsize, angel, rotation, texture)

    ~Plane(){std::cout<<"DELETED PLANE"<<std::endl;}
    /**
        Rysowanie obiektu

        @param render wskazuje jak będzie narysowany objekt, za wykorzystaniem jakiego shaderu
    */
    void drawObject(Rendering &render);
};

#endif // Plane_H
