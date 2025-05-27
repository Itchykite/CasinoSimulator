#include <string>
#include <GL/glew.h>

std::string LoadShaderSource(const std::string& filePath);
GLuint CompileShader(GLenum type, const std::string& source);
GLuint CreateShaderProgram(const std::string& vertexPath, const std::string& fragmentPath);
