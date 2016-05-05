
#include <stdio.h>

int
main(void){

    int h = 0, f = 0;
    scanf("%d, %d", &h, &f);
    printf("%d, %d\n", h, f);

    int y = (f - 2 * h) / 2;
    int x = h - y;

    printf(" cock = %d, rabbit = %d\n", x, y);
    return 0;
}
