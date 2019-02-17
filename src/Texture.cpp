#include "Texture.h"
#include "SOIL.h"

Texture::Texture():  _width(0), _height(0), _internalFormat(GL_RGB), _imgFormat(GL_RGB), _wrapS(GL_REPEAT), _wrapT(GL_REPEAT), _filterMax(GL_LINEAR), _filterMin(GL_LINEAR)
{
    glGenTextures(1, &this->ID);
}

Texture::Texture(const GLchar *imgFile, GLboolean alpha, std::string name):  _name(name), _width(0), _height(0), _internalFormat(GL_RGB), _imgFormat(GL_RGB), _wrapS(GL_REPEAT), _wrapT(GL_REPEAT), _filterMax(GL_LINEAR), _filterMin(GL_LINEAR)
{
    //Generacja tekstury
     glGenTextures(1, &this->ID);
     //Sprawdzenie czy tekstura ma kanał alfa
     if(alpha)
        {
            this->_internalFormat = GL_RGBA;
            this->_imgFormat = GL_RGBA;
            this->_wrapS = GL_CLAMP_TO_EDGE;
            this->_wrapT = GL_CLAMP_TO_EDGE;
        }
    //rozmiary tekstury
    int width, height;
    //Ładowanie obrazku do programu
    unsigned char *image = SOIL_load_image(imgFile,&width, &height, 0, this->_imgFormat == GL_RGBA ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);
    //Generacja i konfiguracja tekstury
    this->generateTexture(width, height, image);

    SOIL_free_image_data(image);
}

Texture::Texture(std::vector<std::string> faces)
{
    glGenTextures(1, &this->ID);
    this->_imgFormat = GL_RGB;
    this->_internalFormat = GL_RGB;
    this->_wrapS = GL_CLAMP_TO_EDGE;
    this->_wrapT = GL_CLAMP_TO_EDGE;
    this->_filterMax = GL_LINEAR;
    this->_filterMin = GL_LINEAR;

    this->generateTexCubeMap(faces);
}

void Texture::generateTexture(GLuint width, GLuint height, unsigned char* data)
{
    this->_height = height;
    this->_width = width;
    if(data) std::cout<<"Loaded"<<std::endl;
    else std::cout<<"Did not load"<<std::endl;
    //Ustawienie tekstury ID jako obecnie przetwarzanej
    glBindTexture(GL_TEXTURE_2D, this->ID);
    //Konfiguracja parametrów tekstury
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->_wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->_wrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->_filterMin);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->_filterMax);
    //Generacja wynikowej tekstury
    glTexImage2D(GL_TEXTURE_2D, 0, this->_internalFormat, width, height,
                 0, this->_imgFormat, GL_UNSIGNED_BYTE, data);

    glBindTexture(GL_TEXTURE_2D, 0);

}
void Texture::generateTexCubeMap(std::vector<std::string> faces)
{
    glBindTexture(GL_TEXTURE_CUBE_MAP, this->ID);

    int width, height;
    for(unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char* image = SOIL_load_image(faces[i].c_str(),&width, &height, 0, SOIL_LOAD_RGB);
        if(image)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X	 + i, 0,
                          GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
            SOIL_free_image_data(image);
        }
        else
        {
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            SOIL_free_image_data(image);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

}
//Ustawienie tekstury, jako obecnie przetwarzanej
void Texture::Bind() const
{
    glBindTexture(GL_TEXTURE_2D, this->ID);
}
//Ustawienie tekstury skybox, jako obecnie przetwarzanej
void Texture::BindCubeMap() const
{
    glBindTexture(GL_TEXTURE_CUBE_MAP, this->ID);
}

