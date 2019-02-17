#ifndef Texture_H
#define Texture_H

#include <iostream>
#include <string>
#include <vector>
#include <glad/glad.h>

//Klasa opisująca teksture
class Texture
{
public:
    GLuint ID;//id tekstury
    std::string _name;//Nazwa tekstury
    GLuint _width, _height;//Rozmiary tekstury
    GLuint _internalFormat;//Format RGB czy RGBA
    GLuint _imgFormat;//Format  RGB czy RGBA
    GLuint _wrapS;//Texture wrapping
    GLuint _wrapT;//Texture wrapping
    GLuint _filterMax;//Filtr tekstury
    GLuint _filterMin;//Filtr tekstury

    //Konstruktor domyślny
    Texture();
    /**
        Ładowanie oraz generacja tekstury

        @param imgFile ścieżka do pliku
        @param alpha czy jest kanał alfa
        @param name nazwa
    */
    Texture(const GLchar *imgFile, GLboolean alpha, std::string name);
    /**
        Generacja tekstury dla skybox

        @param faces wektor każdej ze stron skyboxa
    */
    Texture(std::vector<std::string> faces);
    /**
        Generacja tekstury.

        @param width szerokość tekstury
        @param height wysokość tekstury
        @param data dane obrazka
    */
    void generateTexture(GLuint width, GLuint height, unsigned char* data);
    /**
        Generacja skyboxa

        @param faces wektor każdej ze stron skyboxa
    */
    void generateTexCubeMap(std::vector<std::string> faces);
    /**
        Ustawienie tektury jako aktualnej do przetwarzania
    */
    void Bind() const;
    /**
        Ustawienie tektury skybox jako aktualnej do przetwarzania
    */
    void BindCubeMap() const;
};

#endif // Texture_H
