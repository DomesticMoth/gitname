#include <stdio.h>
#include "lb.c"

int main( int argc, char *argv[] ){
    if (argc < 2) {
         printf("Too few args\n");
         return 0;
    }
    struct Info info = get(argv[1]);
    if (info.username == NULL || info.email == NULL) {
        printf("Cannot find '%s' gitname\n", argv[1]);
        return 0;
    }
    set(&info);
    return 0;
}  
