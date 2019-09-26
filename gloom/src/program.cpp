// Local headers
#include "program.hpp"
#include "gloom/gloom.hpp"
#include "gloom/shader.hpp"

#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <math.h>
#include <vector>

//Declaring the createVAO function here, and defining it below. 
int createVertexArrayObject(std::vector<float> vertices, int vertex_size, std::vector<int> indices, int indices_size, std::vector<float> colour, int colour_size);

//Motion variables - 4c 
float Xmotion = 0.0f;
float Ymotion = 0.0f;
float Zmotion = 0.0f;
float PanSide = 0.0f;
float PanUpDown = 0.0f; 


void runProgram(GLFWwindow* window)
{

    float accumulative_variable = 0;
    // Enable depth (Z) buffer (accept "closest" fragment)
    //glEnable(GL_DEPTH_TEST);
    //glDepthFunc(GL_LESS);

    // Configure miscellaneous OpenGL settings
    glEnable(GL_CULL_FACE);

    // Set default colour after clearing the colour buffer
    glClearColor(0.3f, 0.5f, 0.8f, 1.0f);

    //Added in assignment 2 to enable transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    // Set up your scene here (create Vertex Array Objects, etc.)


    //buffer_values input
    std::vector<float> buffer_values = {
       //3 triangles overlapping
        -0.4f,0.4f,0.6f,
        0.4f,0.4f,0.6f,
        0.0f,-0.4f,0.6f,

      
        0.0f,0.4f,0.4f,
        -0.4f,-0.4f,0.4f,
        0.4f,-0.4f,0.4f,


        0.0f,0.4f,0.2f,
        0.0f,-0.4f,0.2f,
        0.4f,0.0f,0.2f,

   
       //5 triangles
       /*
        -0.8f,0.4f,0.0f,
        -0.4f,0.4f,0.0f,
        -0.6f,0.8f,0.0f,

         0.6f,0.8f,0.0f,
        0.4f,0.4f,0.0f,
        0.8f,0.4f,0.0f,

        0.0f,0.2f,0.0f,
        -0.2f,-0.2f,0.0f,
        0.2f,-0.2f,0.0f,

        -0.8f,-0.8f,0.0f,
        -0.4f,-0.8f,0.0f,
        -0.6f,-0.4f,0.0f,

        0.6f,-0.4f,0.0f,
        0.4f,-0.8f,0.0f,
        0.8f,-0.8f,0.0f,
        */

       };


    std::vector<float> colour = {
        //Colours for 3 triangles
        1.0f, 0.0f, 0.0f, 0.5f,
        1.0f, 0.0f, 0.0f, 0.5f,
        1.0f, 0.0f, 0.0f, 0.5f,    
        
        0.0f, 1.0f, 0.0f, 0.5f,
        0.0f, 1.0f, 0.0f, 0.5f,
        0.0f, 1.0f, 0.0f, 0.5f,        
 
        0.0f, 0.0f, 1.0f, 0.5f,
        0.0f, 0.0f, 1.0f, 0.5f,
        0.0f, 0.0f, 1.0f, 0.5f, 


        //Colours for 5 triangles
      /*  1.0f, 0.0f, 0.0f, 0.4f,
        0.0f, 1.0f, 0.0f, 0.4f,
        0.0f, 0.0f, 1.0f, 0.4f,
         1.0f, 0.0f, 0.0f, 0.4f,
        0.0f, 1.0f, 0.0f, 0.4f,
        0.0f, 0.0f, 1.0f, 0.4f,
         1.0f, 0.0f, 0.0f, 0.4f,
        0.0f, 1.0f, 0.0f, 0.4f,
        0.0f, 0.0f, 1.0f, 0.4f,
         1.0f, 0.0f, 0.0f, 0.4f,
        0.0f, 1.0f, 0.0f, 0.4f,
        0.0f, 0.0f, 1.0f, 0.4f,
         1.0f, 0.0f, 0.0f, 0.4f,
        0.0f, 1.0f, 0.0f, 0.4f,
        0.0f, 0.0f, 1.0f, 0.4f, 
        */
    };


    //buffer_indecis input
    std::vector<int> buffer_indices = {1,0,2,4,5,3,7,8,6};
    // std::vector<int> buffer_indices = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14};

    //Calling the function that creates VAO 
    createVertexArrayObject(buffer_values, buffer_values.size(), buffer_indices, buffer_indices.size(), colour, colour.size());

    //gloom loading shaders, only vertex and fragment shaders
    Gloom::Shader shader;
    shader.makeBasicShader("../gloom/shaders/simple.vert", "../gloom/shaders/simple.frag");
    
    // Activate shader program
    shader.activate();

 

    // Rendering Loop
    while (!glfwWindowShouldClose(window))
    {
        // Clear colour and depth buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES,(buffer_indices).size(), GL_UNSIGNED_INT,0);

        // Handle other events
        glfwPollEvents();
        handleKeyboardInput(window);

        // Flip buffers
        glfwSwapBuffers(window);

        //Accumulative variable
        accumulative_variable += 0.02;
        float sin_av = sin(accumulative_variable)-0.5;

        //Task 3b
        glUniform4f(2,sin_av,0,0,0); //a
        glUniform4f(5,1,sin_av,0,0); //b
        glUniform4f(6,1,0,0,sin_av); //c
        glUniform4f(7,sin_av,1,0,0); //d
        glUniform4f(8,0,sin_av,0,0); //e
        glUniform4f(9,0,1,0,sin_av); //f 




        //Task 4b   //move the matrices that dont change for each frame to runProgram()
        glm::mat4x4 TranslateNegativeZ = glm::mat4(glm::vec4(1,0,0,0),glm::vec4(0,1,0,0),glm::vec4(0,0,-20,0),glm::vec4(0,0,0,1));
        glm::mat4x4 PerspectiveMatrix = glm::perspective(glm::radians(35.0f), 16.0f / 9.0f, 1.0f, 100.0f);
        //glm::mat4x4 PerspectiveProjection = PerspectiveMatrix*TranslateNegativeZ;
        //glUniformMatrix4fv(3,1, GL_FALSE,glm::value_ptr(PerspectiveProjection));


        //Task 4c   
        //Translate x,y and z direction
        glm::mat4x4 Translate = glm::translate(glm::vec3(Xmotion,Ymotion,Zmotion));

        //Rotation around X axis
        glm::mat4x4 RotateX = glm::rotate(glm::radians(PanUpDown), glm::vec3(1,0,0));     

        //Rotation around Y axis   
        glm::mat4x4 RotateY = glm::rotate(glm::radians(PanSide), glm::vec3(0,1,0)); 

        //Scaling 
        glm::mat4x4 Scale = glm::scale(glm::vec3(1,1,1));    

        
        //Task 4d
        glm::mat4x4 CameraMovement = PerspectiveMatrix*Scale*RotateY*RotateX*Translate*TranslateNegativeZ;
        glUniformMatrix4fv(3,1,GL_FALSE, glm::value_ptr(CameraMovement));
      

    }
    // Deactivate shader program
    shader.deactivate();

    //delete the shader program when exiting
    shader.destroy();
}


//Function createVertexArrayObject()
int createVertexArrayObject(std::vector<float> vertices, int vertex_size, std::vector<int> indices, int indices_size, std::vector<float> colour, int colour_size){

     //create new VAO and Binds the VAO
        unsigned int arrayID;
        glGenVertexArrays(1,&arrayID);
        glBindVertexArray(arrayID);

    //Create and Binds the VBO
        unsigned int bufferID;
        glGenBuffers(1,&bufferID);
        glBindBuffer(GL_ARRAY_BUFFER,bufferID);        
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*vertex_size, &vertices[0] , GL_STATIC_DRAW); //Transfer the data to the GPU
        //glBufferData(GL_ARRAY_BUFFER, vertex_size, vertices, GL_STATIC_DRAW); 

        //Vertex Attribute Pointer
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,0, 0 );

        //Enable the Vertex Attribute
        glEnableVertexAttribArray(0);

        
        //The index buffer
        //Generate another buffer
        unsigned int index_buffer;
        glGenBuffers(1, &index_buffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,index_buffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*indices_size, &indices[0], GL_STATIC_DRAW); 

        
        //Colour VBO
        unsigned int colour_bufferID;
        glGenBuffers(1,&colour_bufferID);
        glBindBuffer(GL_ARRAY_BUFFER,colour_bufferID);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*colour_size, &colour[0], GL_STATIC_DRAW); 

        //Enable the Vertex Attribute
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE,0, 0);

        return arrayID;
}



void handleKeyboardInput(GLFWwindow* window)
{
    // Use escape key for terminating the GLFW window
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        Xmotion += 0.1;
        //Move left
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        Xmotion -= 0.1;

        //Move right
    }
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        Zmotion += 0.1;
        //Move forward
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        Zmotion -= 0.1;
        //Move back
    }

    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        Ymotion -= 0.1;
        //Go up
    }
    if(glfwGetKey(window, GLFW_KEY_LEFT_ALT ) == GLFW_PRESS)
    {   
        Ymotion += 0.1;
        //Go down
    }


     if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        //Pan left
        PanSide -= 0.3;
    }
    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        //Pan right
        PanSide += 0.3;
    }
    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        PanUpDown -= 0.3; 
        //Pan ip
    }
    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        PanUpDown += 0.3; 
        //Pan down
    }
}
