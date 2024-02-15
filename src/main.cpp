#include "rg.hpp"

#include <iostream>
#include <cassert>
#include <memory>

const size_t WIDTH = 1280;
const size_t HEIGHT = 720;

int main()
{
    rg::Window window("A short title!", WIDTH, HEIGHT);
    window.setCursorGrabbed(true);
    window.setCursorVisible(false);
    window.setCursorFixed(true);

    gl::initProcs();

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

    rg::VertexBuffer vertices = {
        {0.5f,  0.5f, 0.0f},  // top right
        {0.5f, -0.5f, 0.0f},  // bottom right
        {-0.5f, -0.5f, 0.0f},  // bottom left
        {-0.5f,  0.5f, 0.0f}   // top left 
    };
    rg::IndexBuffer indices = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };
    
    std::unique_ptr<rg::Mesh> mesh = rg::Mesh::create(vertices, indices);

    sprogram->use();
    
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
    
    // Pass transformation matrices to the shader
    sprogram->setMat4("projection", projection);     

    // Model translations and rotations
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    sprogram->setMat4("model", model); 

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
                    camera.update_rotation(event.motion.deltax, -event.motion.deltay, 0.01);
                    break;

                case rg::EventType::FocusGain:
                    //std::cout << "Gained focus!" << std::endl;
                    break;
                case rg::EventType::FocusLost:
                    //std::cout << "Lost focus!" << std::endl;
                    break;

                case rg::EventType::KeyPressed:
                    if(event.key.code == rg::KeyCode::w)
                        camera.move_forward(1.f);   
                    else if(event.key.code == rg::KeyCode::s)
                        camera.move_forward(-1.f);

                    else if(event.key.code == rg::KeyCode::a)
                        camera.move_sideways(-1.f);
                    else if(event.key.code == rg::KeyCode::d)
                        camera.move_sideways(1.f);

                    break;

                case rg::EventType::KeyReleased:
                    break;
            }
        }

        window.initFrame();

        renderer->clear();

        sprogram->use();
        sprogram->setMat4("view", camera.getViewMatrix());
        renderer->draw(*mesh);

        window.presentFrame();
    }
    
    sprogram->unload();

    return 0;
}
