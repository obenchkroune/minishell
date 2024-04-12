#include <unistd.h>
int main(void)
{
	char *argv[] = {
		"echo",
		"\"Hello world\"",
		0
	};
	execve("/usr/bin/echo", argv, 0);
}
