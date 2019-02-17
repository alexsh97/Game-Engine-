#include "Game.h"
#include "Resources.h"
#include "Shader.h"
#include "Texture.h"
#include "Plane.h"
#include "Cuboid.h"
#include "Pyramid.h"
#include <math.h>
#include <glm/glm.hpp>
#include "TextRender.h"

GLboolean Game::_keys[1024];
Rendering* Game::render = nullptr;

GameState Game::_state = ACTIVE;
std::string texttest;

Game::Game(const char* name, GLuint width, GLuint height)
{
    this->_width = width;
    this->_height = height;
    this->_name = name;
    std::cout<<"Created game!"<<std::endl;
  
}

Game::~Game()
{
    
}

void Game::setGameState(GameState state)
{
    _state = state;
    std::cout<<"state:" << state<<std::endl;
}

void Game::initGame()
{
    glfwInit();//Inicjalizacja GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//Określa wersję interfejsu API klienta, z którą musi być zgodny utworzony kontekst
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//W przypadku tego projektu wersja jest - 3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//Używanie profulu podstawowego

    this->_window = glfwCreateWindow(this->_width, this->_height, this->_name, NULL, NULL);//Tworzenie okna GLFW
    //Sprawdzenie czy okno udało się stworzyć czy nie
    if (this->_window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return ;
    }
    //Ustawienie utworzonego okna jako aktualne
    glfwMakeContextCurrent(this->_window);
    //Ładowanie biblioteki GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return ;
    }
    //Ustawienie callback funkcji
    glfwSetFramebufferSizeCallback(_window, framebufferSizeCallback);//Zdarzenie zmainy rozmiarów okna
    glfwSetKeyCallback(_window, keyCallback);//Zdarzenia klawiszy klawiatury
    glfwSetScrollCallback(_window, scrollCallback);//Zdarzenie kółka myszy

    //Ustawienia dodające głębokość oraz obsługe kanału alfa
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //Ukrywa kursor myszy, gdy on jest w oknie window
    glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

void Game::loadGame()
{  /*
    std::cout<<"Init game!"<<std::endl;
    //Tworzenie poziomów dla gry
    Levels.push_back(Level("Tatooine"));
    Levels.push_back(Level("Station"));

    //Shader txtShader("resource\\shaders\\TextShader.vs", "resource\\shaders\\TextShader.fs");
    //Inicjalizacja
    TextRender::initTextRender(new Shader("resource\\shaders\\TextShader.vs", "resource\\shaders\\TextShader.fs"));
    //Ładowanie shaderow
    Resources::loadShader("resource\\shaders\\ObjectShaderLight.vs", "resource\\shaders\\ObjectShaderLight.fs", nullptr,"object");
    Resources::loadShader("resource\\shaders\\SkyBoxShader.vs", "resource\\shaders\\SkyBoxShader.fs", nullptr,"skybox");
    //Ładowanie tekstur
    Resources::loadTexture("resource\\textures\\brickwall.jpg",GL_FALSE, "brickwall");
    Resources::loadTexture("resource\\textures\\wallDesert.jpeg",GL_FALSE, "desertWall");
    Resources::loadTexture("resource\\textures\\sand2.jpg",GL_FALSE, "sand2");
    Resources::loadTexture("resource\\textures\\sand1.jpg",GL_FALSE, "sand1");
    Resources::loadTexture("resource\\textures\\body.jpg", GL_FALSE,"tshirt");
    Resources::loadTexture("resource\\textures\\Scorpion.png",GL_TRUE, "awesomeface");
    Resources::loadTexture("resource\\textures\\trigger.png",GL_TRUE, "container");
    Resources::loadTexture("resource\\textures\\SpaceWall4.png",GL_TRUE, "spacefloor");
    Resources::loadTexture("resource\\textures\\portal.png",GL_TRUE, "portal");
    Resources::loadTexture("resource\\textures\\Roof.jpg",GL_FALSE, "roof");
    Resources::loadTexture("resource\\textures\\fence.png",GL_TRUE, "fence");
    Resources::loadTexture("resource\\textures\\brickwall.jpg",GL_FALSE, "wallspace");

    vector<std::string> faces = {"resource\\textures\\skybox\\right.jpg", "resource\\textures\\skybox\\left.jpg", "resource\\textures\\skybox\\top.jpg",
    "resource\\textures\\skybox\\bottom.jpg", "resource\\textures\\skybox\\front.jpg", "resource\\textures\\skybox\\back.jpg"};
    Resources::loadTexCubeMap(faces, "skybox1");
    //Ładowanie audio
    Resources::loadAudio("resource\\audio\\SWmusic1.mp3", "SW_background");
    Resources::loadAudio("resource\\audio\\R2D2_movement.mp3", "R2D2voice");
    Resources::loadAudio("resource\\audio\\flying.mp3", "R2D2fly");

    //Tworzenie postaci gracza
    player = new Player("hero", glm::vec3(0.0f,1.04f,0.0f), glm::vec3(0.3f,0.8f,0.5f), 90.0f, glm::vec3(0.0f,1.0f,0.0f));
    //Tworzenie kamery
    Camera camera1(glm::vec3(0.0f,3.0f,5.0f), player->getPosition() + glm::vec3(0.0f,0.5f,0.0f), glm::vec3(0.0f,1.0f,0.0f), 50.0f);
    //Przygotowanie silnika renderingu
    render = new Rendering(Resources::getShader("object"), camera1);
    render->setDirLight(glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.2f, 0.2f, 0.2f),glm::vec3( 0.05f, 0.05f, 0.05f),glm::vec3(0.0f, 0.0f, 0.0f));
    render->setSpotLight(glm::vec3(1.01f,0.0f,0.0f), new Light("spot", player->getPosition() + glm::vec3(0.0f,0.5f,0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.5f), glm::vec3(1.0f, 1.0f, 1.0f)));
    render->addPointLight(new Light("light1", glm::vec3(0.0f,0.5f,0.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f)));
    render->addPointLight(new Light("light2", glm::vec3(-5.0f,0.5f,1.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.8f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f)));

    loadLevels();
    texttest = Levels[level]._name;
    pressKey = "";

    Resources::getAudio("SW_background")->playAudio(GL_TRUE);
    */
}

void Game::updateGame(GLfloat dt)
{/*
    if(this->_state == ACTIVE)
    {

         this->render->_spotLight->setPosition(player->getPosition() + glm::vec3(0.0f,0.5f,0.0f));

         if(this->_keys[GLFW_KEY_LEFT])
            this->render->_camera.slideCamera(-dt);
         if(this->_keys[GLFW_KEY_RIGHT])
            this->render->_camera.slideCamera(dt);

         if(this->_keys[GLFW_KEY_0])
            level = 0;

         if(this->_keys[GLFW_KEY_1])
            level = 1;


         if(this->_keys[GLFW_KEY_W])
         {
             player->forwardMove(glm::vec3(dt,0.0f,0.0f));
             this->render->_spotLight->setDirection(0.01f*player->_direction);
            if(this->collisions())
            {
                //player->forwardMove(glm::vec3(-dt,0.0f,0.0f));
                player->backMove(glm::vec3(dt,0.0f,0.0f));
            }
            else this->render->_camera.moveCamera(glm::vec3(dt,0.0f,0.0f));
         }
         if(this->_keys[GLFW_KEY_S])
         {
             if(!this->collisions())
            {
              player->forwardMove(glm::vec3(-dt,0.0f,0.0f));
              this->render->_spotLight->setDirection(-0.01f*player->_direction);
             this->render->_camera.moveCamera(glm::vec3(-dt,0.0f,0.0f));
            }
         }
         if(this->_keys[GLFW_KEY_D])
         {
             if(!this->collisions())
            {
              player->forwardMove(glm::vec3(0.0f,0.0f,dt));
              this->render->_spotLight->setDirection(0.01f*player->_direction);
             this->render->_camera.moveCamera(glm::vec3(0.0f,0.0f,dt));
            }
         }
         if(this->_keys[GLFW_KEY_A])
         {
            player->forwardMove(glm::vec3(0.0f,0.0f,-dt));
            this->render->_spotLight->setDirection(-0.01f*player->_direction);
            if(this->collisions())
            {
                player->forwardMove(glm::vec3(0.0f,0.0f,dt));
                 //player->backMove(glm::vec3(-dt,0.0f,0.0f));
            }
            else this->render->_camera.moveCamera(glm::vec3(0.0f,0.0f,-dt));
         }

         if(this->_keys[GLFW_KEY_W] || this->_keys[GLFW_KEY_S] || this->_keys[GLFW_KEY_A] || this->_keys[GLFW_KEY_D])
            {
                if(!Resources::getAudio("R2D2voice")->isActive)
                    Resources::getAudio("R2D2voice")->playAudio(GL_FALSE);
            }

         if(!this->_keys[GLFW_KEY_W] && !this->_keys[GLFW_KEY_S] && !this->_keys[GLFW_KEY_A] && !this->_keys[GLFW_KEY_D])
         {
             if(Resources::getAudio("R2D2voice")->isActive)
                    Resources::getAudio("R2D2voice")->stopAudio();
         }

         if(this->_keys[GLFW_KEY_T])
         {
             if(this->render->_spotLight->getDiffuse().x > 0.0f)
                this->render->_spotLight->setDiffuse(glm::vec3(0.0f,0.0f,0.0f));
             else this->render->_spotLight->setDiffuse(glm::vec3(1.0f, 1.0f, 1.5f));
             this->_keys[GLFW_KEY_T] = false;
         }

          player->gravityMove(dt);

         if(this->collisions())
         {
             player->gravityMove(-dt);
         }
         if(player->getPosition().y < -1.5f)
         {
             player->resetPlayer();
             this->render->_camera.resetCamera();
         }

         //Animate ship
         Levels[0].allObjects["space"]->_angel += dt*(-100);
         Levels[0].allObjects["space"]->_position = glm::vec3(sin(Levels[0].allObjects["space"]->_angel/99)*5, 2.0f, cos(Levels[0].allObjects["space"]->_angel/99)*5);

         if(checkCollision(player, Levels[level].allTriggers["GoNextLevel"]))
         {
            pressKey = "Press E";
            if(this->_keys[GLFW_KEY_E])
            {
                level = level == 0 ? 1 : 0;
                player->resetPlayer();
                this->render->_camera.resetCamera();
            }
         }
         else pressKey = "";

         if(this->_keys[GLFW_KEY_SPACE])
         {
             player->Jump(dt);
             this->render->_camera.setTarget(player->getPosition() + glm::vec3(0.0f,0.5f,0.0f));
             if(!Resources::getAudio("R2D2fly")->isActive)
                    Resources::getAudio("R2D2fly")->playAudio(GL_FALSE);
             //this->_keys[GLFW_KEY_SPACE] = false;
         }
         else
         {
            if(Resources::getAudio("R2D2fly")->isActive)
                Resources::getAudio("R2D2fly")->stopAudio();
         }
         this->render->_camera.setTarget(player->getPosition() + glm::vec3(0.0f,0.5f,0.0f));
         this->render->_camera._position.y = player->getPosition().y + 3.0f;
    }*/
}
void Game::renderGame()
{/*
    player->drawObject(*this->render);

    for(const auto& obj : Levels[level].allObjects)
    {
        (obj.second)->drawObject(*this->render);
    }
   Levels[level].allTriggers["GoNextLevel"]->drawObject(*this->render);

   TextRender::drawText(Levels[level]._name, glm::vec2(25.0f, 25.0f), 1.0f, glm::vec3(0.5, 0.5f, 0.5f));
   TextRender::drawText(pressKey, glm::vec2(480.0f, 400.0f), 0.4f, glm::vec3(1.0, 1.0f, 1.0f));

   this->drawSkyBox(Resources::getShader("skybox"),"skybox1");

   if(this->_state == MENU)
   {
        TextRender::drawText("PAUSE", glm::vec2(480.0f, 400.0f), 1.4f, glm::vec3(1.0, 1.0f, 1.0f));
   }*/
}


void Game::loadLevels()
{/*
    //Tworzenie obiektów dla pierwszego levelu
     Levels[0].addObject(new Plane("Wall_1", glm::vec3(0.0f,2.5f,-10.0f), glm::vec3(20.0f,5.0f,0.01f), -10.0f, glm::vec3(1.0f, 0.0f, 0.0f), Resources::getTexture("desertWall")));
     Levels[0].addObject(new Plane("Wall_2", glm::vec3(0.0f,1.5f, 10.0f), glm::vec3(20.0f,3.0f,0.01f), -1.0f, glm::vec3(1.0f, 0.0f, 0.0f), Resources::getTexture("desertWall")));
     Levels[0].addObject(new Plane("plane2", glm::vec3(0.0f,0.0f,0.0f), glm::vec3(20.0f,0.06f,20.0f), -90.0f, glm::vec3(1.0f, 0.0f, 0.0f), Resources::getTexture("sand2")));
     Levels[0].addObject(new Plane("plane1", glm::vec3(20.0f,0.0f,0.0f), glm::vec3(20.0f,0.06f,20.0f), -90.0f, glm::vec3(1.0f, 0.0f, 0.0f), Resources::getTexture("sand2")));
     Levels[0].addObject(new Cuboid("cube", glm::vec3(0.5f,0.4f,9.0f), glm::vec3(0.3f,0.8f,0.5f), 180.0f, glm::vec3(1.0f, 0.0f, 0.0f), Resources::getTexture("sand2")));
     Levels[0].addObject(new Model("resource\\objects\\space\\Sample_Ship.obj", "space", glm::vec3(-5.0f,2.0f, 0.0f), glm::vec3(2.0f, 2.0f, 2.0f), 0.0f, glm::vec3(0.0f,1.0f,0.0f)));
     Levels[0].addObject(new Pyramid("pyramid", glm::vec3(4.0f,0.1f,3.0f), glm::vec3(0.5f,0.5f,0.5f), 0.0f, glm::vec3(1.0f, 0.0f, 0.0f), Resources::getTexture("sand1")));
     Levels[0].addObject(new Pyramid("BigPyramid", glm::vec3(25.0f,5.0f, 0.0f), glm::vec3(15.0f,15.0f,15.0f), 0.0f, glm::vec3(1.0f, 0.0f, 0.0f), Resources::getTexture("sand1")));
     Levels[0].addObject(new Plane("fence", glm::vec3(0.0f,1.0f,-5.0f), glm::vec3(3.0f,2.0f,0.01f), -1.0f, glm::vec3(1.0f, 0.0f, 0.0f), Resources::getTexture("fence")));
     Levels[0].addTrigger(new Plane("GoNextLevel", glm::vec3(5.0f,0.5f,0.0f), glm::vec3(1.0f,1.0f,1.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f), Resources::getTexture("portal")));
    //Tworzenie obiektów dla drugiego levelu
     Levels[1].addTrigger(new Plane("GoNextLevel", glm::vec3(0.0f,0.5f,-1.3f), glm::vec3(1.0f,1.0f,1.5f), 180.0f, glm::vec3(1.0f, 0.0f, 0.0f), Resources::getTexture("portal")));
     Levels[1].addObject(new Plane("SpaceFloor", glm::vec3(0.0f,0.0f,0.0f), glm::vec3(10.0f,0.06f,3.0f), -90.0f, glm::vec3(1.0f, 0.0f, 0.0f), Resources::getTexture("spacefloor")));
     Levels[1].addObject(new Plane("SpaceWall", glm::vec3(0.0f,1.0f,-1.5f), glm::vec3(10.0f,2.0f,0.01f), 0.0f, glm::vec3(1.0f, 0.0f, 0.0f), Resources::getTexture("wallspace")));
*/
}

bool Game::checkCollision(Player* p, GameObject *obj) const
{
    bool collX = (p->getPosition().x + p->_collisionDetection.x/2.0) >= (obj->_position.x - obj->_size.x/2.0) &&
     (p->getPosition().x - p->_collisionDetection.x/2.0 )<= (obj->_position.x + obj->_size.x/2.0);
    bool collY = (p->getPosition().y + p->_collisionDetection.y)>= (obj->_position.y - obj->_size.y/2.0) &&
    (p->getPosition().y) <= (obj->_position.y + obj->_size.y/2.0);
    bool collZ = (p->getPosition().z + p->_collisionDetection.z/2.0)>= (obj->_position.z - obj->_size.z/2.0) &&
     (p->getPosition().z - p->_collisionDetection.z/2.0)<= (obj->_position.z + obj->_size.z/2.0);

    return collX && collY && collZ;
}
bool Game::collisions() const
{
    for(const auto& obj : Levels[level].allObjects)
    {
            if(checkCollision(player, obj.second))
            {
                return true;
            }
    }
    return false;
}

void Game::drawSkyBox(Shader* skyShader, std::string name)
{
    //Tekstura skyboxu
    unsigned int cubemapTexture = Resources::getTexture("skybox1").ID;
    //Dane wierzchołków
    float skyboxVertices[] =
    {
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f
    };

    //Generacja VAO i VBO dla skyboxu
    unsigned int skyVAO, skyVBO;
    glGenVertexArrays(1, &skyVAO);
    glGenBuffers(1, &skyVBO);
    glBindVertexArray(skyVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE,3 * sizeof(float), (void*)0);

    glDepthFunc(GL_LEQUAL);
    skyShader->use();
    //Macierze widoku i projekcji
	glm::mat4 view = this->render->_camera._view;
    glm::mat4 projection = this->render->_camera._projection;
    skyShader->setMat4("view",view);
    skyShader->setMat4("projection", projection);
	//Macierz transforamcji
    glm::mat4 model;
    model = glm::translate(model, player->getPosition());
    model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f,1.0f,0.0f));
    skyShader->setMat4("model", model);

    glBindVertexArray(skyVAO);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glDepthFunc(GL_LESS);

}

void Game::framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void Game::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if(key >= 0 && key < 1024)
    {
        if(action == GLFW_PRESS)
        {
            _keys[key] = GL_TRUE;

        }
        else if (action == GLFW_RELEASE)
        {
            if(key == GLFW_KEY_P)
            {
                std::cout<<"PAUSE";
                _state = _state == ACTIVE ? MENU : ACTIVE;
            }
            _keys[key] = GL_FALSE;
        }
    }

}

void Game::scrollCallback(GLFWwindow *window, double xoffset, double yoffset)
{
    float projection = render->_camera._fov;

    if (projection >= 20.0f && projection <= 80.0f)
        projection -= yoffset;
    if (projection <= 20.0f)
        projection = 20.0f;
    if (projection >= 80.0f)
        projection = 80.0f;

    render->_camera.setProjection(projection);
}
