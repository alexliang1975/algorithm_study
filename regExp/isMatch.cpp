/*
 * isMatch.cpp
 *
 */
#include <stdio.h>


bool isMatch(const char *s, const char *p)
{
	   if (s == NULL || p == NULL) return false;
	   if (*s == '\0' && *p == '\0') return true;
	   if (*s == '\0' && *(p) == '*')
		  return  isMatch(s, p+1);  // to deal with isMatch("", "*")
	   if (*p == '\0'  || *s=='\0' ) return false;

	   // *p and *s are not '\0'
	   if (*p == '.'){
		 return isMatch(s+1, p+1);
	   }

	   if (*(p) == '*'){
		   return isMatch(s, p+1)||isMatch(s+1, p)  ;
	   }

	   if (*s != *p) return false;

	   return isMatch(s+1, p+1);
}

