#ifndef Game_H
#define Game_H

#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Level.h"
#include "Rendering.h"
#include "GameObject.h"
#include "Player.h"


enum GameState
{
    ACTIVE,
    MENU
};


class Game
{
protected:
    GLuint _width,_height;//Rozmiary okna
    const char* _name;//Nazwa okna(gry)
    static GameState _state;//Stan gry
    static Rendering *render;//Silnik renderowania
    Player *player;//Gracz
    int level;//Obecnie wybrany poziom gry

    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
    static void scrollCallback(GLFWwindow *window, double xoffset, double yoffset);

public:

    GLFWwindow* _window;//Okno
    std::vector<Level> Levels;//Zbiór poziomów gry
    static GLboolean _keys[1024];//Tablica klawisze

    Game(const char* name, GLuint width, GLuint height);
    virtual ~Game();
    /**
		Ustawienie stanu gry

		@param state stan gry: ACTIVE, MENU
    */
    void setGameState(GameState state);
     /**
		Inicjalizacja aplikacji: tworzenie okna, konfiguracja glfw oraz OpenGL
    */
    void initGame();
     /**
		Ładowanie wszystkich zasobów do gry, tworzenie silnika renderingu (oświetlenie, kamera)
    */
    virtual void loadGame();
     /**
		Aktualizacja gry, obsługa zdarzeń klawiatury i myszy
    */
    virtual void updateGame(GLfloat dt);
     /**
		Rysowanie wszystkich obiektów sceny
    */
    virtual void renderGame();
     /**
		Dodawanie obiektów do gry
    */
    void loadLevels();
     /**
			Sprawdzenie wystąpenia kolizji gracza z każdym obiektem
    */
    bool collisions() const;
     /**
		Sprawdzenie wystąpenia kolizji gracza wybranym obiektem

		@param p postać gracza
		@param obj obiekt z którym może się zdarzyć kolizja

		@return true w przypadku wystąpenia kolizji
    */
    bool checkCollision(Player* p, GameObject *obj) const;
     /**
			Rysowanie skyboxu

			@param skyShader program cieniujący używany do rysowania nieba
			@param name nazwa skyboxu do rysowania
    */
    void drawSkyBox(Shader* skyShader, std::string name);

};

#endif // Game_H
