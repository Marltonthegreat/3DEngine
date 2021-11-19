#include "FileSystem.h"

#include <SDL.h>

#include <filesystem>
#include <fstream>
#include <sstream>

namespace glds
{
	bool ReadFileToString(const std::string& filename, std::string& filestring)
	{
		std::ifstream fileStream(filename, std::ios::in);
		if (!fileStream.is_open())
		{
			SDL_Log("Error: Failed to open file: %s", filename.c_str());
			return false;
		}

		std::stringstream stream;
		stream << fileStream.rdbuf();
		filestring = stream.str();

		fileStream.close();

		return true;
	}

	void SetFilePath(const std::string& pathName)
	{
		std::filesystem::current_path(pathName);
	}

	std::string GetFilePath()
	{
		return std::filesystem::current_path().string();
	}
}
