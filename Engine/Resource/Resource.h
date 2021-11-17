#pragma once
#include <string>

class Resource
{
public:
	virtual bool Load(const std::string& filename, void* data) = 0;
};