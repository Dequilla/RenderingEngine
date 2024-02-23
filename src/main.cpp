#include "rg.hpp"

#include "graphics/model_formats/wavefront_obj.hpp"

#include <iostream>
#include <cassert>
#include <memory>

const size_t WIDTH = 1280;
const size_t HEIGHT = 720;

const float mouse_sens = 0.04;
const double movement_speed = 2.2f;

int main()
{
    rg::Window window("A short title!", WIDTH, HEIGHT);
    window.setCursorGrabbed(true);
    window.setCursorVisible(false);
    window.setCursorFixed(true);

    gl::initProcs();

    rg::WavefrontOBJ_ModelLoader objLoader;
    //std::optional<rg::Model> objmodel = objLoader.load("./models/Square/square_tri_normals.obj");
    std::optional<rg::Model> objmodel = objLoader.load("./models/Duck/12248_Bird_v1_L2.obj");
    //std::optional<rg::Model> objmodel = objLoader.load("./models/Church/church_tri_normals.obj");
    if(objmodel.has_value())
        std::cout << "Loaded model." << std::endl;
    else
    {
        std::cout << "Could not load model." << std::endl;
        return -1;
    }

    rg::Camera camera;

    std::unique_ptr<rg::Renderer3D> renderer = rg::Renderer3D::create();
    renderer->init();
    renderer->setClearColor( {0.2f, 0.3f, 0.3f, 1.0f} );

    std::unique_ptr<rg::ShaderProgram> sprogram = rg::ShaderProgram::create();
    {
        std::unique_ptr<rg::Shader> vxShader = rg::Shader::create();
        std::unique_ptr<rg::Shader> fgShader = rg::Shader::create();
        if(vxShader->load(rg::Shader::Type::VERTEX, "./shaders/vertex_3d.glsl"))
            std::cout << "Loaded vertex shader." << std::endl;
        if(fgShader->load(rg::Shader::Type::FRAGMENT, "./shaders/fragment_3d.glsl"))
            std::cout << "Loaded fragment shader." << std::endl;

        sprogram->attach(*vxShader);
        sprogram->attach(*fgShader);
        if(sprogram->finish())
            std::cout << "Success linking shaders." << std::endl;
        else
            std::cout << "Error linking shaders." << std::endl;

        vxShader->unload();
        fgShader->unload();
    }


    sprogram->use();
    
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
    
    // Pass transformation matrices to the shader
    sprogram->setMat4("projection", projection);     

    // Model translations and rotations
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::degrees(90.f), glm::vec3(1.f, 0.f, 0.f));
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
    sprogram->setMat4("model", model); 
    
    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE ); // Wireframe mode
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL ); // Normal mode

    uint32_t accumilator = 0;
    rg::Clock clock;
    rg::ClockState clockState;
    double deltaTime = 0.0f;

    // 0: forward
    // 1: backward
    // 2: left
    // 3: right
    bool movement[4] = { false };

    while(window.isOpen())
    {
        rg::Event event;
        while(window.pollEvent(event))
        {
            switch(event.type)
            {
                case rg::EventType::Close:
                    std::cout << "Closing window..." << std::endl;
                    break;

                case rg::EventType::Motion:
                    camera.update_rotation(event.motion.deltax, -event.motion.deltay, mouse_sens);
                    break;

                case rg::EventType::FocusGain:
                    //std::cout << "Gained focus!" << std::endl;
                    break;
                case rg::EventType::FocusLost:
                    //std::cout << "Lost focus!" << std::endl;
                    break;

                case rg::EventType::KeyPressed:
                    if(event.key.code == rg::KeyCode::w)
                        movement[0] = true;
                    if(event.key.code == rg::KeyCode::s)
                        movement[1] = true;
                    if(event.key.code == rg::KeyCode::a)
                        movement[2] = true;
                    if(event.key.code == rg::KeyCode::d)
                        movement[3] = true;
                    break;

                case rg::EventType::KeyReleased:
                    if(event.key.code == rg::KeyCode::w)
                        movement[0] = false;
                    if(event.key.code == rg::KeyCode::s)
                        movement[1] = false;
                    if(event.key.code == rg::KeyCode::a)
                        movement[2] = false;
                    if(event.key.code == rg::KeyCode::d)
                        movement[3] = false;
                    break;
            }
        }

        if(movement[0])
        {
            camera.move_forward(movement_speed * deltaTime);   
        }
        
        if(movement[1])
        {
            camera.move_forward(-movement_speed * deltaTime);
        }

        if(movement[2])
        {
            camera.move_sideways(-movement_speed * deltaTime);
        }

        if(movement[3])
        {
            camera.move_sideways(movement_speed * deltaTime);
        }

        window.initFrame();

        renderer->clear();

        sprogram->use();
        sprogram->setMat4("view", camera.getViewMatrix());
        //renderer->draw(*mesh);
        renderer->draw(objmodel.value());

        window.presentFrame();

        clockState = clock.restart();
        deltaTime = clockState.elapsed().delta_seconds().count();
        accumilator += 1;
        if(accumilator >= 100)
        {
            accumilator = 0;
            std::cout << "Frame time: " << clockState.elapsed().milliseconds() << std::endl;
        }
    }
    
    sprogram->unload();

    return 0;
}
