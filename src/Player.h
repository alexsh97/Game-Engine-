#ifndef Player_H
#define Player_H

#include "GameObject.h"
#include "Model.h"
//#include "Item.h"

//Klasa określająca postać gracza
class Player//: public GameObject
{
public:
    glm::vec3 _velocity;//Wektor prędkości postaci
    glm::vec3 _direction;//Kierunek ruchu
    glm::vec3 _collisionDetection;
    int _health = 100;
    GameObject* model;//Załadowany model postaci

    //std::map<std::string, Item> inventory;//Mapa rzeczy gracza
    /**
        Tworzenie postaci dla gracza.

        @param name nazwa tego objektu
        @param position wektor położenia
        @param objsize wektór zmiany rozmiaru objektu
        @param angel kąt obrotu
        @param rotation wektor obrotu
    */
    Player(std::string name, glm::vec3 position, glm::vec3 objsize, GLfloat angel, glm::vec3 rotation)
    {
        this->_velocity = glm::vec3(1.0f,-9.8f,1.0f);
        this->_collisionDetection = glm::vec3(0.3f,0.8f,0.5f);
        model = new Model("resource\\objects\\R2D2\\r2-d2.obj", "droid", position, glm::vec3(0.005f, 0.005f,0.005f), angel, rotation);

    }
    void setModel(Model* m) { this->model = m;}

    /**
        Zwraca 3D model gracza

        @return wskaźnik do GameObject-załadowany model
    */
    GameObject* getModel() { return this->model;  }
    /**
        Zwraca położenie gracza

        @return wektor położenia x,y,z
    */
    glm::vec3 getPosition()
    {
        return this->model->_position;
    }
    /**
        @param HP zmienia wartość Życia postaci
    */
    void setHealth(int HP){  this->_health = HP;   }
    /**
        @return poziom życia postaci
    */
    int getHealth() {return this->_health; }
    /**
        Ruch gracza

        @param direction kierunek ruchu
    */
    void forwardMove(glm::vec3 direction)
    {
        model->_position.x += direction.x*this->_velocity.x;
        model->_position.z += direction.z*this->_velocity.z;
        //this->_position = this->model->_position;



        if(direction.z < 0.0f)
           this->model->_angel = 180.0f;
        else this->model->_angel = 0.0f;

        this->_direction = glm::vec3(0.0f,0.0f,1.0f);

        if(direction.z == 0.0f)
        {
            this->_direction = glm::vec3(1.0f,0.0f,0.0f);
            if(direction.x < 0.0f)
                this->model->_angel = -90.0f;
            else this->model->_angel = 90.0f;

        }

    }
    /**
        Wycofanie gracza.

        @param direction kierunek wycofania
    */
     void backMove(glm::vec3 direction)
    {
        model->_position.x -= direction.x*this->_velocity.x;
        model->_position.z -= direction.z*this->_velocity.z;
        model->_position.y += direction.y*this->_velocity.y;
        //this->_position = this->model->_position;
    }
    /**
        Rysowanie obiektu

        @param render wskazuje jak będzie narysowany objekt, za wykorzystaniem jakiego shaderu
    */
    void drawObject(Rendering &render)
    {
        this->model->drawObject(render);
    }
    /**
        Ruch obiektu pod wpływem grawitacji

        @param dt delta time
    */
    void gravityMove(GLfloat dt)
    {
        model->_position.y -= dt*1.8f;
        //this->_position.y = model->_position.y;

    }
    /**
        Skok gracza

        @param dt delta time
    */
    void Jump(GLfloat dt)
    {

        this->model->_position.y += 5.0f*dt*sin(40.0f);// + (this->_velocity.y*dt*dt)/2.0f;
        //this->_position.y = this->model->_position.y;
        //std::cout<<this->model->_position.y<<std::endl;
    }
    /**
        Resetowanie wszystkich zmian obiektu

    */
    void resetPlayer()
    {
        this->model->_position = glm::vec3(0.0f,0.04f,0.0f);
        //this->_position = this->model->_position;

    }
};

#endif
