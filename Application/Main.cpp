#include "Engine.h"

int main(int argc, char** argv)
{
	// create engine
	std::unique_ptr<glds::Engine> engine = std::make_unique<glds::Engine>();
	engine->Startup();
	engine->Get<glds::Renderer>()->Create("OpenGL", 800, 600);

	// create scene
	std::unique_ptr<glds::Scene> scene = std::make_unique<glds::Scene>();
	scene->engine = engine.get();

	glds::SeedRandom(static_cast<unsigned int>(time(nullptr)));
	glds::SetFilePath("../resources");

	// load scene
	rapidjson::Document document;
	bool success = glds::json::Load("scenes/main.scn", document);
	scene->Read(document);
		
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
		engine->Update();
		scene->Update(engine->time.deltaTime);

		// update actor
		auto actor = scene->FindActor("light");
		if (actor != nullptr)
		{
			glm::mat3 rotation = glm::rotate(engine->time.deltaTime, glm::vec3{ 0, 0, 1 });
			actor->transform.position = actor->transform.position * rotation;
		}

		engine->Get<glds::Renderer>()->BeginFrame();

		scene->Draw(nullptr);

		engine->Get<glds::Renderer>()->EndFrame();
	}

	return 0;
}
