#include <stdio.h>

char *strcpy_(char *dest, const char *src)
{
	char *p = dest;

	while((*p++ = *src++) != '\0');

	return dest;
}

size_t strlen_(const char *s)
{
	const char *p = s;

	while(*s++ != '\0');

	return (s - p - 1);
}

char *strcat_(char *dest, const char *src)
{
	char *p = dest;

	for(; *p != '\0'; p++);

	while((*p++ = *src++) != '\0');
	
	return dest;
}

int strcmp_(const char *s1, const char *s2)
{
	for(;*s1 != '\0' && *s2 != '\0' && *s1 == *s2; s1++,s2++);

	return (*s1 - *s2);
}

char *strchr_(const char *s, int c)
{
#if 1
	while(*s != '\0')
	{
		if(*s == (char)c)
			return (char *)s;
		s++;
	}
	return NULL;
#else
	for(;*s != '\0' && *s != (char)c; s++);
	
	if(*s == '\0')
		return NULL;
	return (char *)s;
#endif
}

char *strstr_(const char *haystack, const char *needle)
{
	const char *p;
	const char *q;

	while(*haystack != '\0')
	{
		p = haystack;
		q = needle;

		for(; *q != '\0' && *p == *q; p++, q++);
		
		if(*q == '\0')
			return (char *)haystack;

		haystack++;
	}
	return NULL;
}













