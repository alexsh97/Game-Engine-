#ifndef Camera_H
#define Camera_H
//Klasa kamery
class Camera
{
public:
    GLfloat x,y,z;//Położenie kamery w przestrzeni 3D
    GLfloat _movement;
    GLfloat _fov;//Field of view - pole widzenia
    glm::vec3 _position;//Położenie kamery w przestrzeni 3D
    glm::vec3 _target;//Punkt na który kamera "patrzy"
    glm::vec3 _up;//Wektor wskazujący gdzie jest góra
    glm::mat4 _projection;//Typ projekcji : perspective lub orthographic
    glm::mat4 _view;//Spojrzenie kamery

	/**
		Konstruktor domyślny
	*/
    Camera()
    {
        this->x = 0.0f;
        this->y = 0.0f;
        this->z = 0.0f;
        this->_movement = 0.0;
        this->_position = glm::vec3(0.0f,0.0f,0.0f);
        this->_target = glm::vec3(0.0f,0.0f,0.0f);
        this->_up = glm::vec3(0.0f,0.0f,0.0f);
        this->_fov = 45.0f;
        this->_view = glm::lookAt(this->_position, this->_target, this->_up);
        this->_projection = glm::perspective(glm::radians(_fov), (float)1000 / (float)540, 0.1f, 100.0f);
    }
    /**
        Tworzenie kamery, podane są położenie, cel, wektor góry, wartość field of view, i obliczane są spojrzenie kamery i projekcja

        @param position położenie kamery
        @param target punkt na który kamera "patrzy"
        @param up wektor wskazujący gdzie jest góra
        @param fov field of view
    */
    Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up, GLfloat fov)
    {
        this->x = 0.0f;
        this->y = 0.0f;
        this->z = 0.0f;
        this->_movement = 0.0;
        this->_position = position;
        this->_target = target;
        this->_up = up;
        this->_fov = fov;
        this->_view = glm::lookAt(this->_position, this->_target, this->_up);
        this->_projection = glm::perspective(glm::radians(_fov), (float)1000 / (float)540, 0.1f, 100.0f);
    }

    /**
        Ustawia nowe położenie dla kamery

        @param position wektor położenia
    */
    void setPosition(glm::vec3 position)
    {
        this->_position = position;
    }
    /**
        Ustawia nową wartość dla field of view

        @param fov wartość field of view
    */
    void setProjection(GLfloat fov)
    {
        this->_fov = fov;
        this->_projection = glm::perspective(glm::radians(this->_fov), (float)1000 / (float)540, 0.1f, 100.0f);
    }
    /**
        Ustawia nowe położenie punktu w który kamera patrzy

        @param target wektor położenia tego punktu
    */
    void setTarget(glm::vec3 target)
    {
        this->_target = target;
        this->_view = glm::lookAt(this->_position, this->_target, this->_up);
    }
    /**
        Ruch kamery wokół target

        @param dt delta time
    */
    void slideCamera(GLfloat dt)
    {
        this->_movement += dt;
        this->_position = glm::vec3(sin(_movement)*5.0f + x,this->_position.y,cos(_movement)*5.0f + z);
        this->_view = glm::lookAt(this->_position, this->_target, this->_up);
    }
    /**
        Ruch kamery w przestrzeni jeżeli cel się rusza. Zmiana nie tylko położenie kamery, ale jeszcze target.

        @param movement wektor prędkości ruchu
    */
    void moveCamera(glm::vec3 movement)
    {
        this->x += movement.x;
        this->z += movement.z;
        this->y += movement.y;
        this->_position = glm::vec3(sin(this->_movement)*5.0f + x,this->_position.y + this->y,cos(this->_movement)*5.0f + z);

        this->_target.x += movement.x;
        this->_target.z += movement.z;
        this->_view = glm::lookAt(this->_position, this->_target, this->_up);
    }
    /**
        Resetowanie wszystkich zmian kamery
    */
    void resetCamera()
    {
        this->x = 0.0f;
        this->y = 0.0f;
        this->z = 0.0f;
        this->_movement = 0.0;

        this->_position = glm::vec3(0.0f,3.0f,5.0f);
        this->_target = glm::vec3(0.0f,0.04f,0.0f);

        this->_view = glm::lookAt(this->_position, this->_target, this->_up);
        this->_projection = glm::perspective(glm::radians(50.0f), (float)1000 / (float)540, 0.1f, 100.0f);

    }
};

#endif // Camera_H
