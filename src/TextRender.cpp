#include "TextRender.h"

std::string GUI::keyToPress = "";
std::string GUI::levelName = "";
std::string GUI::playerHP = "100";

std::map<GLchar, Letter> TextRender::Letters;
GLuint TextRender::VAO;
GLuint TextRender::VBO;
Shader* TextRender::_shader;

 void TextRender::initTextRender(Shader *shader)
 {
     _shader = shader;
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(1000), 0.0f, static_cast<GLfloat>(540));
    shader->use();
    glUniformMatrix4fv(glGetUniformLocation(shader->getID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    // FreeType
    FT_Library ft;
    // Inicjalizacja biblioteki FreeType
    if (FT_Init_FreeType(&ft))
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

    // Ładowanie czcionka
    FT_Face face;
    if (FT_New_Face(ft, "C:\\Windows\\Fonts\\Arial.ttf", 0, &face))
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

    // Rozmiar glifu
    FT_Set_Pixel_Sizes(face, 0, 48);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // Ładowanie pierwszych 128 znaków ASCII
    for (GLubyte c = 0; c < 128; c++)
    {
        // Ładowanie glif znaku
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }
        // Generacja tekstury tekstu
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
        // Konfiguracja tekstury
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        //Zapis liter
        Letter character = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x
        };
        Letters.insert(std::pair<GLchar, Letter>(c, character));
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    //Usuwanie freetype
    FT_Done_Face(face);
    FT_Done_FreeType(ft);


    //Konfiguracja VAO i VBO dla tekstu
    glGenVertexArrays(1, &TextRender::VAO);
    glGenBuffers(1, &TextRender::VBO);

    glBindVertexArray(TextRender::VAO);
    glBindBuffer(GL_ARRAY_BUFFER, TextRender::VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);


    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);


    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
 }

void TextRender::drawText(std::string text, glm::vec2 position, GLfloat scale, glm::vec3 color)
{
    //Wykorzystanie shaderu
    _shader->use();
    glUniform3f(glGetUniformLocation(_shader->getID(), "textColor"), color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    //Iteracja po wszystkich znakach
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Letter ch = Letters[*c];

        GLfloat xpos = position.x + ch._bearing.x * scale;
        GLfloat ypos = position.y - (ch._size.y - ch._bearing.y) * scale;

        GLfloat w = ch._size.x * scale;
        GLfloat h = ch._size.y * scale;
        // Aktualizacja VBO dla kolejnego znaku
        GLfloat vertices[] =
        {   //vertex              //texture
             xpos,     ypos + h,   0.0, 0.0 ,
             xpos,     ypos,       0.0, 1.0 ,
             xpos + w, ypos,       1.0, 1.0 ,

             xpos,     ypos + h,   0.0, 0.0 ,
             xpos + w, ypos,       1.0, 1.0 ,
             xpos + w, ypos + h,   1.0, 0.0
        };

        glBindTexture(GL_TEXTURE_2D, ch._textureID);
        // Aktualizacja VBO
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // Rysowanie
        glDrawArrays(GL_TRIANGLES, 0, 6);

        position.x += (ch._advance >> 6) * scale;
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}
