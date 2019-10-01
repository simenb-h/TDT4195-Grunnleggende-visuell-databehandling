#version 430 core

in layout(location=1) vec4 colourVertex;
in layout(location=2) vec3 normalVertex;

out vec4 Outcolor;

vec4 color; 
vec3 lightDirection = normalize(vec3(0.8, -0.5, 0.6));

void main()
{

    //color = colourVertex;
    //Outcolor = vec4(normalVertex,1.0f);
    //Outcolor = vec4(normalVertex,1.0f)*max(0.0f,dot(normalVertex,lightDirection));   
    Outcolor = colourVertex*max(0.0f,dot(normalVertex,-lightDirection));  
}



