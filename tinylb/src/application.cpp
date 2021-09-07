#include<iostream>
#include<math.h>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

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
    GLFWwindow* window = glfwCreateWindow(800,800,"Hello OpenGL",nullptr,nullptr);
    // Error check if the window fails to create
    if(window == nullptr)
    {
        std::cout << "Failed to init window" << '\n';
        glfwTerminate();
    }
    // Introduce the window into current contet
    glfwMakeContextCurrent(window);

    // Load GLAD so it configures opengl
    if(!gladLoadGL()){
        std::cout << "Failed to load GLAD" << '\n';
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }
    // Specify the viewport of OpenGL in the Window
    // In this case the viewport goes from x = 0 y = 0 to x = 800, y = 800 
    glViewport(0,0,800,800); 

    int success ;
    char infoLog[512];
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader,1,&vertexShaderSource,nullptr);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader,512,nullptr,infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << '\n';
    }


    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader,1,&fragmentShaderSource,nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader,512,nullptr,infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << '\n';
    }

    GLuint shaderProgram =  glCreateProgram();
    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram,fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram,GL_LINK_STATUS,&success);
    if(!success)
    {
        glGetProgramInfoLog(shaderProgram,512,nullptr,infoLog);
         std::cout << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog << ' \n';
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    GLfloat vertices[] = {
        -0.5f,-0.5f* float(sqrt(3))/3,0.0f,
        0.5f,-0.5f* float(sqrt(3))/3,0.0f,
        0.0f,0.5f* float(sqrt(3))/3 * 2,0.0f, 
        -0.5f /2,0.5f* float(sqrt(3))/6,0.0f,
        0.5f /2,0.5f* float(sqrt(3))/6,0.0f,
        0.0f,-0.5f* float(sqrt(3))/3,0.0f,
    };

    GLuint indices[] = {
        0,3,5,
        3,2,4,
        5,4,1
    };

    GLuint VAO,VBO,EBO;
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    glGenBuffers(1,&EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3 * sizeof(GL_FLOAT),(void*)0);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);
    
    // Specify the color of the bkacground
    glClearColor(0,0.7f,0.6f,1.0f);
    // Clean the back buffer and assign the new color to it
    glClear(GL_COLOR_BUFFER_BIT);
    // Swap the back buffer with the front buffer
    glfwSwapBuffers(window);

    // Main while
    while(!glfwWindowShouldClose(window))
    {
        // Get all GLFW events
        glfwPollEvents();
        // Specify the color of the background
        glClearColor(0,0.7f,0.6f,1.0f);
        // Clean the back buffer and assign the new color to it
        glClear(GL_COLOR_BUFFER_BIT);
        // Tell OpenGL which Shader Prorgram we want to use
        glUseProgram(shaderProgram);
        // Bind the VAo so OpenGL knows to use it
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES,9,GL_UNSIGNED_INT,0);
        // Swap the back buffer with the frornt buffer
        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
    glDeleteBuffers(1,&EBO);
    glDeleteProgram(shaderProgram);

    // Delete window before ending the program
    glfwDestroyWindow(window);
    // Terminate GLFW
    glfwTerminate();
    return 0;
}