#version 460 core

layout(location = 0) in vec4 aPos; // Vertex position

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, aPos.w); // Set the position of the vertex
}
