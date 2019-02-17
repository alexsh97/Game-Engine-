#ifndef Level_H
#define Level_H

#include "GameObject.h"
#include "Plane.h"
#include <map>
#include <string>

//Klasa określająca poziom gry
class Level
{
public:
    std::map<std::string,GameObject*> allObjects;//Mapa przechowująca wszystkie obiekty na tym poziomie
    std::map<std::string,GameObject*> allTriggers;//Mapa przechowyjaca wszystkie triggery na tym poziomie
    std::string _name;//Nazwa poziomu
    /**
        Tworzenie levela

        @param name nazwa tego poziomu
    */
    Level(std::string name);
    /**
        Dodaje kolejny obiekt do levela

        @param object obiekt który został dodany
    */
    void addObject(GameObject *object);
     /**
        Dodaje kolejny triggera do levela

        @param object triggera który został dodany
    */
    void addTrigger(GameObject *object);
};

#endif // Level_H
