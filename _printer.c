#include "main.h"

void PRINT(const char *message) {
	write(STDOUT_FILENO, message, strlen(message));
}
