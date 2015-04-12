#version 400

////////////////////
//Input Variable///
//////////////////

in vec3 inputPosition;

//////////////////////
//UNIFORM Variable////
/////////////////////

uniform mat4 worldMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

/////////////////////////
//Vertex Shader//////////
////////////////////////

void main(void)
{
	///calculate the pos of the vertex in world,view,projection 
	gl_Position = worldMatrix * vec4(inputPosition,1.0f);
	gl_Position = viewMatrix * gl_Position;
	gl_Position = projectionMatrix * gl_Position;
}
