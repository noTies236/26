#include "./render.h"
#include "../window/window.h"
#include "../pipeline/pipeline.h"

bool isRunning = true;
SDL_Event event;

float x_Axis = 0.0;
float y_Axis = 0.0;


void matrixM();
void matrixM()
{
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

	int modelLoc = glGetUniformLocation(worldObject::Pragram::square, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	int viewLoc = glGetUniformLocation(worldObject::Pragram::square, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	int projectionLoc = glGetUniformLocation(worldObject::Pragram::square, "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
}

void render::mainLoop()
{
	windowAplication::setupSdl();

	// vertex			color				coordd
	std::vector<float> Data {
		0.7,  0.0, 0.0,     0.3, 0.0, 0.0,     1.0f, 7.0f,
		-0.5, 0.0, 0.0,		0.0, 0.3, 0.0,     0.0f, 0.0f,
		0.0,  0.3, 0.0,		0.0, 1.0, 0.5,     1.0f, 0.0f,
	};

	std::vector<float> squareData { 
		// pos              normal          uv
		-0.5f,-0.5f,0.0f,     0.0, 0.4, 1.0,          1,0,
		 0.5f,-0.5f,0.0f,     0.3, 0.0, 1.0,          0,0,
		 0.5f, 0.5f,0.0f,     0.3, 0.0, 1.0,         1,1,
		-0.5f, 0.5f,0.0f,     0.3, 0.0, 1.0,          0,11,
	};

	/*worldObject::VAO::TestSruct test;
	test.strideOS = 6;
	test.ptr = 0;*/

	/*worldObject::VAO::SquareSruct saquare;
	saquare.strideOS = 8;
	saquare.ptr = 0;*/

	Layout Triangle;
	Triangle.strideOS = 6;
	Triangle.ptr = 0;
	Triangle.strindeTexBegning = 6;

	Layout Square;
	Square.strideOS = 8;
	Square.ptr = 0;

	int squareIndices[] = {
		0,1,2,
		2,3, 0
	};

	int indices[] = {
		0, 1, 2
	};

	pipeline::defineVertex(Data, worldObject::VAO::triangle, Triangle, indices);
	pipeline::loadTexture("C:/Users/wallyson/Downloads/awesomeface.png", GlobalTexture::smileFace);
	worldObject::Pragram::triangle = pipeline::createGraphicProgram(1);

	pipeline::defineVertex(squareData, worldObject::VAO::square, Square, squareIndices);
	worldObject::Pragram::square = pipeline::createGraphicProgram(0);
	
	while (isRunning) {
		render::obj();

		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_EVENT_QUIT) {
				isRunning = false;
			}
			
			GLuint u_X_axis = glGetUniformLocation(worldObject::Pragram::square, "uX");
			GLuint u_Y_axis = glGetUniformLocation(worldObject::Pragram::square, "uY");

			if (x_Axis > 0.9) {
				x_Axis = 0.9;
			}

			if (y_Axis > 0.9) {
				y_Axis = 0.9;
			}

			if (x_Axis < -1.0) {
				x_Axis = 0.1;
			}

			if (y_Axis < -1.0) {
				y_Axis = 0.1;
			}

			if (event.type == SDL_EVENT_KEY_DOWN) {
				if (event.key.key == SDLK_S) {
					glUseProgram(worldObject::Pragram::square);
					y_Axis -= 0.1;
					glUniform1f(u_Y_axis, y_Axis);
					std::cout << "S u_X_axis+ " << y_Axis << "\n";
				}

				if (event.key.key == SDLK_W) {
					glUseProgram(worldObject::Pragram::square);
					y_Axis += 0.1;
					glUniform1f(u_Y_axis, y_Axis);
					std::cout << "W u_X_axis+ " << y_Axis << "\n";
				}

				if (event.key.key == SDLK_A) {
					glUseProgram(worldObject::Pragram::square);
					x_Axis -= 0.1;
					glUniform1f(u_X_axis, x_Axis);
					std::cout << "A u_X_axis+ "<< x_Axis << "\n";
				}

				if (event.key.key == SDLK_D) {
					glUseProgram(worldObject::Pragram::square);
					x_Axis += 0.1f;
					glUniform1f(u_X_axis, x_Axis);
					std::cout << "D u_X_axis+ " << x_Axis << "\n";
				}

				if (event.key.key == SDLK_L) {
					glUseProgram(worldObject::Pragram::triangle);

					float triangleLoc = glGetUniformLocation(worldObject::Pragram::triangle, "xxx");

					x_Axis -= 0.1f;
					glUniform1f(triangleLoc, x_Axis);
					std::cout << "test triangle" << x_Axis << "\n";
				}
			}
		
			if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
				std::cout << "mouse";
				//pipeline::FBO();
			}
		}

		SDL_GL_SwapWindow(windowAplication::window);
	}
}

void render::obj()
{
	// pre draw
	glClearColor(0.0f, 0.4f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

	// draw 1
	glBindVertexArray(worldObject::VAO::square);
	glUseProgram(worldObject::Pragram::square); 
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	matrixM();
	// draw 2

	glBindVertexArray(worldObject::VAO::triangle);
	glUseProgram(worldObject::Pragram::triangle);

	glUniform1i(glGetUniformLocation(worldObject::Pragram::triangle, "xxx"), 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	// fix 
	// why my texture is being loaded on my square and triangle?
}