#include <iostream>

#include "DroidGame.h"
#include "Resources.h"

void processInput(GLFWwindow *window);

const unsigned int GAME_WIDTH = 1000;//Szerokość okna
const unsigned int GAME_HEIGHT = 540;//Wysokość okna


int main()
{
	//Tworzenie gry z nazwą oraz rozmiarami okna aplikacji
	Game* newGame = new DroidGame("Droid", GAME_WIDTH, GAME_HEIGHT);

	newGame->initGame();//Inicjalizacja okna glfw, OpenGL
	newGame->loadGame();//ładowanie wszystkich zasobów gry
	newGame->setGameState(ACTIVE);//Ustawienie trybu gry

	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;

	//Główna pętla aplikacji
	while (!glfwWindowShouldClose(newGame->_window))
	{
		//Obliczamy delta time
		GLfloat thisFrame = glfwGetTime();
		deltaTime = thisFrame - lastFrame;
		lastFrame = thisFrame;

		glfwPollEvents();
		processInput(newGame->_window);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//Aktualizacja gry, wszystkich obiektów, parametrów
		newGame->updateGame(deltaTime);
		//Rysowanie całej sceny
		newGame->renderGame();

		glfwSwapBuffers(newGame->_window);
	}
	delete newGame;
	glfwTerminate();
	return 0;
}


void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
