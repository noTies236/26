#include <iostream>
#include <vector>
#include "glad/glad.h"
#include "../data/data.h"

namespace pipeline {
	void defineVertex(std::vector<float>& data, GLuint& vao, Layout& p, int ibo[]);
	std::string loadShaderAsString(const std::string source);
	GLuint compilerGLSL(GLuint type, const std::string source);
	GLuint createGraphicProgram(int numberValue);
	//void FBO();
	void loadTexture(const std::string& file, GLuint& storeIdTexrue);
}