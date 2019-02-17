#include "Cuboid.h"

Cuboid::Cuboid(std::string name, glm::vec3 position, glm::vec3 objsize, GLfloat angel, glm::vec3 rotation, Texture texture): GameObject(name, position, objsize, angel, rotation, texture)
{

    float vertices[] = {
        // positions           normalize         texture coords
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  -1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  -1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  -1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  -1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  -1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  -1.0f, 0.0f, 0.0f,  1.0f, 1.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f, 0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f, 0.0f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f, 0.0f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f, 0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f, 0.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f, 0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f
    };


    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Cuboid::drawObject(Rendering &render)
{

    glBindVertexArray(VAO);

    render._shader->use();
   //LIGHT
    render._shader->setVec3("viewPos", render._camera._position);

    render._shader->setVec3("dirLight.direction", render._dirLight->getDirection());
    render._shader->setVec3("dirLight.ambient", render._dirLight->getAmbient());
    render._shader->setVec3("dirLight.diffuse", render._dirLight->getDiffuse());
    render._shader->setVec3("dirLight.diffuse", render._dirLight->getSpecular());

    render._shader->setInt("lightSize", render._pointLight.size());

        for(unsigned int i=0; i < render._pointLight.size(); i++)
        {
            std::string str = "pointLight[" + std::to_string(i);
            render._shader->setVec3(str + "].position", render._pointLight[i]->getPosition());
            render._shader->setVec3(str + "].ambient", render._pointLight[i]->getAmbient());
            render._shader->setVec3(str + "].diffuse", render._pointLight[i]->getDiffuse());
            render._shader->setVec3(str + "].specular", render._pointLight[i]->getSpecular());
        }

    render._shader->setVec3("spotLight.position", render._spotLight->getPosition());
    render._shader->setVec3("spotLight.direction", render._spotLight->getDirection());
    render._shader->setVec3("spotLight.ambient", render._spotLight->getAmbient());
    render._shader->setVec3("spotLight.diffuse", render._spotLight->getDiffuse());
    render._shader->setVec3("spotLight.specular", render._spotLight->getSpecular());
    render._shader->setFloat("spotLight.cutOff", glm::cos(glm::radians(render._spotLight->cutOff)));
    render._shader->setFloat("spotLight.outerCutOff", glm::cos(glm::radians(render._spotLight->outerCutOff)));

    render._shader->setVec3("material.specular", 0.5f, 0.5f, 0.5f);
    render._shader->setFloat("material.shininess", 64.0f);


    glm::mat4 model;

    model = glm::translate(model,this->_position);
    model = glm::rotate(model, glm::radians(this->_angel), this->_rotation);
    model = glm::scale(model,this->_size);

    this->_model = model;

    glUniformMatrix4fv(glGetUniformLocation(render._shader->getID(),"model"),1,GL_FALSE, glm::value_ptr(this->_model));
    render._shader->setMat4("view", render._camera._view);
    render._shader->setMat4("projection", render._camera._projection);

    this->_texture.Bind();

    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}
