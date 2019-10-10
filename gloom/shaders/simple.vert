#version 430 core


in vec3 position;

in layout(location=1) vec4 colourVertex;
out layout(location=1) vec4 OutcolourVertex;

in layout(location=2) vec3 NormalVertex; 
out layout(location=2) vec3 OutNormalVertex; 

//uniform layout(location = 4) mat4 ModelMatrix;



uniform layout(location = 3) mat4 ModelViewProjectionMatrix;


void main()
{
    OutcolourVertex = colourVertex;

    OutNormalVertex = NormalVertex;

    gl_Position = ModelViewProjectionMatrix*vec4(position,1.0f);
}


    