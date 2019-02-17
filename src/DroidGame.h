#ifndef DroidGame_H
#define DroidGame_H

#include "Game.h"
#include "TextRender.h"
#include "Plane.h"
#include "Cuboid.h"
#include "Pyramid.h"

//Klasa DroidGame reprezentuje grę utworzoną na tym silniku
class DroidGame: public Game
{
public:
    DroidGame(): Game("Droid",500,500)
    {}
    DroidGame(const char* name, GLuint width, GLuint height): Game(name, width, height)
    { }
    ~DroidGame(){ std::cout<<"DroidGame has been deleted"<<std::endl;}

    void loadGame();
    void updateGame(GLfloat dt);
    void renderGame();
    void prepareLevels();
};

#endif // DroidGame_H



