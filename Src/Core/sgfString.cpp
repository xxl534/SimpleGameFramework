#include "sgfString.h"

//----------------------------------------
int sgfStrLen(const char * s)
{
	ASSERT(s);
	return strlen(s);
}

//----------------------------------------
int sgfStrLen(const wchar * s)
{
	ASSERT(s);
	size_t len = 0;
	while ((*s++) != '\0')
	{
		++len;
	}
	return len;
}

//----------------------------------------
int sgfStrLen(const unsigned int* s)
{

}
