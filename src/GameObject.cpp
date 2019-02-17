#include "GameObject.h"


GameObject::GameObject()
{

}
GameObject::GameObject(std::string name, glm::vec3 position, glm::vec3 objsize, GLfloat angel, glm::vec3 rotation,Texture texture)
{
    this->_name = name;
    this->_texture = texture;
    this->_position = position;
    this->_size = objsize;
    this->_angel = angel;
    this->_rotation = rotation;
}

GameObject::GameObject(std::string name, glm::vec3 position, glm::vec3 objsize, GLfloat angel, glm::vec3 rotation)
{
    this->_name = name;
    this->_position = position;
    this->_size = objsize;
    this->_angel = angel;
    this->_rotation = rotation;

}

void GameObject::drawObject(Rendering &render)
{
    std::cout<<"DRAW OBJECT"<<std::endl;
}

void GameObject::setPosition(glm::vec3 position)
{
    this->_position = position;
}


void GameObject::setRotation(GLfloat angle, glm::vec3 rotation)
{
    this->_rotation = rotation;
    this->_angel = angle;
}
