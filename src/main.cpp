#include "platform/opengl/opengl.hpp"

#include "window.hpp"
#include "model.hpp"
#include "renderer.hpp"
#include "shader.hpp"

#include <iostream>
#include <cassert>
#include <memory>

int main()
{
    rg::Window window("A short title!", 1280, 720);
    std::unique_ptr<rg::Renderer3D> renderer = rg::Renderer3D::create();

    gl::initProcs();

    renderer->init();
    renderer->setClearColor( {0.2f, 0.3f, 0.3f, 1.0f} );

    std::unique_ptr<rg::ShaderProgram> sprogram = rg::ShaderProgram::create();
    {
        std::unique_ptr<rg::Shader> vxShader = rg::Shader::create();
        std::unique_ptr<rg::Shader> fgShader = rg::Shader::create();
        if(vxShader->load(rg::Shader::Type::VERTEX, "./shaders/vertex.glsl"))
            std::cout << "Loaded vertex shader." << std::endl;
        if(fgShader->load(rg::Shader::Type::FRAGMENT, "./shaders/fragment.glsl"))
            std::cout << "Loaded fragment shader." << std::endl;

        sprogram->attach(*vxShader);
        sprogram->attach(*fgShader);
        if(sprogram->finish())
            std::cout << "Success linking shaders." << std::endl;

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

    while(window.isOpen())
    {
        rg::Event event;
        while(window.pollEvent(event))
        {
        }

        window.initFrame();

        renderer->clear();

        sprogram->use();

        renderer->draw(*mesh);

        window.presentFrame();
    }
    
    sprogram->unload();

    return 0;
}

    /*

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

                // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
*/


