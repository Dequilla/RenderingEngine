#include "platform/opengl/opengl.hpp"

#include <GL/glx.h>

#include <cassert>

namespace gl
{
    ///////////////////////////
    // OpenGL function ptrs
    FP_SHADER_SOURCE glShaderSource;  
    FP_CREATE_SHADER glCreateShader;
    FP_DELETE_SHADER glDeleteShader;
    FP_COMPILE_SHADER glCompileShader;
    FP_ATTACH_SHADER glAttachShader;
    FP_GET_SHADER_IV glGetShaderiv;
    FP_GET_SHADER_INFO_LOG glGetShaderInfoLog;
    
    FP_CREATE_PROGRAM glCreateProgram;
    FP_LINK_PROGRAM glLinkProgram;
    FP_GET_PROGRAM_IV glGetProgramiv;
    FP_GET_PROGRAM_INFO_LOG glGetProgramInfoLog;
    FP_DELETE_PROGRAM glDeleteProgram;
    FP_USE_PROGRAM glUseProgram;

    FP_UNIFORM_MATRIX4FV glUniformMatrix4fv;
    FP_GET_UNIFORM_LOCATION glGetUniformLocation;

    FP_GEN_VERTEX_ARRAYS glGenVertexArrays;
    FP_BIND_VERTEX_ARRAY glBindVertexArray;
    FP_VERTEX_ATTRIB_POINTER glVertexAttribPointer;
    FP_ENABLE_VERTEX_ATTRIB_ARRAY glEnableVertexAttribArray;
    FP_DELETE_VERTEX_ARRAYS glDeleteVertexArrays;

    FP_GEN_BUFFERS glGenBuffers;
    FP_BIND_BUFFER glBindBuffer;
    FP_BUFFER_DATA glBufferData;
    FP_DELETE_BUFFERS glDeleteBuffers;

    FP_DRAW_ELEMENTS glDrawElements;
    FP_DRAW_ARRAYS glDrawArrays;

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
        glShaderSource = (FP_SHADER_SOURCE)getProcAddress("glShaderSource");  
        glCreateShader = (FP_CREATE_SHADER)getProcAddress("glCreateShader");
        glDeleteShader = (FP_DELETE_SHADER)getProcAddress("glDeleteShader");
        glCompileShader = (FP_COMPILE_SHADER)getProcAddress("glCompileShader");
        glAttachShader = (FP_ATTACH_SHADER)getProcAddress("glAttachShader");
        glGetShaderiv = (FP_GET_SHADER_IV)getProcAddress("glGetShaderiv");
        glGetShaderInfoLog = (FP_GET_SHADER_INFO_LOG)getProcAddress("glGetShaderInfoLog");

        glCreateProgram = (FP_CREATE_PROGRAM)getProcAddress("glCreateProgram");
        glLinkProgram = (FP_LINK_PROGRAM)getProcAddress("glLinkProgram");
        glGetProgramiv = (FP_GET_PROGRAM_IV)getProcAddress("glGetProgramiv");
        glGetProgramInfoLog = (FP_GET_PROGRAM_INFO_LOG)getProcAddress("glGetProgramInfoLog");
        glDeleteProgram = (FP_DELETE_PROGRAM)getProcAddress("glDeleteProgram");
        glUseProgram = (FP_USE_PROGRAM)getProcAddress("glUseProgram");

        glUniformMatrix4fv = (FP_UNIFORM_MATRIX4FV)getProcAddress("glUniformMatrix4fv");
        glGetUniformLocation = (FP_GET_UNIFORM_LOCATION)getProcAddress("glGetUniformLocation");

        glGenVertexArrays = (FP_GEN_VERTEX_ARRAYS)getProcAddress("glGenVertexArrays");
        glBindVertexArray = (FP_BIND_VERTEX_ARRAY)getProcAddress("glBindVertexArray");
        glVertexAttribPointer = (FP_VERTEX_ATTRIB_POINTER)getProcAddress("glVertexAttribPointer");
        glEnableVertexAttribArray = (FP_ENABLE_VERTEX_ATTRIB_ARRAY)getProcAddress("glEnableVertexAttribArray");
        glDeleteVertexArrays = (FP_DELETE_VERTEX_ARRAYS)getProcAddress("glDeleteVertexArrays");

        glGenBuffers = (FP_GEN_BUFFERS)getProcAddress("glGenBuffers");
        glBindBuffer = (FP_BIND_BUFFER)getProcAddress("glBindBuffer");
        glBufferData = (FP_BUFFER_DATA)getProcAddress("glBufferData");
        glDeleteBuffers = (FP_DELETE_BUFFERS)getProcAddress("glDeleteBuffers");

        glDrawElements = (FP_DRAW_ELEMENTS)getProcAddress("glDrawElements");
        glDrawArrays = (FP_DRAW_ARRAYS)getProcAddress("glDrawArrays");
    }

}
