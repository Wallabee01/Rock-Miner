#pragma once
#include <string>
#include <GL/glew.h>

namespace SPH {

	class GLSLProgram
	{
	public:
		GLSLProgram() : _numAttributes(0), _programID(0), _vertexShaderID(0), _fragmentShaderID(0) {} // Initialize ivars in constructor
		~GLSLProgram();

		void compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);  // Can label const bc dont want it to change, can pass by reference, if the file
		void compileShadersFromSource(const char* vertexSource, const char* fragmentSource);																												// size is large it is more efficent to pass by reference

		void linkShaders();
		void addAttribute(const std::string& attributeName);
		void use();
		void unuse();
		GLint getUniformLocation(const std::string& uniformName);

		void dispose();

	private:

		void compileShader(const char* source, const std::string& fileID, GLuint id);

		int _numAttributes;
		GLuint _programID;
		GLuint _vertexShaderID;
		GLuint _fragmentShaderID;
	};

}