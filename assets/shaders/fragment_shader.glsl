#version 460 core

in vec3 ourColor; // Color passed from vertex shader
out vec4 FragColor;

void main()
{
    FragColor = vec4(ourColor, 1.0); // Set the output color of the fragment
}
