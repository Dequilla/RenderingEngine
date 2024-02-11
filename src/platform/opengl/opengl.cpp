#include "platform/opengl/opengl.hpp"

#include <GL/glx.h>

#include <cassert>

namespace gl
{
    ///////////////////////////
    // OpenGL function ptrs
    FP_SHADER_SOURCE shaderSource;  
    FP_CREATE_SHADER createShader;
    FP_DELETE_SHADER deleteShader;
    FP_COMPILE_SHADER compileShader;
    FP_ATTACH_SHADER attachShader;
    FP_GET_SHADER_IV getShaderiv;
    FP_GET_SHADER_INFO_LOG getShaderInfoLog;
    
    FP_CREATE_PROGRAM createProgram;
    FP_LINK_PROGRAM linkProgram;
    FP_GET_PROGRAM_IV getProgramiv;
    FP_GET_PROGRAM_INFO_LOG getProgramInfoLog;
    FP_DELETE_PROGRAM deleteProgram;
    FP_USE_PROGRAM useProgram;

    FP_UNIFORM_MATRIX4FV uniformMatrix4fv;
    FP_GET_UNIFORM_LOCATION getUniformLocation;

    FP_GEN_VERTEX_ARRAYS genVertexArrays;
    FP_BIND_VERTEX_ARRAY bindVertexArray;
    FP_VERTEX_ATTRIB_POINTER vertexAttribPointer;
    FP_ENABLE_VERTEX_ATTRIB_ARRAY enableVertexAttribArray;
    FP_DELETE_VERTEX_ARRAYS deleteVertexArrays;

    FP_GEN_BUFFERS genBuffers;
    FP_BIND_BUFFER bindBuffer;
    FP_BUFFER_DATA bufferData;
    FP_DELETE_BUFFERS deleteBuffers;

    FP_DRAW_ELEMENTS drawElements;
    FP_DRAW_ARRAYS drawArrays;

    void* getProcAddress(const char* funcName)
    {
        void* fptr = reinterpret_cast<void*>( glXGetProcAddress( 
          reinterpret_cast<const GLubyte*>(funcName)
        ) );
        assert(fptr != nullptr && "Unsupported GL func.");
        return fptr;  
    }

    void initProcs()
    {
        shaderSource = (FP_SHADER_SOURCE)getProcAddress("glShaderSource");  
        createShader = (FP_CREATE_SHADER)getProcAddress("glCreateShader");
        deleteShader = (FP_DELETE_SHADER)getProcAddress("glDeleteShader");
        compileShader = (FP_COMPILE_SHADER)getProcAddress("glCompileShader");
        attachShader = (FP_ATTACH_SHADER)getProcAddress("glAttachShader");
        getShaderiv = (FP_GET_SHADER_IV)getProcAddress("glGetShaderiv");
        getShaderInfoLog = (FP_GET_SHADER_INFO_LOG)getProcAddress("glGetShaderInfoLog");

        createProgram = (FP_CREATE_PROGRAM)getProcAddress("glCreateProgram");
        linkProgram = (FP_LINK_PROGRAM)getProcAddress("glLinkProgram");
        getProgramiv = (FP_GET_PROGRAM_IV)getProcAddress("glGetProgramiv");
        getProgramInfoLog = (FP_GET_PROGRAM_INFO_LOG)getProcAddress("glGetProgramInfoLog");
        deleteProgram = (FP_DELETE_PROGRAM)getProcAddress("glDeleteProgram");
        useProgram = (FP_USE_PROGRAM)getProcAddress("glUseProgram");

        uniformMatrix4fv = (FP_UNIFORM_MATRIX4FV)getProcAddress("glUniformMatrix4fv");
        getUniformLocation = (FP_GET_UNIFORM_LOCATION)getProcAddress("glGetUniformLocation");

        genVertexArrays = (FP_GEN_VERTEX_ARRAYS)getProcAddress("glGenVertexArrays");
        bindVertexArray = (FP_BIND_VERTEX_ARRAY)getProcAddress("glBindVertexArray");
        vertexAttribPointer = (FP_VERTEX_ATTRIB_POINTER)getProcAddress("glVertexAttribPointer");
        enableVertexAttribArray = (FP_ENABLE_VERTEX_ATTRIB_ARRAY)getProcAddress("glEnableVertexAttribArray");
        deleteVertexArrays = (FP_DELETE_VERTEX_ARRAYS)getProcAddress("glDeleteVertexArrays");

        genBuffers = (FP_GEN_BUFFERS)getProcAddress("glGenBuffers");
        bindBuffer = (FP_BIND_BUFFER)getProcAddress("glBindBuffer");
        bufferData = (FP_BUFFER_DATA)getProcAddress("glBufferData");
        deleteBuffers = (FP_DELETE_BUFFERS)getProcAddress("glDeleteBuffers");

        drawElements = (FP_DRAW_ELEMENTS)getProcAddress("glDrawElements");
        drawArrays = (FP_DRAW_ARRAYS)getProcAddress("glDrawArrays");
    }

}
