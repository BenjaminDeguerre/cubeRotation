#ifndef SCENE_H
#define SCENE_H

#include "glm/glm.hpp"

class Scene
{
public:
    /**
      Load textures, initialize shaders, etc.
      */
    virtual void initScene() = 0;

    /**
      This is called prior to every frame.  Use this
      to update your animation.
      */
    virtual void update( float t ) = 0;

    /**
      Draw your scene.
      */
    virtual void render() = 0;

    /**
      Called when screen is resized
      */
    virtual void resize(int, int) = 0;

    virtual void setAngleAxis(float angle, glm::vec3 axis) = 0;

    virtual void setView(glm::mat4 view) = 0;

    virtual void rotate(glm::mat4 rotationMatrix) = 0;

    virtual void drawLine(float x1, float y1, float z1, float x2, float y2, float z2) = 0;
};

#endif // SCENE_H
