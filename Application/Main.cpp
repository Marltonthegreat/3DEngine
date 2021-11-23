#include "Engine.h"

#include <glad/glad.h>
#include <SDL.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <iostream>

// vertices
const float vertices[] =
{
	// front
	-1.0f, -1.0f,  1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	 1.0f, -1.0f,  1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	 1.0f,  1.0f,  1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
	-1.0f,  1.0f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
	// back
	-1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	 1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
	 1.0f,  1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
	-1.0f,  1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f
};

const GLuint indices[] =
{
	// front
	0, 1, 2,
	2, 3, 0,
	// right
	1, 5, 6,
	6, 2, 1,
	// back
	7, 6, 5,
	5, 4, 7,
	// left
	4, 0, 3,
	3, 7, 4,
	// bottom
	4, 5, 1,
	1, 0, 4,
	// top
	3, 2, 6,
	6, 7, 3
};

int main(int argc, char** argv)
{
	glds::Engine engine;
	engine.Startup();
	engine.Get<glds::Renderer>()->Create("OpenGL", 800, 600);

	glds::SeedRandom(static_cast<unsigned int>(time(nullptr)));
	glds::SetFilePath("../resources");

	std::shared_ptr<glds::Program> program = engine.Get<glds::ResourceSystem>()->Get<glds::Program>("basic_program");
	std::shared_ptr<glds::Shader> vshader = engine.Get<glds::ResourceSystem>()->Get<glds::Shader>("shaders/basic.vert", (void*)GL_VERTEX_SHADER);
	std::shared_ptr<glds::Shader> fshader = engine.Get<glds::ResourceSystem>()->Get<glds::Shader>("shaders/basic.frag", (void*)GL_FRAGMENT_SHADER);

	program->AddShader(vshader);
	program->AddShader(fshader);
	program->Link();
	program->Use();

	// texture
	glds::Texture texture;
	texture.CreateTexture("textures/llama.jpg");
	texture.Bind();

	std::shared_ptr<glds::VertexIndexBuffer> vertexBuffer = engine.Get<glds::ResourceSystem>()->Get<glds::VertexIndexBuffer>("vertex_index_buffer");
	vertexBuffer->CreateVertexBuffer(sizeof(vertices), 8, (void*)vertices);
	vertexBuffer->CreateIndexBuffer(GL_UNSIGNED_INT, 36, (void*)indices);
	vertexBuffer->SetAttribute(0, 3, 8 * sizeof(float), 0);
	vertexBuffer->SetAttribute(1, 3, 8 * sizeof(float), 3 * sizeof(float));
	vertexBuffer->SetAttribute(2, 2, 8 * sizeof(float), 6 * sizeof(float));

	// matrix uniform
	glm::mat4 view = glm::lookAt(glm::vec3{ 0, 0, 2 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 });
	program->SetUniform("view", view);

	glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
	program->SetUniform("projection", projection);

	glm::vec3 translate{ 0 };
	float angle = 0;
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
		engine.Update();

		if (engine.Get<glds::InputSystem>()->GetKeyState(SDL_SCANCODE_A) == glds::InputSystem::eKeyState::Held)
		{
			translate.x -= 1 * engine.time.deltaTime;
		}
		if (engine.Get<glds::InputSystem>()->GetKeyState(SDL_SCANCODE_D) == glds::InputSystem::eKeyState::Held)
		{
			translate.x += 1 * engine.time.deltaTime;
		}
		if (engine.Get<glds::InputSystem>()->GetKeyState(SDL_SCANCODE_W) == glds::InputSystem::eKeyState::Held)
		{
			translate.y += 1 * engine.time.deltaTime;
		}
		if (engine.Get<glds::InputSystem>()->GetKeyState(SDL_SCANCODE_S) == glds::InputSystem::eKeyState::Held)
		{
			translate.y -= 1 * engine.time.deltaTime;
		}
		angle += engine.time.deltaTime;

		glm::mat4 model{ 1.0f };
		model = glm::translate(model, translate);
		model = glm::rotate(model, angle, glm::vec3{ 0, 1, 0 });
		model = glm::scale(model, glm::vec3{ 0.25f });
		program->SetUniform("model", model);

		engine.Get<glds::Renderer>()->BeginFrame();

		vertexBuffer->Draw(GL_TRIANGLES);

		engine.Get<glds::Renderer>()->EndFrame();
	}
	return 0;
}