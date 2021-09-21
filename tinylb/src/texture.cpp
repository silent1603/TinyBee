#include "texture.h"
Texture::Texture(const char* image,GLenum texType,GLenum slot, GLenum format,GLenum pixelType){
    type = texType;
    int widthImg, heightImg, numberColorChannel;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* bytes = stbi_load(image,&widthImg,&heightImg,&numberColorChannel,0);

    
    glGenTextures(1,&ID);
    glActiveTexture(slot);
    glBindTexture(texType,ID);
    
    glTexParameteri(texType,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(texType,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

    glTexParameteri(texType,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(texType,GL_TEXTURE_WRAP_T,GL_REPEAT);
    
    // Extra lines in case you choose to use GL_CLAMP_TO_BORDER 
	// float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
	// glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);
    
    glTexImage2D(texType,0,GL_RGBA,widthImg,heightImg,0,format,pixelType,bytes);    
    glGenerateMipmap(texType);

    stbi_image_free(bytes);
    glBindTexture(texType,0);
}

Texture::~Texture(){
    Delete();
}

void Texture::texUnit(Shader& shader,const char* uniform, GLuint unit){
    GLuint texSlotUnit = glGetUniformLocation(shader.ID,uniform);
    shader.Active();
    glUniform1i(texSlotUnit,unit);
}


    
void Texture::Bind(){
    glBindTexture(type,ID);
}

void Texture::UnBind(){
    glBindTexture(type,0);
}

void Texture::Delete(){
    glDeleteTextures(1,&ID);
}