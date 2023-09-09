#include "OrionLoop.h"
#include "CollisionMap.h"
#include "EntityManager.h"
#include "Camera.h"
#include "Box.h"
#include "Timer.h"
#include "Utils.h"
#include "IOException.h"
#include "SecondOrderDynamics.h"

#include <iostream>

//We need to include glad before glfw
#include <glad/glad.h> 
#include <GLFW/glfw3.h>

const char *vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec2 aTexCoord;\n"
    "out vec2 TexCoord;\n"
    "uniform mat4 transform;\n"
    "void main()\n"
    "{\n"
    "    gl_Position = transform * vec4(aPos, 1.0f);\n"
    "    TexCoord = vec2(aTexCoord.x, aTexCoord.y);\n"
    "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
	"uniform vec4 ourColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = ourColor;\n"
    "}\n\0";

OrionLoop::OrionLoop(Options* options, EventHandler* eventHandler) {
	this->FPS = options->FPS;
	this->eventHandler = eventHandler;
}

void OrionLoop::initialize() {

}

void OrionLoop::execute() {
	gl::initializeGLFW();
	gl::setOpenGLVersion(3, 3);
	gl::setGLFWUseCoreProfile();

	GLFWwindow * window = gl::createWindow(800, 600, "OrionEngine 3.0 Tech Demo");

	if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        gl::terminate();
        return;
    }

	gl::updateCurrentContext(window);

	try {
        gl::initializeGLAD();
    }
    catch (IOException &ex) {
        gl::terminate();
        return;
    }

	gl::setViewport(0, 0, 800, 600);
	gl::setWindowResizeEvent(window);

	int TICKS_PER_FRAME = 1000 / FPS;
	bool hasController = false;
	Camera* c = new Camera();
	Box * b = new Box(0, 0, 500, 500, 2000, 2000, 222, 72, 31);
	Box * b2 = new Box(600, 600, 300, 400, 2000, 2000, 165, 93, 201);
	CollisionMap* collisionMap = new CollisionMap(2000, 2000, 107);

	//Instantiate EntityManager
	this->entityManager = new EntityManager(collisionMap);

	//Add entities to entity manager
	entityManager->addEntity(c);
	entityManager->addEntity(b);
	entityManager->addEntity(b2);

	int simulationTime = 0;
    Timer timer;

	bool quit = false;
	unsigned int shaderProgram = gl::getShaderProgram(vertexShaderSource, fragmentShaderSource);

	while (!gl::shouldWindowClose(window)) {
		gl::processInput(window);
		gl::setClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		gl::clearColorBuffer();

        timer.start();
        int realTime = timer.getTime();

        while (simulationTime < realTime) {
			eventHandler->handleEvents(&quit, entityManager, window);
			entityManager->handleStateChanges();
			entityManager->enactStateChanges();
			
            simulationTime += 16;
        }

        int frameTicks = timer.getTicks();
		entityManager->showAll(shaderProgram);
		gl::swapBuffers(window);
		gl::pollEvents();
	}

	gl::terminate();

	int orbX = getEntityX("ORB");
	int orbY = getEntityY("ORB");

	std::cout << "ORBB: " << orbX << ", " << orbY << std::endl;
}

int OrionLoop::getEntityX(std::string entityName) {
	return entityManager->getEntityX(entityName);
}

int OrionLoop::getEntityY(std::string entityName) {
	return entityManager->getEntityY(entityName);
}