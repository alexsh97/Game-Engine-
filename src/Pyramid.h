#ifndef Pyramid_H
#define Pyramid_H

#include "GameObject.h"
#include "Rendering.h"

//Klasa piramidy
class Pyramid: public GameObject
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
    Pyramid(std::string name, glm::vec3 position, glm::vec3 objsize, GLfloat angel, glm::vec3 rotation, Texture texture);//: GameObject(name, position, objsize, angel, rotation, texture)

    /**
        Rysowanie obiektu

        @param render wskazuje jak będzie narysowany objekt, za wykorzystaniem jakiego shaderu
    */
    void drawObject(Rendering &render);
};

#endif // Cuboid_H
