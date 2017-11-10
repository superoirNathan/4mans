#include "GameObject.h"
#include <glm/gtc/type_ptr.hpp>
#include "Texture.h"
#include "ParticleEmitter.h"

GameObject::GameObject() 
{

}
GameObject::GameObject(const Mesh &m)
{
	mesh = m;
}
GameObject::~GameObject()
{
	mesh.unload(); 
}
void GameObject::loadTexture( TextureType type, const  std::string &texFile) {

    //if (!mat, load(mat)) {
    //    system("pause");
    //    exit(0);
    //}

    mat.loadTexture(type, texFile);
}

void GameObject::draw(ShaderProgram &shader, glm::mat4 &cameraTransform,
	glm::mat4 &cameraProjection, std::vector<Light> &pointLights)
{
	shader.bind();
	shader.sendUniformMat4("uModel", glm::value_ptr(transform), false);
	shader.sendUniformMat4("uView", glm::value_ptr(cameraTransform), false);
	shader.sendUniformMat4("uProj", glm::value_ptr(cameraProjection), false);	

    //Texture
    shader.sendUniform("material.diffuse", 0);
    shader.sendUniform("material.specular", 1);
    shader.sendUniform("material.hue", mat.hue);
    shader.sendUniform("material.specularExponent", mat.specularExponent);

    //	shader.sendUniform("lightPos", cameraTransform * glm::vec4(0.f, 10.f, 0.f, 1.f));
    //glm::vec4 camPos = cameraTransform * glm::vec4(0.f, 0.f, 0.f, 1.f);

    for (int i = 0; i < pointLights.size(); i++) {

        std::string prefix = "pointLights[" + std::to_string(i) + "].";

        if(i == 0)
            shader.sendUniform(prefix + "position",  glm::vec4(0.f, 10.f, 0.f, 1.f));
        else
            shader.sendUniform(prefix + "position", cameraTransform * pointLights[i].position);

        shader.sendUniform(prefix + "ambient",                    pointLights[i].ambient);
        shader.sendUniform(prefix + "diffuse",                    pointLights[i].diffuse);
        shader.sendUniform(prefix + "specular",                   pointLights[i].specular);
        shader.sendUniform(prefix + "specularExponent",           pointLights[i].specularExponent);
        shader.sendUniform(prefix + "consantAttenuation",         pointLights[i].consantAttenuation);
        shader.sendUniform(prefix + "linearAttenuation",          pointLights[i].linearAttenuation);
        shader.sendUniform(prefix + "quadraticAttenuation",       pointLights[i].quadraticAttenuation);
    }


    glActiveTexture(GL_TEXTURE0);
    mat.diffuse.bind();
    glActiveTexture(GL_TEXTURE1);
    mat.specular.bind();

	glBindVertexArray(mesh.vao);
	glDrawArrays(GL_TRIANGLES, 0, mesh.getNumVertices());
	glBindVertexArray(GL_NONE);


    mat.specular.unbind();
    glActiveTexture(GL_TEXTURE0);
    mat.diffuse.unbind();

	shader.unbind();
}

void GameObject::update2(float dt) {

    // Update physics

    // Update acceleration

    acceleration =  force  / 10.f ;
    velocity = velocity + (acceleration * dt);
    position = position +  velocity * dt;

    // We've applied the force, let's remove it so it does not get applied next frame
    force = glm::vec3(0.0f);
    velocity = velocity - (velocity / 2.0f * dt);


}
