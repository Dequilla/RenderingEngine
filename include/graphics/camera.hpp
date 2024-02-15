#pragma once

#include <iostream>

#include "glm/glm.hpp"

namespace rg
{

    class Camera
    {
        glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f);
        glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

        float yaw   = -90.0f;        
        float pitch =  0.0f;

    public:
        inline void update_rotation(float deltax, float deltay, float sensativity = 0.1f)
        {
            yaw += deltax * sensativity;
            pitch += deltay * sensativity;

            if (pitch > 89.0f)
                pitch = 89.0f;
            if (pitch < -89.0f)
                pitch = -89.0f;

            glm::vec3 tfront;
            tfront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
            tfront.y = sin(glm::radians(pitch));
            tfront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
            front = glm::normalize(tfront);
        }

        inline void move_forward(float speed)
        {
            position += speed * front;
        }

        inline void move_sideways(float speed)
        {
            position += glm::normalize(glm::cross(front, up)) * speed;
        }

        inline glm::mat4 getViewMatrix() const
        {
            return glm::lookAt(position, position + front, up);
        }

    };

}

