#pragma once

#include "OrionEntity.h"
#include "SecondOrderDynamics.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Box : public OrionEntity {
private:
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
    float r;
    float g;
    float b;

    const double VELOCITY = 9.2;

    double realX;
    double realY;
    double settleX;
    double settleY;

    double futureRealX;
    double futureRealY;
    double futureSettleX;
    double futureSettleY;

    SecondOrderDynamics * xDynamic;
    SecondOrderDynamics * yDynamic;

    unsigned int virtualWidth;
    unsigned int virtualHeight;

    bool doHaveUniformLocations = false;

    int transformLoc = -1;
    int vertexColorLoc = -1;

    glm::mat4 transform;

    void handleJoystickInput(std::set<JoystickInput *> * joystickInputs);
    void handleArrowKeyInput(std::set<InputType>* currentInputs);
    void setDynamicForMovementWhileInput();

    int getUniformLocation(int shaderProgram, std::string uniform);
    void useProgram(int program);
    void uniformMatrix4fv(int transformLoc);
    void uniform4f(int vertexColorLocation);
    void bindVertexArray();
    void drawElements();

public:
    Box(double x, double y, unsigned int width, unsigned int height, unsigned int virtualWidth, unsigned int virtualHeight, int r, int g, int b);

	void handleStateChanges(std::set<InputType>* currentInputs, std::set<JoystickInput *> * joystickInputs, CollisionMap * collisionMap);
	void enactStateChanges();
	void show(int shaderProgram);
};