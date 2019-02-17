#ifndef TextRender_H
#define TextRender_H

#include <glad/glad.h>
#include <iostream>
#include <map>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include <ft2build.h>
#include FT_FREETYPE_H

//Struktura określająca proste GUI
struct GUI
{
    static std::string keyToPress; //Klawisz który można nacisnąć
    static std::string playerHP;//Poziom życia gracza
    static std::string levelName;//Nazwa obecnej sceny
};

//Struktura opisująca litere czy inny znak
struct Letter
{
    GLuint _textureID;//Tekstura znaku
    glm::ivec2 _size;//Rozmiar znaku
    glm::ivec2 _bearing;//
    GLuint _advance;//
};

//Klasa do wyświetlenia tekstu
class TextRender
{
    static std::map<GLchar, Letter> Letters;//Mapa przechowująca wszystkie znaki
    static GLuint VAO,VBO;//Vertex Arrey oraz Vertex Buffer
    static Shader* _shader;//Shader dla wyświetlenia tekstu
public:
    /**
        Inicjalizacja render tekstu

        @param shader program wyświetlający tekst
    */
    static void initTextRender(Shader *shader);
    /**
        Rysowanie tekstu na ekranie

        @param text łańcuch, który należy wyświetlić
        @param position położenie tekstu
        @param scale rozmiar tekstu
        @param color kolor tekstu
    */
    static void drawText(std::string text, glm::vec2 position, GLfloat scale, glm::vec3 color);
};

#endif // TextRender_H
