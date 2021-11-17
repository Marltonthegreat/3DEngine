#pragma once
#include <string>

namespace glds
{
	std::string string_toLower(const std::string& str);
	bool istring_compare(const std::string& str1, const std::string& str2);
	std::string unique_string(const std::string& str);

	bool IsButtonPressed(int id, class Engine* engine);
	bool IsButtonHeld(int id, class Engine* engine);
	bool IsButtonPressHold(int id, class Engine* engine);
}