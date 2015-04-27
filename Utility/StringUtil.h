#ifndef STRING_H
#define STRING_H

#include <string>
#include <vector>

namespace Utility
{
	class String : public std::string
	{
	public:
		typedef std::vector<String> StringVec;

		String();
		String(const char* _string);
		String(std::string _string);

		StringVec Split(char _delimiter);
		static StringVec Split(const char* _string, char _delimiter);
	};
}

#endif