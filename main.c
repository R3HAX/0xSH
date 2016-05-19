#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ncurses.h>
#include <fcntl.h>
#include <unistd.h>

#include "shell.c"
#include "builtin.c"
#include "lib/liberr.c"
#include "lib/net.c"

int ret = 0;

struct version {
    double v = 0.1;
    int rc = 0;
    char author[8] = "R3V0LT";
};

int check_ret ()
{
    if ( ret == 1 )
    {
        printf("\t [OK]\n");
	return 0;
    } else if ( ret != 1 )
    {
	printf("\t [ERROR]\n");
	return 1;
    }
}

int __LOG_RW (char buffer[800])
{
    open("~/.0xlog", O_CREAT);
    open("~/.0xlog", O_RDWR);

    write(buffer);

    if ( write(buffer) == 0 )
    {
	return 0;
    } else if ( write(buffer) == 1 )
    {
	ret = 1;
    }
    ret = 1; // This means that the operation has completeted successfully.
}

int __INIT__ __attribute__(noreturn)
{
    __LOG_RW("BEGIN:");
    check_ret();

    if ( check_ret == 1 )
    {
	printf("Warning! It is dangerous to continue, because it appears this program doesn't have the correct permissions available to write in a logfile. Please try to resolve the issue, and restart the program.\n");
	abort();
    } 
}

int main ( int argc, char *argv[] )
{
    __INIT__();
    shell();
    _LOG_RW("Process has completed!\n");
      
}
