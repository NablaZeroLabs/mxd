// -*- coding:utf-8; mode:c++; mode:auto-fill; fill-column:80; -*-

/// @file      shader.cpp
/// @brief     Graphics shader.
/// @author    J. Arrieta <juan.arrieta@nablazerolabs.com>
/// @date      November 12, 2018
/// @copyright (c) 2018 Nabla Zero Labs

// Related mxd header
#include "shader.hpp"  // ALWAYS the first include

// C++ Standard Library
#include <string>  // All C++ Standard Library includes needed to implement the class.

// mxd Library
// Any mxd headers go here.

// Third party libraries
// Any third-party libraries go here.
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace nzl {

Shader::Shader(Shader::Stage stage, std::string source)
    : m_stage{stage}, m_source(std::move(source)) {

    switch(stage){
        case Shader::Stage::Compute:
            Shader::m_shaderID = glCreateShader(GL_COMPUTE_SHADER);
            break;
        case Shader::Stage::Fragment:
            Shader::m_shaderID = glCreateShader(GL_FRAGMENT_SHADER);
            break;
        case Shader::Stage::Geometry:
            Shader::m_shaderID = glCreateShader(GL_GEOMETRY_SHADER);
            break;
        case Shader::Stage::TessellationControl:
            Shader::m_shaderID = glCreateShader(GL_TESS_CONTROL_SHADER);
            break;
        case Shader::Stage::TessellationEvaluation:
            Shader::m_shaderID = glCreateShader(GL_TESS_EVALUATION_SHADER);
            break;
        case Shader::Stage::Vertex:
            Shader::m_shaderID = glCreateShader(GL_VERTEX_SHADER);
            break;
    }

    const char* cStringSource = source.c_str();
    glShaderSource(Shader::m_shaderID, 1, &cStringSource, NULL);
    glCompileShader(Shader::m_shaderID);
    Shader::checkCompileErrors();
}

Shader::Stage Shader::stage() const noexcept { return m_stage; }

const std::string& Shader::source() const noexcept { return m_source; }

void Shader::checkCompileErrors(){
    int success;
    char infoLog[1024];
    glGetShaderiv(Shader::m_shaderID, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(Shader::m_shaderID, 1024, NULL, infoLog);
        std::string error = infoLog;
        error = "ERROR::SHADER_COMPILATION_ERROR:\n" + error +"\n----------------------------------------";
        throw error;
    }
}

Shader::~Shader(){
    glDeleteShader(m_shaderID);
}

}  // namespace nzl
