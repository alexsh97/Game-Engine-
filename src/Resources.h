#ifndef Resources_H
#define Resources_H

#include <iostream>
#include <map>
#include <string>

#include <glad/glad.h>
#include "Texture.h"
#include "Shader.h"
#include "irrklang/irrKlang.h"

//Audio silnik irrKlang
static irrklang::ISoundEngine *SoundEngine = irrklang::createIrrKlangDevice();

//Klasa opisująca plik audio
class Audio
{
    irrklang::ISound *sound;//Dźwięk
public:
	
	bool isActive;//Czy już dzwięk jest włączony
	
    const char* path;//Ścieżka do pliku
    //Konstruktor domyślny
    Audio(){}
    /**
        Tworzenie Audio

        @param path ścieżka do pliku
    */
    Audio(const char* path)
    {

        this->path = path;
        this->isActive = false;

    }
    /**
        Włączenie dzięku

        @param isWhile czy dzięk będzie zapętlany
    */
    void playAudio(GLboolean isWhile)
    {

        this->sound = SoundEngine->play2D(this->path, isWhile, false,true);
        this->isActive = true;

    }
    /**
        Zatrzymanie dzięku
    */
    void stopAudio()
    {
        this->sound->stop();
        this->sound->drop();
        this->isActive = false;

    }
};
//Klasa dla zasobów gry
class Resources
{
public:
    static std::map<std::string, Shader*> allShader;//Mapa przchowująca wszystkie sadery
    static std::map<std::string, Texture> allTextures;//Mapa przchowująca wszystkie tekstury
    static std::map<std::string, Audio*> allAudios;//Mapa przchowująca wszystkie pliki audio

    /**
        Ładowanie do gry shaderu.

        @param vertexShaderFile plik opisujący shader wierzchołków
        @param fragmentShaderFile plik opisujący shader fragmentowy
        @param geometryShaderFile plik opisujący shader geometryczny
        @param name nazwa shaderu
    */
    static Shader* loadShader(const GLchar *vertexShaderFile, const GLchar *fragmentShaderFile, const GLchar *geometryShaderFile, std::string name);
    /**
        Zwraca wskaźnik do shaderu o podanej nazwie

        @param name nazwa shaderu
        @return shader
    */
    static Shader* getShader(std::string name);
    /**
        Ładowanie tekstury do gry

        @param imgFile ścieżka do pliku
        @param alpha czy jest alfa kanał
        @param name nazwa tekstury
    */
    static Texture loadTexture(const GLchar *imgFile, GLboolean alpha, std::string name);
    /**
        Ładowanie tekstury skyboxu

        @param faces wektor każdej ze stron skyboxu
        @param name nazwa
    */
    static Texture loadTexCubeMap(std::vector<std::string> faces, std::string name);
    /**
        Zwraca teksture o podanej nazwie

        @param name nazwa
    */
    static Texture getTexture(std::string name);
    /**
        Ładowanie dzięku.

        @param path ścieżka do pliku audio
        @param name nazwa dzięku
    */
    static Audio* loadAudio(const char* path, std::string name);
    /**
        Zwraca wskaźnik do audio o podanej nazwie

        @param name nazwa
    */
    static Audio* getAudio(std::string name);
    static void clearResources();
private:
    Resources(){}

};

#endif // Resources_H
