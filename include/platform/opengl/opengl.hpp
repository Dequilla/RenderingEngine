#pragma once

#include <GL/gl.h>

namespace gl
{
    //////////////////////////////////////
    // OpenGL functions

    // Shaders
    typedef void(*FP_SHADER_SOURCE)(GLuint shader, GLsizei count, const GLchar **string, const GLint *length);
    extern FP_SHADER_SOURCE glShaderSource;

    typedef GLuint(*FP_CREATE_SHADER)(GLenum shaderType);
    extern FP_CREATE_SHADER glCreateShader;

    typedef void(*FP_DELETE_SHADER)(GLuint shader);
    extern FP_DELETE_SHADER glDeleteShader;

    typedef void(*FP_COMPILE_SHADER)(GLuint shader);
    extern FP_COMPILE_SHADER glCompileShader;

    typedef void(*FP_ATTACH_SHADER)(GLuint program, GLuint shader);
    extern FP_ATTACH_SHADER glAttachShader;

    typedef void(*FP_GET_SHADER_IV)(GLuint shader, GLenum pname, GLint *params);
    extern FP_GET_SHADER_IV glGetShaderiv;

    typedef void(*FP_GET_SHADER_INFO_LOG)(GLuint shader, GLsizei maxLength, GLsizei *length, GLchar *infoLog);
    extern FP_GET_SHADER_INFO_LOG glGetShaderInfoLog;

    typedef void(*FP_UNIFORM_MATRIX4FV)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
    extern FP_UNIFORM_MATRIX4FV glUniformMatrix4fv;

    typedef GLint(*FP_GET_UNIFORM_LOCATION)(GLuint program, const GLchar *name);
    extern FP_GET_UNIFORM_LOCATION glGetUniformLocation;

    // Programs
    typedef GLuint(*FP_CREATE_PROGRAM)();
    extern FP_CREATE_PROGRAM glCreateProgram;

    typedef void(*FP_LINK_PROGRAM)(GLuint program);
    extern FP_LINK_PROGRAM glLinkProgram;

    typedef void(*FP_GET_PROGRAM_IV)(GLuint program, GLenum pname, GLint *params);
    extern FP_GET_PROGRAM_IV glGetProgramiv;

    typedef void(*FP_GET_PROGRAM_INFO_LOG)(GLuint program, GLsizei maxLength, GLsizei *length, GLchar *infoLog);
    extern FP_GET_PROGRAM_INFO_LOG glGetProgramInfoLog;

    typedef void(*FP_DELETE_PROGRAM)(GLuint program);
    extern FP_DELETE_PROGRAM glDeleteProgram;

    typedef void(*FP_USE_PROGRAM)(GLuint program);
    extern FP_USE_PROGRAM glUseProgram;

    // Vertex Array
    typedef void(*FP_GEN_VERTEX_ARRAYS)(GLsizei n, GLuint *arrays);
    extern FP_GEN_VERTEX_ARRAYS glGenVertexArrays;

    typedef void(*FP_BIND_VERTEX_ARRAY)(GLuint array);
    extern FP_BIND_VERTEX_ARRAY glBindVertexArray;

    typedef void(*FP_VERTEX_ATTRIB_POINTER)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void * pointer);
    extern FP_VERTEX_ATTRIB_POINTER glVertexAttribPointer;

    typedef void(*FP_ENABLE_VERTEX_ATTRIB_ARRAY)(GLuint index);
    extern FP_ENABLE_VERTEX_ATTRIB_ARRAY glEnableVertexAttribArray;

    typedef void(*FP_DELETE_VERTEX_ARRAYS)(GLsizei n, const GLuint *arrays);
    extern FP_DELETE_VERTEX_ARRAYS glDeleteVertexArrays;

    // Buffers
    typedef void(*FP_GEN_BUFFERS)(GLsizei n, GLuint * buffers);
    extern FP_GEN_BUFFERS glGenBuffers;

    typedef void(*FP_BIND_BUFFER)(GLenum target, GLuint buffer); 
    extern FP_BIND_BUFFER glBindBuffer;

    typedef void(*FP_BUFFER_DATA)(GLenum target, GLsizeiptr size, const void * data, GLenum usage);
    extern FP_BUFFER_DATA glBufferData;

    typedef void(*FP_DELETE_BUFFERS)(GLsizei n, const GLuint * buffers);
    extern FP_DELETE_BUFFERS glDeleteBuffers;

    // Draw
    typedef void(*FP_DRAW_ELEMENTS)(GLenum mode, GLsizei count, GLenum type, const void * indices);
    extern FP_DRAW_ELEMENTS glDrawElements;

    typedef void(*FP_DRAW_ARRAYS)(GLenum mode, GLint first, GLsizei count);
    extern FP_DRAW_ARRAYS glDrawArrays;

    void* getProcAddress(const char* funcName);
    void initProcs();
}
