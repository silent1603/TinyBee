#include "shader.h"

std::string get_file_contents(const char* fileName)
{
    std::ifstream in(fileName,std::ios::binary);
    if(in)
    {
        std::string contents;
        in.seekg(0,std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0,std::ios::beg);
        in.read(&contents[0],contents.size());
        in.close();
        return(contents);
    }
    std::cout << "can't read file " << '\n';
    throw(errno);
}

Shader::Shader(const char* vertexFile,const char* fragmentFile)
{
    std::string vertexCode = get_file_contents(vertexFile);
    std::string fragmentCode = get_file_contents(fragmentFile);

    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();


  
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader,1,&vertexSource,nullptr);
    glCompileShader(vertexShader);
    complieError(vertexShader,"VERTEX");

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader,1,&fragmentSource,nullptr);
    glCompileShader(fragmentShader);
    complieError(fragmentShader,"FRAGMENT");

    ID= glCreateProgram();
    glAttachShader(ID,vertexShader);
    glAttachShader(ID,fragmentShader);
    glLinkProgram(ID);
    complieError(ID,"PROGRAM");


    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::Active(){
        glUseProgram(ID);
}


void Shader::Delete()
{
    glDeleteProgram(ID);
}

void Shader::complieError(unsigned int shader,const char* type)
{
    int success;
    if(type != "PROGRAM")
    {
        glGetShaderiv(shader,GL_COMPILE_STATUS,&success);
        if(!success)
        {
            glGetShaderInfoLog(shader,512,nullptr,infoLog);
            std::cout <<"ERROR::SHADER:: "<<type <<"::COMPILATION_FAILED\n" << infoLog << '\n';
        }
    }else{
        glGetProgramiv(shader,GL_LINK_STATUS,&success);
        if(!success)
        {
            glGetProgramInfoLog(shader,512,nullptr,infoLog);
            std::cout <<"ERROR::PROGRAM::LINKING_FAILED\n" << infoLog << '\n';
        }
    }
}