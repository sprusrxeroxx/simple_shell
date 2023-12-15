#include "main.h"

/**
 * main - function to check for shell call
 *
 * Return: 0 or nothing
 */

int main(void)
{
	if (isatty(STDIN_FILENO) == 1)
	interactive_mode();
	else
	{
		interactive_mode();
	}
	return (0);
}
