#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

char* custom_getline() {
static char buffer[BUFFER_SIZE];
static ssize_t buffer_pos = 0;
static ssize_t buffer_size = 0;

/**
* Check if buffer is empty
* Read data into buffer
* Return NULL if read fails or reaches EOF
*/
if (buffer_pos >= buffer_size)
{

buffer_size = read(STDIN_FILENO, buffer, BUFFER_SIZE);


if (buffer_size <= 0) {
return NULL;
}
buffer_pos = 0;
}

ssize_t newline_pos = buffer_pos;
while (newline_pos < buffer_size && buffer[newline_pos] != '\n') {
newline_pos++;
}

ssize_t line_length = newline_pos - buffer_pos;

char* line = (char*) malloc((line_length + 1) * sizeof(char));

for (ssize_t i = 0; i < line_length; i++) {
line[i] = buffer[buffer_pos + i];
}
line[line_length] = '\0';  // Null-terminate the line

buffer_pos += line_length + 1;

return line;
}

int main() {
char* line;

while ((line = custom_getline()) != NULL) {
/**
* Process the line
* Free the allocated memory
*/
free(line);
}
return 0;
}

