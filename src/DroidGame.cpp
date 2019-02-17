#include "DroidGame.h"

 void DroidGame::loadGame()
    {
        std::cout<<"Init game!"<<std::endl;

    //Inicjalizacja silnika do renderowania tekstu
    TextRender::initTextRender(new Shader("resource\\shaders\\TextShader.vs", "resource\\shaders\\TextShader.fs"));
    //Ładowanie shaderow
    Resources::loadShader("resource\\shaders\\ObjectShaderLight.vs", "resource\\shaders\\ObjectShaderLight.fs", nullptr,"object");
    Resources::loadShader("resource\\shaders\\SkyBoxShader.vs", "resource\\shaders\\SkyBoxShader.fs", nullptr,"skybox");
    //Ładowanie tekstur
    Resources::loadTexture("resource\\textures\\brickwall.jpg",GL_FALSE, "brickwall");
    Resources::loadTexture("resource\\textures\\wallDesert.jpeg",GL_FALSE, "desertWall");
    Resources::loadTexture("resource\\textures\\sand2.jpg",GL_FALSE, "sand2");
    Resources::loadTexture("resource\\textures\\sand1.jpg",GL_FALSE, "sand1");
    Resources::loadTexture("resource\\textures\\pyramide.jpg",GL_FALSE, "pyramide");
    Resources::loadTexture("resource\\textures\\body.jpg", GL_FALSE,"tshirt");
    Resources::loadTexture("resource\\textures\\trigger.png",GL_TRUE, "container");
    Resources::loadTexture("resource\\textures\\SpaceWall4.png",GL_TRUE, "spacefloor");
    Resources::loadTexture("resource\\textures\\portal.png",GL_TRUE, "portal");
    Resources::loadTexture("resource\\textures\\Roof.jpg",GL_FALSE, "roof");
    Resources::loadTexture("resource\\textures\\fence.png",GL_TRUE, "fence");
	Resources::loadTexture("resource\\textures\\Fire.png", GL_TRUE, "fire");
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
    Camera camera1(glm::vec3(0.0f,3.0f,5.0f),
                   player->getPosition() + glm::vec3(0.0f,0.5f,0.0f), glm::vec3(0.0f,1.0f,0.0f), 50.0f);
    //Przygotowanie silnika renderingu
    render = new Rendering(Resources::getShader("object"), camera1);
    render->setDirLight(glm::vec3(0.0f,0.0f,0.0f),
                        glm::vec3(0.2f, 0.2f, 0.2f),glm::vec3( 0.05f, 0.05f, 0.05f),glm::vec3(0.0f, 0.0f, 0.0f));
    render->setSpotLight(glm::vec3(1.01f,0.0f,0.0f), new Light("spot", player->getPosition() + glm::vec3(0.0f,0.5f,0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.5f), glm::vec3(1.0f, 1.0f, 1.0f)));
    render->addPointLight(new Light("light1", glm::vec3(0.0f,0.5f,0.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f)));
    render->addPointLight(new Light("light2", glm::vec3(-5.0f,0.5f,1.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.8f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f)));
    render->addPointLight(new Light("light3", glm::vec3(-1.0f,1.5f,-1.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.1f, 0.3f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f)));

    //Tworzenie poziomów dla gry
    Levels.push_back(Level("Tatooine"));
    Levels.push_back(Level("Station"));
    prepareLevels();
	this->level = 0;
    GUI::levelName = Levels[level]._name;

    Resources::getAudio("SW_background")->playAudio(GL_TRUE);

    }
    void DroidGame::updateGame(GLfloat dt)
    {
        //Jeżeli stan gry jest ACTIVE, można grać
        if(this->_state == ACTIVE)
        {
             //Strumień światła przemieszcza się razem z graczem
             this->render->_spotLight->setPosition(player->getPosition() + glm::vec3(0.0f,0.5f,0.0f));
             //Kamera się kręci wokół gracza
             if(this->_keys[GLFW_KEY_LEFT])
                this->render->_camera.slideCamera(-dt);
             if(this->_keys[GLFW_KEY_RIGHT])
                this->render->_camera.slideCamera(dt);
             //Ruch po scenie
             if(this->_keys[GLFW_KEY_W])
             {
                 player->forwardMove(glm::vec3(dt,0.0f,0.0f));
                 this->render->_spotLight->setDirection(0.01f*player->_direction);
                if(this->collisions())//Sprawdzenie kolizji
                {   //Jeżeli postać jest w innym obiekcie, robimy krok w tył
                    player->backMove(glm::vec3(dt,0.0f,0.0f));
                }
                else this->render->_camera.moveCamera(glm::vec3(dt,0.0f,0.0f));//Kamera się przemieszcza razem z graczem
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
             //Jeżeli gracz  przemieszcza się, wówczas włączany jest dżwięk ruchu
             if(this->_keys[GLFW_KEY_W] || this->_keys[GLFW_KEY_S] || this->_keys[GLFW_KEY_A] || this->_keys[GLFW_KEY_D])
            {
                    if(!Resources::getAudio("R2D2voice")->isActive)
                        Resources::getAudio("R2D2voice")->playAudio(GL_FALSE);
            }

             else//if(!this->_keys[GLFW_KEY_W] && !this->_keys[GLFW_KEY_S] && !this->_keys[GLFW_KEY_A] && !this->_keys[GLFW_KEY_D])
             {
                 if(Resources::getAudio("R2D2voice")->isActive)
                        Resources::getAudio("R2D2voice")->stopAudio();
             }
             //Włączenie\wyłączenie strumieni światła
             if(this->_keys[GLFW_KEY_T])
             {
                 if(this->render->_spotLight->getDiffuse().x > 0.0f)
                    this->render->_spotLight->setDiffuse(glm::vec3(0.0f,0.0f,0.0f));
                 else this->render->_spotLight->setDiffuse(glm::vec3(1.0f, 1.0f, 1.5f));
                 this->_keys[GLFW_KEY_T] = false;
             }

              player->gravityMove(dt);//ruch gracza po osi Y

             if(this->collisions())//Sprawdzenie kolizji - czy jest ziemia\podłoga
             {
                 player->gravityMove(-dt);
             }
             if(player->getPosition().y < -1.5f)//Jeżeli gracz upadł, to wraca się na początkowe miejsce
             {
                 player->resetPlayer();
                 this->render->_camera.resetCamera();
             }

             //Animacja statku kosmicznego
             Levels[0].allObjects["space"]->_angel += dt*(-100);
             Levels[0].allObjects["space"]->_position = glm::vec3(sin(Levels[0].allObjects["space"]->_angel/99)*5, 2.0f, cos(Levels[0].allObjects["space"]->_angel/99)*5);
             //Trigger, jeżeli jest kolizja z triggerem, wtedy można nacisnąć E i zmienić poziom
             if(checkCollision(player, Levels[level].allTriggers["GoNextLevel"]))
             {
                GUI::keyToPress = "Press E";
                if(this->_keys[GLFW_KEY_E])
                {
                    level = level == 0 ? 1 : 0;
                    player->resetPlayer();
                    this->render->_camera.resetCamera();
                }
             }
             else  GUI::keyToPress = "";

			 //Jeśli gracz przejdzie przez ogień, to straci kawałek zycia
			 if (checkCollision(player, Levels[0].allTriggers["fire"]))
			 {
				 player->_health -= 0.1;
				 GUI::playerHP = std::to_string(player->_health);
			 }
             //Skok
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
             //Kamera zawsze śledzi gracza
             this->render->_camera.setTarget(player->getPosition() + glm::vec3(0.0f,0.5f,0.0f));
             this->render->_camera._position.y = player->getPosition().y + 3.0f;

			 //Jeżeli poziom życia gracza jest 0 lub niżej, wówczas gra jest resetowana
			 if (player->_health <= 0)
			 {
				 player->resetPlayer();
				 this->render->_camera.resetCamera();
				 player->_health = 100;
				 GUI::playerHP = std::to_string(player->_health);
			 }
        }

    }
    void DroidGame::renderGame()
    {
        //Rysowanie nieba
        this->drawSkyBox(Resources::getShader("skybox"),"skybox1");
        //Rusowanie gracza
        player->drawObject(*this->render);
        //Rysowanie wszystkich obiektów sceny
        for(const auto& obj : Levels[level].allObjects)
        {
            (obj.second)->drawObject(*this->render);
        }
       Levels[level].allTriggers["GoNextLevel"]->drawObject(*this->render);
	   if(level == 0)
			Levels[0].allTriggers["fire"]->drawObject(*this->render);
        //Rysowanie nazwy levelu
       TextRender::drawText(Levels[level]._name, glm::vec2(25.0f, 25.0f), 1.0f, glm::vec3(0.5, 0.5f, 0.5f));
       TextRender::drawText(GUI::keyToPress, glm::vec2(480.0f, 400.0f), 0.4f, glm::vec3(1.0, 1.0f, 1.0f));
       TextRender::drawText(GUI::playerHP, glm::vec2(50.0f,450.0f),0.5f,glm::vec3(1.0f,0.0f,0.0f));


       if(this->_state == MENU)
       {
            TextRender::drawText("PAUSE", glm::vec2(480.0f, 400.0f), 1.4f, glm::vec3(1.0, 1.0f, 1.0f));
       }
    }

    void DroidGame::prepareLevels()
    {
        //Tworzenie obiektów dla pierwszego levelu
         Levels[0].addObject(new Plane("Wall_1", glm::vec3(0.0f,2.5f,-10.0f), glm::vec3(20.0f,5.0f,0.01f), -10.0f, glm::vec3(1.0f, 0.0f, 0.0f), Resources::getTexture("desertWall")));
         Levels[0].addObject(new Plane("Wall_2", glm::vec3(0.0f,1.5f, 10.0f), glm::vec3(20.0f,3.0f,0.01f), 180.0f, glm::vec3(0.0f, 1.0f, 0.0f), Resources::getTexture("desertWall")));
         Levels[0].addObject(new Plane("plane2", glm::vec3(0.0f,0.0f,0.0f), glm::vec3(20.0f,0.06f,20.0f), -90.0f, glm::vec3(1.0f, 0.0f, 0.0f), Resources::getTexture("sand2")));
         Levels[0].addObject(new Plane("plane1", glm::vec3(20.0f,0.0f,0.0f), glm::vec3(20.0f,0.06f,20.0f), -90.0f, glm::vec3(1.0f, 0.0f, 0.0f), Resources::getTexture("sand2")));
         Levels[0].addObject(new Cuboid("cube", glm::vec3(0.5f,0.4f,2.0f), glm::vec3(0.3f,0.8f,1.5f), 180.0f, glm::vec3(1.0f, 0.0f, 0.0f), Resources::getTexture("roof")));
         Levels[0].addObject(new Model("resource\\objects\\space\\Sample_Ship.obj", "space", glm::vec3(-5.0f,2.0f, 0.0f), glm::vec3(2.0f, 2.0f, 2.0f), 0.0f, glm::vec3(0.0f,1.0f,0.0f)));
         Levels[0].addObject(new Pyramid("pyramid", glm::vec3(4.0f,0.1f,3.0f), glm::vec3(0.5f,0.5f,0.5f), 0.0f, glm::vec3(1.0f, 0.0f, 0.0f), Resources::getTexture("sand1")));
         Levels[0].addObject(new Pyramid("BigPyramid", glm::vec3(25.0f,5.0f, 0.0f), glm::vec3(15.0f,15.0f,15.0f), 0.0f, glm::vec3(1.0f, 0.0f, 0.0f), Resources::getTexture("brickwall")));
         Levels[0].addObject(new Plane("fence", glm::vec3(0.0f,1.0f,-5.0f), glm::vec3(3.0f,2.0f,0.01f), -1.0f, glm::vec3(1.0f, 0.0f, 0.0f), Resources::getTexture("fence")));
		 Levels[0].addTrigger(new Cuboid("fire", glm::vec3(7.0f, 0.5f, 5.0f), glm::vec3(3.0f, 1.0f, 0.01f), -1.0f, glm::vec3(1.0f, 0.0f, 0.0f), Resources::getTexture("fire")));
         Levels[0].addTrigger(new Plane("GoNextLevel", glm::vec3(5.0f,0.5f,0.0f), glm::vec3(1.0f,1.0f,1.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f), Resources::getTexture("portal")));
        //Tworzenie obiektów dla drugiego levelu
         Levels[1].addTrigger(new Plane("GoNextLevel", glm::vec3(0.0f,0.5f,-1.3f), glm::vec3(1.0f,1.0f,1.5f), 180.0f, glm::vec3(1.0f, 0.0f, 0.0f), Resources::getTexture("portal")));
         Levels[1].addObject(new Plane("SpaceFloor", glm::vec3(0.0f,0.0f,0.0f), glm::vec3(10.0f,0.06f,3.0f), -90.0f, glm::vec3(1.0f, 0.0f, 0.0f), Resources::getTexture("spacefloor")));
         Levels[1].addObject(new Plane("SpaceWall", glm::vec3(0.0f,1.0f,-1.5f), glm::vec3(10.0f,2.0f,0.01f), 0.0f, glm::vec3(1.0f, 0.0f, 0.0f), Resources::getTexture("wallspace")));

    }
