#pragma once

#include <GL/gl.h>

namespace gl
{
    //////////////////////////////////////
    // OpenGL functions

    // Shaders
    typedef void(*FP_SHADER_SOURCE)(GLuint shader, GLsizei count, const GLchar **string, const GLint *length);
    extern FP_SHADER_SOURCE shaderSource;

    typedef GLuint(*FP_CREATE_SHADER)(GLenum shaderType);
    extern FP_CREATE_SHADER createShader;

    typedef void(*FP_DELETE_SHADER)(GLuint shader);
    extern FP_DELETE_SHADER deleteShader;

    typedef void(*FP_COMPILE_SHADER)(GLuint shader);
    extern FP_COMPILE_SHADER compileShader;

    typedef void(*FP_ATTACH_SHADER)(GLuint program, GLuint shader);
    extern FP_ATTACH_SHADER attachShader;

    typedef void(*FP_GET_SHADER_IV)(GLuint shader, GLenum pname, GLint *params);
    extern FP_GET_SHADER_IV getShaderiv;

    typedef void(*FP_GET_SHADER_INFO_LOG)(GLuint shader, GLsizei maxLength, GLsizei *length, GLchar *infoLog);
    extern FP_GET_SHADER_INFO_LOG getShaderInfoLog;

    typedef void(*FP_UNIFORM_MATRIX4FV)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
    extern FP_UNIFORM_MATRIX4FV uniformMatrix4fv;

    typedef GLint(*FP_GET_UNIFORM_LOCATION)(GLuint program, const GLchar *name);
    extern FP_GET_UNIFORM_LOCATION getUniformLocation;

    // Programs
    typedef GLuint(*FP_CREATE_PROGRAM)();
    extern FP_CREATE_PROGRAM createProgram;

    typedef void(*FP_LINK_PROGRAM)(GLuint program);
    extern FP_LINK_PROGRAM linkProgram;

    typedef void(*FP_GET_PROGRAM_IV)(GLuint program, GLenum pname, GLint *params);
    extern FP_GET_PROGRAM_IV getProgramiv;

    typedef void(*FP_GET_PROGRAM_INFO_LOG)(GLuint program, GLsizei maxLength, GLsizei *length, GLchar *infoLog);
    extern FP_GET_PROGRAM_INFO_LOG getProgramInfoLog;

    typedef void(*FP_DELETE_PROGRAM)(GLuint program);
    extern FP_DELETE_PROGRAM deleteProgram;

    typedef void(*FP_USE_PROGRAM)(GLuint program);
    extern FP_USE_PROGRAM useProgram;

    // Vertex Array
    typedef void(*FP_GEN_VERTEX_ARRAYS)(GLsizei n, GLuint *arrays);
    extern FP_GEN_VERTEX_ARRAYS genVertexArrays;

    typedef void(*FP_BIND_VERTEX_ARRAY)(GLuint array);
    extern FP_BIND_VERTEX_ARRAY bindVertexArray;

    typedef void(*FP_VERTEX_ATTRIB_POINTER)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void * pointer);
    extern FP_VERTEX_ATTRIB_POINTER vertexAttribPointer;

    typedef void(*FP_ENABLE_VERTEX_ATTRIB_ARRAY)(GLuint index);
    extern FP_ENABLE_VERTEX_ATTRIB_ARRAY enableVertexAttribArray;

    typedef void(*FP_DELETE_VERTEX_ARRAYS)(GLsizei n, const GLuint *arrays);
    extern FP_DELETE_VERTEX_ARRAYS deleteVertexArrays;

    // Buffers
    typedef void(*FP_GEN_BUFFERS)(GLsizei n, GLuint * buffers);
    extern FP_GEN_BUFFERS genBuffers;

    typedef void(*FP_BIND_BUFFER)(GLenum target, GLuint buffer); 
    extern FP_BIND_BUFFER bindBuffer;

    typedef void(*FP_BUFFER_DATA)(GLenum target, GLsizeiptr size, const void * data, GLenum usage);
    extern FP_BUFFER_DATA bufferData;

    typedef void(*FP_DELETE_BUFFERS)(GLsizei n, const GLuint * buffers);
    extern FP_DELETE_BUFFERS deleteBuffers;

    // Draw
    typedef void(*FP_DRAW_ELEMENTS)(GLenum mode, GLsizei count, GLenum type, const void * indices);
    extern FP_DRAW_ELEMENTS drawElements;

    typedef void(*FP_DRAW_ARRAYS)(GLenum mode, GLint first, GLsizei count);
    extern FP_DRAW_ARRAYS drawArrays;

    void* getProcAddress(const char* funcName);
    void initProcs();
}
