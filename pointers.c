#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tmpS{
    char *string;
} ;

void getIt(struct tmpS* S) {
    int i, size;

    size = 10;
    S->string = (char *) malloc(size*sizeof(char));
    S->string = strdup("aaaaaaaaa\0");
}


int main (int argc, char **argv) {
    struct tmpS *S;

    S = (struct tmpS*) malloc(sizeof(struct tmpS));
    getIt(S);

    printf ("   %s\n", S->string);
    free(S);
    printf ("   %s\n", S->string);
    return 1;
}
