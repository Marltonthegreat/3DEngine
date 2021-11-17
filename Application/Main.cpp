//#include "Engine.h"

#include <glad\glad.h>
#include <SDL.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <iostream>

// vertices
const float vertices[] =
{
	-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
	 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
	 0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
	-0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f
};

const GLuint indices[] =
{
	0, 2, 1,
	0, 3, 2
};

// vertex shader
const char* vertexSource = R"(
    #version 430 core 
    layout(location = 0) in vec3 position;
	layout(location = 1) in vec3 color;

	out vec3 fs_color;
	
	uniform float scale;

    void main()
    {
		fs_color = color;
        gl_Position = vec4(position * scale, 1.0);
    }
)";



// fragment
const char* fragmentSource = R"(
    #version 430 core
	in vec3 fs_color;
	out vec4 outColor;

	uniform vec3 tint;

    void main()
    {
        outColor = vec4(fs_color * tint, 1.0);
    }
)";

int main(int argc, char** argv)
{
	//glds::Engine engine;
	//engine.Startup();
	//engine.Get<glds::Renderer>()->Create("OpenGL", 800, 600);

	//glds::SeedRandom(static_cast<unsigned int>(time(nullptr)));
	//glds::SetFilePath("../resources");

	// Set Vertex Shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	GLint status;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		char buffer[512];
		glGetShaderInfoLog(vertexShader, 512, NULL, buffer);
		std::cout << buffer;
	}

	// Set Fragment Shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		char buffer[512];
		glGetShaderInfoLog(fragmentShader, 512, NULL, buffer);
		std::cout << buffer;
	}

	// Create Shader Program
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glLinkProgram(shaderProgram);
	
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		char buffer[512];
		glGetShaderInfoLog(shaderProgram, 512, NULL, buffer);
		std::cout << buffer;
	} 

	glUseProgram(shaderProgram);

	// vertex array
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// create vertex buffer
	GLuint vbo;
	glGenBuffers(1, &vbo);

	// bind vertex buffer as active buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	// set vertex data into vertex buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	GLuint ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);



	// position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	// color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// uniform
	GLuint scaleLocation = glGetUniformLocation(shaderProgram, "scale");
	float time = 0;

	GLuint tintLocation = glGetUniformLocation(shaderProgram, "tint");
	glm::vec3 tint{ 0.25f, 0.25f, 1.0f };

	bool quit = false;
	while (!quit)
	{
		SDL_Event event;
		SDL_PollEvent(&event);

		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				quit = true;
			}
		}

		SDL_PumpEvents();

		time += 0.01f;
		glUniform1f(scaleLocation, std::sin(time));
		glUniform3fv(tintLocation, 1, &tint[0]);

		glClearColor(0.0f, 0.0f, 0.00f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//engine.Get<glds::Renderer>()->BeginFrame();

		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		//engine.Get<glds::Renderer>()->EndFrame();
	}

	return 0;
}