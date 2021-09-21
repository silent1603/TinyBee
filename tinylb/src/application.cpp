#include<iostream>
#include<filesystem>
#include<string>
#include<math.h>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>


#include "shader.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "texture.h"
#include "camera.h"

const int width =800;
const int height = 800;
int main()
{
    // Initialize GLFW
    glfwInit();
    // Tell GLFW what version of OpenGl we are using
    // In this case we are using OPenGl 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    // Tell GLFW we are using the CORE profile
    // So that means we only have the modern functions
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    // Create a GLFWwindow object of 800 by 800 pixel , name it "Hello OpenGL"
    GLFWwindow* window = glfwCreateWindow(width,height,"Hello OpenGL",nullptr,nullptr);
    // Error check if the window fails to create
    if(window == nullptr)
    {
        std::cout << "Failed to init window" << '\n';
        glfwTerminate();
    }
    // Introduce the window into current contet
    glfwMakeContextCurrent(window);

    // Load GLAD so it configures opengl
    // if(!gladLoadGL()){
    //     std::cout << "Failed to load GLAD" << '\n';
    //     glfwDestroyWindow(window);
    //     glfwTerminate();
    //     return -1;
    // }
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to load GLAD" << '\n';
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }
    // Specify the viewport of OpenGL in the Window
    // In this case the viewport goes from x = 0 y = 0 to x = 800, y = 800 
    glViewport(0,0,800,800); 

    //enable VSync
    //glfwSwapInterval(1);

  
    Camera Camera(width,height,glm::vec3(0.0f,1.0f,3.0f)); 
  
  
    
 


    GLfloat vertices[] = {
        -0.5f,0.0f,0.5f,    1.0f,1.0f,1.0f, 0.0f , 0.0f,
        -0.5f,0.0f,-0.5f,   1.0f,1.0f,1.0f, 5.0f , 0.0f,
        0.5f,0.0f,-0.5f,    1.0f,1.0f,1.0f, 0.0f , 0.0f,
        0.5f,0.0f,0.5f,    1.0f,1.0f,1.0f, 5.0f , 0.0f,
        0.0f,0.8f,0.0f ,    1.0f,1.0f,1.0f, 2.5f , 5.0f
    };

    GLuint indices[] = {
        0,1,2,
        0,2,3,
        0,1,4,
        1,2,4,
        2,3,4,
        3,0,4
    };

    Shader defaultShader("../tinylb/shaders/default.vert","../tinylb/shaders/default.frag");
    
    VAO VAOMain;
    VAOMain.Bind();
    
    VBO VBOMain(vertices,sizeof(vertices));
    EBO EBOMain(indices,sizeof(indices));


    VAOMain.LinkAttrib(VBOMain,0,3,GL_FLOAT,8*sizeof(float),(void*)0);
    VAOMain.LinkAttrib(VBOMain,1,3,GL_FLOAT,8*sizeof(float),(void*) (3*sizeof(float)));
    VAOMain.LinkAttrib(VBOMain,2,2,GL_FLOAT,8*sizeof(float),(void*) (6*sizeof(float)));
    EBOMain.Bind();

    VAOMain.Unbind();
    VBOMain.Unbind();
    EBOMain.Unbind(); 

    
    std::string texPath = "../tinylb/resources/brick.png";
    Texture popCat(texPath.c_str(),GL_TEXTURE_2D,GL_TEXTURE0,GL_RGBA,GL_UNSIGNED_BYTE);
    popCat.texUnit(defaultShader,"tex0",0);
    glEnable(GL_DEPTH_TEST);
    // Main while
    while(!glfwWindowShouldClose(window))
    {
        // Get all GLFW events
        glfwPollEvents();
        // Specify the color of the background
        glClearColor(0,0.7f,0.6f,1.0f);
        // Clean the back buffer and assign the new color to it
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        defaultShader.Active();

        Camera.Input(window);
        Camera.Setup(45.0f,0.1f,100.0f,defaultShader,"cameraMatrix");
      
        popCat.Bind();
        VAOMain.Bind();
      
        glDrawElements(GL_TRIANGLES,sizeof(indices)/sizeof(int),GL_UNSIGNED_INT,0);
        // Swap the back buffer with the frornt buffer
        glfwSwapBuffers(window);
    }

    VAOMain.Delete();
    VBOMain.Delete();
    EBOMain.Delete();   
    defaultShader.Delete();
    popCat.Delete();
    // Delete window before ending the program
    glfwDestroyWindow(window);
    // Terminate GLFW
    glfwTerminate();
    return 0;
}