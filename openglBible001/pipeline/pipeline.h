#include <iostream>
#include <vector>
#include "glad/glad.h"
#include "../data/data.h"
#include "./glm/glm/glm.hpp"
#include "./glm/glm/mat4x4.hpp"
#include "./glm/glm/gtc/matrix_transform.hpp"
#include "./glm/glm/gtc/type_ptr.hpp"


namespace pipeline {
	void defineVertex(std::vector<float>& data, GLuint& vao, Layout& p, int ibo[]);
	std::string loadShaderAsString(const std::string source);
	GLuint compilerGLSL(GLuint type, const std::string source);
	GLuint createGraphicProgram(int numberValue);
	//void FBO();
	void loadTexture(const std::string& file, GLuint& storeIdTexrue);
}