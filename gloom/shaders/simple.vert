#version 430 core


in vec3 position;
in layout(location=1) vec4 colourVertex;
out layout(location=1) vec4 OutcolourVertex;

in layout(location=2) vec3 NormalVertex; 
out layout(location=2) vec3 OutNormalVertex; 

//Task 3a
mat4x4 IdentityMatrix = {{1.0f,0.0f,0.0f,0.0f}, {0.0f,1.0f,0.0f,0.0f}, {0.0f,0.0f,1.0f,0.0f}, {0.0f,0.0f,0.0f,1.0f}};


//Task 3b
//uniform layout(location=2) vec4 A;
//uniform layout(location=5) vec4 B;
//uniform layout(location=6) vec4 C;
//uniform layout(location=7) vec4 D;
//uniform layout(location=8) vec4 E;
//uniform layout(location=9) vec4 F;
//mat4x4 M = {A, {0.0f,1.0f,0.0f,0.0f}, {0.0f,0.0f,1.0f,0.0f}, {0.0f,0.0f,0.0f,1.0f}}; // a // 
//mat4x4 M = {B, {0.0f,1.0f,0.0f,0.0f}, {0.0f,0.0f,1.0f,0.0f}, {0.0f,0.0f,0.0f,1.0f}}; // b //
//mat4x4 M = {C, {0.0f,1.0f,0.0f,0.0f}, {0.0f,0.0f,1.0f,0.0f}, {0.0f,0.0f,0.0f,1.0f}}; // c //
//mat4x4 M = {{1.0f,0.0f,0.0f,0.0f},D, {0.0f,0.0f,1.0f,0.0f}, {0.0f,0.0f,0.0f,1.0f}}; // d //
//mat4x4 M = {{1.0f,0.0f,0.0f,0.0f},E, {0.0f,0.0f,1.0f,0.0f}, {0.0f,0.0f,0.0f,1.0f}}; // e //
//mat4x4 M = {{1.0f,0.0f,0.0f,0.0f},F, {0.0f,0.0f,1.0f,0.0f}, {0.0f,0.0f,0.0f,1.0f}}; // f //



//Task 4
uniform layout(location = 3) mat4 T;


void main()
{
    OutcolourVertex = colourVertex;

    OutNormalVertex = NormalVertex;

    //Task 2b
    //gl_Position = vec4(position,1.0f);


    //Task 3a
    //gl_Position = I*vec4(position,1.0f);


    //Task 3b
    //gl_Position = transpose(M)*vec4(position,1.0f);


    //Task 4
    gl_Position = T*vec4(position,1.0f);
}


    