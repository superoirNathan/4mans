//Nathan Alphonse 100523109
//100555192 Janarthan Ravikumar
//Bill Ko 100590491

#include <iostream> // for std::cout
#include <glm\gtc\random.hpp> // for glm::linearRand

#include "AnimationMath.h"
#include "ParticleEmitter.h"

ParticleEmitter::ParticleEmitter()
	: m_pParticles(nullptr),
	m_pNumParticles(0),
	playing(true),
	interpolateColour(false)
{

}

ParticleEmitter::~ParticleEmitter()
{
	freeMemory();
}

void ParticleEmitter::initialize(unsigned int numParticles)
{
	freeMemory(); // destroy any existing particles

	if (numParticles > 0)
	{
		m_pParticles = new Particle[numParticles];
		memset(m_pParticles, 0, sizeof(Particle) * numParticles);
		m_pNumParticles = numParticles;
	}
        emitterName = "emitter";

}

void ParticleEmitter::freeMemory()
{
	if (m_pParticles) // if not a null pointer
	{
		delete[] m_pParticles;
		m_pParticles = nullptr;
		m_pNumParticles = 0;
	}
}

void ParticleEmitter::update(float dt)
{
    if (pathOn) {
        // All keyframe and tvalue management replaced with a single line of code!
        keyframeController.calculateLookupTable(step);
        interpolatedPosition = keyframeController.update(dt);

        keyframeController.setKey(0, catmullT0);
        keyframeController.setKey(1, emitterPosition);
        keyframeController.setKey(2, pathEnd);
        keyframeController.setKey(3, catmullT1);

//        pointHandles[0].position = emitterPosition;
//        pointHandles[1].position = pathEnd;
    }


    TotalT += dt;

	if (m_pParticles && playing) // make sure memory is initialized and system is playing
	{
		// loop through each particle
		Particle* particle = m_pParticles;
		for (unsigned int i = 0; i < m_pNumParticles; ++i, ++particle)
		{
            if (durationOn) {
                float randomTvalRate = glm::linearRand(0, 1);
                float tempRate = Math::lerp(spawnRange.x, spawnRange.y, randomTvalRate);


                if (particle->life <= 0 && (TotalT >= (1 / tempRate))) // if particle has no life remaining
                {
                    glm::vec3 tempEmitter = glm::vec3(0.f);

                    if (boxOn == true) {
                        randomTvalRate = glm::linearRand(0.f, 1.f);
                        tempEmitter.x = Math::lerp(0.f - boxWH.x, boxWH.x, randomTvalRate);
                        randomTvalRate = glm::linearRand(0.f, 1.f);
                        tempEmitter.y = Math::lerp(0.f - boxWH.y, boxWH.y, randomTvalRate);
                        randomTvalRate = glm::linearRand(0.f, 1.f);
                        tempEmitter.z = Math::lerp(0.f - boxWH.z, boxWH.z, randomTvalRate);

                        //              std::cout << randomTvalRate <<":: "<< tempEmitter.x << " , " << tempEmitter.y << std::endl;
                    }

                    TotalT = 0;
                    // Respawn particle
                    // Note: we are not freeing memory, we are "Recycling" the particles
                    float randomTval = glm::linearRand(0.0f, 1.0f);
                    if (gravityOn) {
                        particle->acceleration = glm::vec3(-9.8) * gravity;
                    }
                    else {
                        particle->acceleration = glm::vec3(0.0f);
                    }

                    particle->colour = Math::lerp(colour0, colour1, randomTval);
                    particle->life = Math::lerp(lifeRange.x, lifeRange.y, randomTval);
                    particle->mass = Math::lerp(massRange.x, massRange.y, randomTval);
                    particle->position = emitterPosition + tempEmitter;
                    particle->size = Math::lerp(sizeRange.x, sizeRange.y, randomTval);
                    particle->velocity = Math::lerp(velocity0, velocity1, randomTval);

                }
            }// if duration end

                // Update physics

                // Update acceleration
                particle->acceleration = particle->force / particle->mass;
                particle->velocity = particle->velocity + (particle->acceleration * dt);
                particle->position = particle->position + particle->velocity * dt;

                // We've applied the force, let's remove it so it does not get applied next frame
                particle->force = glm::vec3(0.0f);

                // Decrease particle life
                particle->life -= dt;

                // Update visual properties
                if (interpolateColour)
                {
                    // calculate t value
                    float tVal = Math::invLerp(particle->life, lifeRange.x, lifeRange.y);
                    particle->colour = Math::lerp(colour0, colour1, tVal);
                }
		}// forloop end
	}// if playing end
}

void ParticleEmitter::draw()
{
	// Draw the emitter position
	// Note: not necessary
//    if (showEmitter) {
//    }
//	Particle* p = m_pParticles;
//	for (int i = 0; i < m_pNumParticles; ++i, ++p)
//	{
//		if (p->life >= 0.0f) // if particle is alive, draw it
//		{
//
//		}
//	}


}

void ParticleEmitter::applyForceToParticle(unsigned int idx, glm::vec3 force)
{
	if (idx >= m_pNumParticles)
	{
		std::cout << "ParticleEmitter::applyForceToParticle ERROR: idx " << idx << "out of range!" << std::endl;
		return;
	}

	m_pParticles[idx].force = force;
}

glm::vec3 ParticleEmitter::getParticlePosition(unsigned int idx)
{
	if (idx >= m_pNumParticles)
	{
		std::cout << "ParticleEmitter::getParticlePosition ERROR: idx " << idx << "out of range!" << std::endl;
		return glm::vec3();
	}

	return m_pParticles[idx].position;
}

glm::vec3 ParticleEmitter::getParticleVelocity(unsigned int idx)
{
    if (idx >= m_pNumParticles)
    {
        std::cout << "ParticleEmitter::getParticlePosition ERROR: idx " << idx << "out of range!" << std::endl;
        return glm::vec3();
    }

    return m_pParticles[idx].position;
}
void ParticleEmitter::setParticleVelocity(unsigned int idx, glm::vec3 newVeloctiy)
{
    if (idx >= m_pNumParticles)
    {
        std::cout << "ParticleEmitter::getParticlePosition ERROR: idx " << idx << "out of range!" << std::endl;
    }

    m_pParticles[idx].velocity = newVeloctiy;
}
void ParticleEmitter::setParticleAcceleration(unsigned int idx, glm::vec3 addedAcceleration)
{
    if (idx >= m_pNumParticles)
    {
        std::cout << "ParticleEmitter::getParticlePosition ERROR: idx " << idx << "out of range!" << std::endl;
    }

    m_pParticles[idx].acceleration = addedAcceleration;

}
float ParticleEmitter::getParticleLife(unsigned int idx)
{
    if (idx >= m_pNumParticles)
    {
        std::cout << "ParticleEmitter::getParticlePosition ERROR: idx " << idx << "out of range!" << std::endl;
        return float();
    }
    return m_pParticles[idx].life;
}


