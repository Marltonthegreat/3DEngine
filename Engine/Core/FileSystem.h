#pragma once
#include <string>

namespace glds
{
	bool ReadFileToString(const std::string& filename, std::string& filestring);

	void SetFilePath(const std::string& pathName);
	std::string GetFilePath();
}