#include "StringUtil.h"

namespace Utility
{
	String::String() : std::string(){}
	String::String(const char* _string) : std::string(_string){}
	String::String(std::string _string) : std::string(_string){}

	std::vector<String> String::Split(char _delimiter)
	{
		size_t pos = 0;
		std::vector<String> strVec;

		if(size() > 0)
		{
			do
			{
				pos = find(_delimiter);
				if(substr(0, pos).size() > 0)
				{
					strVec.push_back(substr(0, pos));
				}
				erase(0, pos + sizeof(_delimiter));
			}while(pos != String::npos);
		}

		return strVec;
	}
}