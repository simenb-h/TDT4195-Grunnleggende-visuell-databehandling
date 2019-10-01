// Local headers
#include "program.hpp"
#include "gloom/gloom.hpp"
#include "gloom/shader.hpp"
#include "mesh.hpp"
#include "OBJLoader.hpp"
#include "toolbox.hpp"
#include "sceneGraph.hpp"

#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <math.h>
#include <vector>   
#include <list>
#include <algorithm> 


//Declaring the createVAO function here, and defining it below. 
int createVertexArrayObject(std::vector<float> vertices, int vertex_size, std::vector<unsigned int> indices,int indices_size, std::vector<float> colour,int colour_size, std::vector<float> normal ,int normal_size );

//Declaring the drawSceneNode function here, and defining it below. 
void drawSceneNode(SceneNode* root, glm::mat4 viewProjectionMatrix);


//Motion variables - 4c 
float Xmotion = 0.0f;
float Ymotion = 0.0f;
float Zmotion = 0.0f;
float PanSide = 0.0f;
float PanUpDown = 0.0f; 


//Indices length of terrain and helicopter parts mesh
unsigned int lengthOfTerrainObj = 0; 
unsigned int lengthOfHelicopterBody = 0; 
unsigned int lengthOfHelicopterDoor = 0; 
unsigned int lengthOfHelicopterTailRotor = 0; 
unsigned int lengthOfHelicopterMainRoter = 0; 



void runProgram(GLFWwindow* window)
{
    //Creates the nodes og all the helicopter parts, terrain and a root
    SceneNode* root = createSceneNode(); 
    SceneNode* terrainNode = createSceneNode();
    SceneNode* heliBodyNode = createSceneNode();
    SceneNode* heliTailNode = createSceneNode();
    SceneNode* heliMainRotorNode = createSceneNode();
    SceneNode* heliDoorNode = createSceneNode();
    
    //Add helicopter body as parent of the other parts, tarrain parent of helicopter body, and root parent of terrain
    addChild(root, terrainNode);
    addChild(terrainNode, heliBodyNode);
    addChild(heliBodyNode, heliDoorNode);
    addChild(heliBodyNode, heliTailNode);
    addChild(heliBodyNode, heliMainRotorNode);

   //Load terrain and set the VAO ID and VAOIndexCount for the terrain node 
    struct Mesh TerrainObj = loadTerrainMesh("../gloom/resources/lunarsurface.obj");
    terrainNode->vertexArrayObjectID = createVertexArrayObject(TerrainObj.vertices, TerrainObj.vertices.size(), TerrainObj.indices, TerrainObj.indices.size(), TerrainObj.colours, TerrainObj.colours.size(), TerrainObj.normals, TerrainObj.normals.size());
    terrainNode->VAOIndexCount = TerrainObj.indices.size();

   //Load helicopter and set the VAO ID and VAOIndexCount for the helicopter-part nodes 
    struct Helicopter HelicopterObj  = loadHelicopterModel("../gloom/resources/helicopter.obj");
    heliDoorNode->vertexArrayObjectID = createVertexArrayObject(HelicopterObj.door.vertices, HelicopterObj.door.vertices.size(), HelicopterObj.door.indices, HelicopterObj.door.indices.size(), HelicopterObj.door.colours, HelicopterObj.door.colours.size(), HelicopterObj.door.normals, HelicopterObj.door.normals.size());
    heliDoorNode->VAOIndexCount = HelicopterObj.door.indices.size();
    
    heliBodyNode->vertexArrayObjectID = createVertexArrayObject(HelicopterObj.body.vertices, HelicopterObj.body.vertices.size(), HelicopterObj.body.indices, HelicopterObj.body.indices.size(), HelicopterObj.body.colours, HelicopterObj.body.colours.size(), HelicopterObj.body.normals, HelicopterObj.body.normals.size());
    heliBodyNode->VAOIndexCount = HelicopterObj.body.indices.size();

    heliMainRotorNode->vertexArrayObjectID = createVertexArrayObject(HelicopterObj.mainRotor.vertices, HelicopterObj.mainRotor.vertices.size(), HelicopterObj.mainRotor.indices, HelicopterObj.mainRotor.indices.size(), HelicopterObj.mainRotor.colours, HelicopterObj.mainRotor.colours.size(), HelicopterObj.mainRotor.normals, HelicopterObj.mainRotor.normals.size());
    heliMainRotorNode->VAOIndexCount = HelicopterObj.mainRotor.indices.size();

    heliTailNode->vertexArrayObjectID = createVertexArrayObject(HelicopterObj.tailRotor.vertices, HelicopterObj.tailRotor.vertices.size(), HelicopterObj.tailRotor.indices, HelicopterObj.tailRotor.indices.size(), HelicopterObj.tailRotor.colours, HelicopterObj.tailRotor.colours.size(), HelicopterObj.tailRotor.normals, HelicopterObj.tailRotor.normals.size());
    heliTailNode->VAOIndexCount = HelicopterObj.tailRotor.indices.size();


    printNode(root);
    printNode(terrainNode);
    printNode(heliBodyNode);
    printNode(heliTailNode);
    printNode(heliMainRotorNode);
    printNode(heliDoorNode);

    // Enable depth (Z) buffer (accept "closest" fragment)
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Configure miscellaneous OpenGL settings
    glEnable(GL_CULL_FACE);

    // Set default colour after clearing the colour buffer
    glClearColor(0.3f, 0.5f, 0.8f, 1.0f);

    //gloom loading shaders, only vertex and fragment shaders
    Gloom::Shader shader;
    shader.makeBasicShader("../gloom/shaders/simple.vert", "../gloom/shaders/simple.frag");
    
    // Activate shader program
    shader.activate();


    /*
    TASK 1
    //Creates VAO for terrain
    struct Mesh TerrainObj = loadTerrainMesh("../gloom/resources/lunarsurface.obj");
    lengthOfTerrainObj = TerrainObj.indices.size();
    int VAOterrain = createVertexArrayObject(TerrainObj.vertices, TerrainObj.vertices.size(), TerrainObj.indices, TerrainObj.indices.size(), TerrainObj.colours, TerrainObj.colours.size(), TerrainObj.normals, TerrainObj.normals.size());
    // Task 1acreateVertexArrayObject(TerrainObj.vertices, TerrainObj.vertices.size(), TerrainObj.indices, TerrainObj.indices.size(), TerrainObj.colours, TerrainObj.colours.size());

    //Creates VAOs for all the helicopter parts and stores the arrayID as an int, I will use to bind the VAO in the rendering loop
    struct Helicopter HelicopterObj  = loadHelicopterModel("../gloom/resources/helicopter.obj");
    //lengthOfHelicopterDoor = HelicopterObj.door.indices.size();
    int VAOhelicopterDoor= createVertexArrayObject(HelicopterObj.door.vertices, HelicopterObj.door.vertices.size(), HelicopterObj.door.indices, HelicopterObj.door.indices.size(), HelicopterObj.door.colours, HelicopterObj.door.colours.size(), HelicopterObj.door.normals, HelicopterObj.door.normals.size());
    lengthOfHelicopterBody = HelicopterObj.body.indices.size();
    int VAOhelicopterBody = createVertexArrayObject(HelicopterObj.body.vertices, HelicopterObj.body.vertices.size(), HelicopterObj.body.indices, HelicopterObj.body.indices.size(), HelicopterObj.body.colours, HelicopterObj.body.colours.size(), HelicopterObj.body.normals, HelicopterObj.body.normals.size());
    lengthOfHelicopterMainRoter = HelicopterObj.mainRotor.indices.size();
    int VAOhelicopterMainRotor = createVertexArrayObject(HelicopterObj.mainRotor.vertices, HelicopterObj.mainRotor.vertices.size(), HelicopterObj.mainRotor.indices, HelicopterObj.mainRotor.indices.size(), HelicopterObj.mainRotor.colours, HelicopterObj.mainRotor.colours.size(), HelicopterObj.mainRotor.normals, HelicopterObj.mainRotor.normals.size());
    lengthOfHelicopterTailRotor = HelicopterObj.tailRotor.indices.size();
    int VAOhelicopterTailRotor = createVertexArrayObject(HelicopterObj.tailRotor.vertices, HelicopterObj.tailRotor.vertices.size(), HelicopterObj.tailRotor.indices, HelicopterObj.tailRotor.indices.size(), HelicopterObj.tailRotor.colours, HelicopterObj.tailRotor.colours.size(), HelicopterObj.tailRotor.normals, HelicopterObj.tailRotor.normals.size());
*/



    // Rendering Loop
    while (!glfwWindowShouldClose(window))
    {
        // Clear colour and depth buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        //Transformations
        glm::mat4x4 TranslateNegativeZ = glm::mat4(glm::vec4(1,0,0,0),glm::vec4(0,1,0,0),glm::vec4(0,0,1,0),glm::vec4(0,0,0,1));
        glm::mat4x4 PerspectiveMatrix = glm::perspective(glm::radians(35.0f), 16.0f / 9.0f, 1.0f, 1000.0f);
        glm::mat4x4 Translate = glm::translate(glm::vec3(Xmotion,Ymotion,Zmotion));
        glm::mat4x4 RotateX = glm::rotate(glm::radians(PanUpDown), glm::vec3(1,0,0));     
        glm::mat4x4 RotateY = glm::rotate(glm::radians(PanSide), glm::vec3(0,1,0)); 
        glm::mat4x4 Scale = glm::scale(glm::vec3(1,1,1));    
        glm::mat4x4 CameraMovement = PerspectiveMatrix*Scale*RotateX*RotateY*Translate*TranslateNegativeZ;
        glUniformMatrix4fv(3,1,GL_FALSE, glm::value_ptr(CameraMovement));

        //Draw the scene in order of the scene graph using the drawSceneNode function
        drawSceneNode(root, CameraMovement);

        // Handle other events
        glfwPollEvents();
        handleKeyboardInput(window);

        // Flip buffers
        glfwSwapBuffers(window);

        printGLError();

      
    


    /* Task 1d 
        //Bind VAO og draw tarrain
        glBindVertexArray(VAOterrain);
        glDrawElements(GL_TRIANGLES,lengthOfTerrainObj , GL_UNSIGNED_INT,0);
        //Bind VAO og draw main rotor
        glBindVertexArray(VAOhelicopterMainRotor);
        glDrawElements(GL_TRIANGLES,lengthOfHelicopterMainRoter, GL_UNSIGNED_INT,0);
        //Bind VAO og draw door
        glBindVertexArray(VAOhelicopterDoor);
        glDrawElements(GL_TRIANGLES,lengthOfHelicopterDoor , GL_UNSIGNED_INT,0);
        //Bind VAO og draw tail rotor
        glBindVertexArray(VAOhelicopterTailRotor);
        glDrawElements(GL_TRIANGLES,lengthOfHelicopterTailRotor , GL_UNSIGNED_INT,0);
        //Bind VAO og draw body
        glBindVertexArray(VAOhelicopterBody);
        glDrawElements(GL_TRIANGLES,lengthOfHelicopterBody , GL_UNSIGNED_INT,0);
    */

    }

    // Deactivate shader program
    shader.deactivate();

    //delete the shader program when exiting
    shader.destroy();
}


//Function createVertexArrayObject()
int createVertexArrayObject(std::vector<float> vertices, int vertex_size, std::vector<unsigned int> indices, int indices_size, std::vector<float> colour, int colour_size, std::vector<float> normal  ,int normal_size ){
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



        //Normal VBO
        unsigned int normal_bufferID;
        glGenBuffers(1,&normal_bufferID);
        glBindBuffer(GL_ARRAY_BUFFER,normal_bufferID);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*normal_size, &normal[0], GL_STATIC_DRAW); 

        //Enable the Vertex Attribute
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE,0, 0);

        return arrayID;
}

//Function drawSceneNode() that iterates trough every child of the root, bind the VAO and draw it 
void drawSceneNode(SceneNode* root, glm::mat4 viewProjectionMatrix) {
    glBindVertexArray(root->vertexArrayObjectID);
    glDrawElements(GL_TRIANGLES,root->VAOIndexCount, GL_UNSIGNED_INT,0);
    for (SceneNode* child : root->children) {
        drawSceneNode(child, viewProjectionMatrix);
    }
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
        Xmotion += 2.5;
        //Move left
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        Xmotion -= 2.5;

        //Move right
    }
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        Zmotion += 2.5;
        //Move forward
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        Zmotion -= 2.5;
        //Move back
    }

    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        Ymotion -= 2.5;
        //Go up
    }
    if(glfwGetKey(window, GLFW_KEY_LEFT_ALT ) == GLFW_PRESS)
    {   
        Ymotion += 2.5;
        //Go down
    }


     if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        //Pan left
        PanSide -= 2.5;
    }
    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        //Pan right
        PanSide += 2.5;
    }
    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        PanUpDown -= 2.5; 
        //Pan ip
    }
    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        PanUpDown += 2.5; 
        //Pan down
    }
}
