#ifndef STRING_H
#define STRING_H

#include <string>
#include <vector>

namespace Utility
{
	class String : public std::string
	{
	public:
		String();
		String(const char* _string);
		String(std::string _string);

		std::vector<String> Split(char _delimiter);
	};
}

#endif