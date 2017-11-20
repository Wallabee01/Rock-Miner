#pragma once
#include <vector>

namespace SPH {

	class IOManager // static class, one 1 instance so no constructor/destructor
	{
	public:
		static bool readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer);
		static bool readFileToBuffer(std::string filePath, std::string& buffer);
	};

}