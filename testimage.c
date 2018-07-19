#include <stdio.h>

void square(FILE *fp, int xpos, int ypos, int w, int h, int c)
{
    int x, y;

    for(y = 0; y < h; y++) {
        for(x = 0; x < w; x++) {
            fprintf(fp, "%d %d %d pxpt\n",
                    x + xpos, y + ypos, c);
        }
    }
}

int main(int argc, char *argv[])
{
    FILE *fp;
    int x;

    fp = fopen("test.rnt", "w");

    fprintf(fp, "# generated image using testimage program\n");

    for(x = 0; x < 8; x++) {
        square(fp, x * 32, 0, 32, 32 * (x + 1), x % 8);
    }

    fprintf(fp, "\"out.png\" pxsave\n");
    fclose(fp);
    return 0;
}
