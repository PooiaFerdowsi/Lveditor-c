#include "input.h"

#include <unistd.h>
#include <errno.h>

#include "glob.h"

char read_key() 
{
    int nread;
    char c;
    while ((nread = read(STDIN_FILENO, &c, 1)) != 1) {
        if (nread == -1 && errno != EAGAIN) 
            die("read");
    }
    return c;
}
