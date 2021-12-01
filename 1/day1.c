#include <stdio.h>
#include <limits.h>

int main(int argc, char** argv) {
    int a = INT_MAX;
    int b = INT_MAX;
    int c = INT_MAX;
    int d = INT_MAX;
    int bigger = 0;
    FILE* fptr;
    
    if (argc < 2) {
        puts("need filepath");
        return 1;
    }
    fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        puts("invalid filename");
        return 1;
    }
    
    while(fscanf(fptr, "%d\n", &d) != EOF) {
        if(d > a) {
            bigger++;
        }
        a = b;
        b = c;
        c = d;
    }
    
    fclose(fptr);
    
    printf("%d bigger\n", bigger);
    return 0;
}
