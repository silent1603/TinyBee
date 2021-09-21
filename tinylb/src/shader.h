#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

std::string get_file_contents(const char* filename);

class Shader {
    public : 
    GLuint ID;
    Shader(const char* vertexFile, const char* Fragment);     
    void Active();
    void Delete();
    private:
    void complieError(unsigned int shader,const char* type); 
    char infoLog[512];
};


#endif