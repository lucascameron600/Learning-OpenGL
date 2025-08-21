#include <iostream>


#include <glad/gl.h>
#include <GLFW/glfw3.h>
//vertex shader source code
const char* vShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

//handles excape key
void getInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main()
{
    //initialize GLFW
    glfwInit();
    //version 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    //version 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // CORE GLFW profile means we have mot recent functions only
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //error handling for window

    //verticies of our traingle in 3d space normalized cords
    GLfloat verticies[] =
    {
        -0.75f, -0.75f,0.0f,
        0.75f, -0.75f,0.0f,
        0.0f, -0.75f, 0.0f

    };


    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    //ensures that glfw associates the window we are using with the commands we give it
    glfwMakeContextCurrent(window);
    //Glad error handling
    if (!gladLoadGL(glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    

    glViewport(0, 0, 800, 600);

    //unisgned integer shader object v shader is the name
    GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
    //we must attach the shader 1 means number of strings in the array
    //vshdadersource points to the source code definded above
    //Null means the source string is null at the end ???
    glShaderSource(vShader, 1 , &vShaderSource, NULL);
    //compile shader
    glCompileShader(vShader);

    //exact same steps from above but here
    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fShader, 1 , &fShaderSource, NULL);
    glCompileShader(fShader);

    //generating a shader program to link everything
    Gluint shaderApp = glCreateProgram();
    //attaching vshader and fshader to the app
    glAttachShader(shaderApp, vShader);
    glAttachShader(shaderApp, fShader);
    //linking the program????
    glLinkProgram(shaderApp);
    
    //deleting shaders after we are done with them because they are already linked to the program
    glDeleteShader(vShader);
    glDeleteShader(fshader);

    
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    //main while loop
    while(!glfwWindowShouldClose(window))
    {
        glClearColor(1.0f, 0.6f, 0.6f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        getInput(window);

        //render here
        //
        //
        //swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();    
    }
    

    glfwTerminate();
    return 0;
}
