#version 430 core

in layout(location=1) vec4 colourVertex;
in layout(location=2) vec3 normalVertex;

out vec4 Outcolor;

vec4 color; 
vec3 lightDirection = normalize(vec3(0.8, -0.5, 0.6));

uniform layout(location = 4) mat4 ModelMatrix;


vec3 vnormal = normalize(mat3(ModelMatrix) * normalVertex);

void main()
{
    Outcolor = colourVertex*max(0.0f,dot(vnormal,-lightDirection));  
}



