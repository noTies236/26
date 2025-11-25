#define STB_IMAGE_IMPLEMENTATION
#include "./pipeline.h"
#include "../stb_image.h"

int aa = 0;

void pipeline::defineVertex(std::vector<float>& data, GLuint& vao, Layout& p, int ibo[])
{
	GLuint vbo;
	GLuint EBO;

	int iboTest[] = {
		0,1,2,
		0, 2,3
	};

	glCreateVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	glCreateBuffers(1, &vbo);	
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * data.size(), data.data(), GL_STATIC_DRAW);

	glCreateBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(iboTest) , iboTest, GL_STATIC_DRAW);
	// vertex
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * p.strideOS, (void*)p.ptr);
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * p.strideOS, (void*)p.ptr);
	glEnableVertexAttribArray(2);
}

GLuint pipeline::compilerGLSL(GLuint type, const std::string source)
{
	GLuint program = glCreateShader(type);
	const char* sourceData = source.c_str();

	glShaderSource(program, 1, &sourceData, nullptr);
	glCompileShader(program);
	
	return program;
}

GLuint pipeline::createGraphicProgram(int numberValue)
{

	std::cout << "has been compiled: " << aa << "\n";
	aa++;
	GLuint program = glCreateProgram();

	// shader program one
	std::string vertexShaderFile {
		"#version 430 core\n"
		"\n"
		"out vec2 coordValue;\n"
		"\n"
		"uniform float xxx;\n"
		"\n"
		"layout (location = 1) in vec3 aPos;\n"
		"layout (location = 2) in vec2 aCoord;\n"
		"\n"
		"void main() {\n"
		"	gl_Position = vec4(aPos.x+xxx, aPos.y, 0.0, 1.0);\n"
		"	coordValue = vec2(aCoord);\n"
		"}\n"
	};

	std::string vertexFragmentFile {
		"#version 430 core\n"
		"\n"
		"in vec2 coordValue;\n"
		"\n"
		"out vec4 FragColor;\n"
		"\n"
		"uniform sampler2D texture;\n"
		"\n"
		"void main() {\n"
		"\n"
		"	FragColor =  texture(texture, coordValue) * vec4(1.0,0.0,0.8,1.0);\n"
		"}\n"
	};

	// shader program two
	std::string vertexShaderProgramTwo {
		"#version 430 core"
		"\n"
		"uniform float uY;\n"
		"uniform float uX;\n"
		"uniform mat4 model;\n"
		"uniform mat4 view;\n"
		"uniform mat4 projection;\n"
		"\n"
		"\n"
		"layout (location = 1) in vec3 aPos;\n"
		"layout (location = 2) in vec3 aCoord;\n"
		"\n"
		"out vec2 coordValue;\n"
		"\n"
		"void main() {\n"
		"\n"
		"	gl_Position = projection * view * model * vec4(aPos.x+uX, aPos.y+uY, 0.0, 1.0);\n"
		"	coordValue = vec2(aCoord);\n"
		"}\n"
	};

	std::string fragmentShaderProgramTwo {
		"#version 430 core"
		"\n"
		"in vec2 coordValue;\n"
		"\n"
		"out vec4 FragColor;\n"
		"\n"
		"uniform sampler2D texture;\n"
		"\n"
		"void main () {\n"
		"	FragColor = texture(texture, coordValue);\n"
		"}\n"
	};

	GLuint vertexCompiled = 0;  
	GLuint fragmentCompiled = 0;

	if (numberValue == 1) {
		vertexCompiled = compilerGLSL(GL_VERTEX_SHADER, vertexShaderFile);
		fragmentCompiled = compilerGLSL(GL_FRAGMENT_SHADER, vertexFragmentFile);
		std::cout << "shader triangle: OK\n";
	}
	else
	{
		vertexCompiled = compilerGLSL(GL_VERTEX_SHADER, vertexShaderProgramTwo);
		fragmentCompiled = compilerGLSL(GL_FRAGMENT_SHADER, fragmentShaderProgramTwo);
		std::cout << "shader square: OK";
	}

	glAttachShader(program, vertexCompiled);
	glAttachShader(program, fragmentCompiled);
	glLinkProgram(program);

	return program;
}

//void pipeline::FBO()
//{
//	
//	GLuint fbo;
//	glGenFramebuffers(1, &fbo);
//	std::cout << "this is my framebuffer!!!";
//
//	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
//}

void pipeline::loadTexture(const std::string& file, GLuint& storeIdTexrue)
{
	stbi_set_flip_vertically_on_load(true);
	glGenTextures(1, &storeIdTexrue);
	//glBindTexture(GL_TEXTURE_2D, storeIdTexrue); 

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannel;

	unsigned char *dataImage = stbi_load(file.c_str(), &width, &height, &nrChannel, 0);

	if (!dataImage) {
		std::cout << "your data hasnt been loaded!!!";
	}
	else
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,	width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, dataImage);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	std::cout << "nr channel: " << nrChannel << "\n";
	
	stbi_image_free(dataImage);
	// fix the erro
}