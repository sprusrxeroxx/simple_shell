#include "shell.h"

/**
 * _strlen - returns the length of a string
 * @str: the string whose length to check
 *
 * Return: integer length of string
 */
int _strlen(char *str)
{
	int length = 0;

	if (!str)
	return (0);

	while (*str++)
	length++;	
	return (length);
}

/**
 * _strcmp - performs lexicogarphic comparison of two strangs.
 * @str1: the first strang
 * @str2: the second strang
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int _strcmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
	if (*str1 != *str2)
	return (*str1 - *str2);
	str1++;
	str2++;
	}
	if (*str1 == *str2)
	return (0);
	else
	return (*str1 < *str2 ? -1 : 1);
}

/**
 * starts_with_ - checks if needle starts with haystack
 * @str: string to search
 * @substr: the substring to find
 *
 * Return: address of next char of substring or NULL
 */
char *starts_with(const char *str, const char *substr)
{
	while (*substr)
		if (*substr++ != *str++)
			return (NULL);
	return ((char*) str);
}
/**
 * join_strings - concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *_strcat(char *dest, char *src)
{
    char *result = dest;

    while (*dest)
        dest++;
    while (*src)
        *dest++ = *src++;
    *dest = *src;
    return (result);
}

