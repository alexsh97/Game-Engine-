#include "Level.h"
#include "Resources.h"

Level::Level(std::string name)
{
    this->_name = name;
}

void Level::addObject(GameObject *object)
{
    std::string name = object->_name;
    std::cout<<"Add object to "<<this->_name<<name<<std::endl;

    allObjects[name] = object;
}

void Level::addTrigger(GameObject *object)
{
    std::string name = object->_name;
    std::cout<<"Add trigger to "<<this->_name<<name<<std::endl;

    allTriggers[name] = object;
}
