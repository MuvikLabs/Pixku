#include <stdio.h>

#define GLYPH_WIDTH 5
#define GLYPH_HEIGHT 8

const char glyph_0[] = {
0, 0, 0, 0, 0,
0, 1, 1, 1, 0,
1, 0, 0, 0, 1,
1, 0, 0, 1, 1,
1, 0, 1, 0, 1,
1, 1, 0, 0, 1,
1, 0, 0, 0, 1,
0, 1, 1, 1, 0,
};

const char glyph_1[] = {
0, 0, 0, 0, 0,
0, 0, 1, 0, 0,
0, 1, 1, 0, 0,
0, 0, 1, 0, 0,
0, 0, 1, 0, 0,
0, 0, 1, 0, 0,
0, 0, 1, 0, 0,
0, 1, 1, 1, 0,
};

const char glyph_2[] = {
0, 0, 0, 0, 0,
0, 1, 1, 1, 0,
1, 0, 0, 0, 1,
0, 0, 0, 0, 1,
0, 0, 0, 1, 0,
0, 0, 1, 0, 0,
0, 1, 0, 0, 0,
1, 1, 1, 1, 1,
};

const char glyph_3[] = {
0, 0, 0, 0, 0,
1, 1, 1, 1, 1,
0, 0, 0, 1, 0,
0, 0, 1, 0, 0,
0, 0, 0, 1, 0,
0, 0, 0, 0, 1,
1, 0, 0, 0, 1,
0, 1, 1, 1, 0,
};

const char glyph_4[] = {
0, 0, 0, 0, 0,
0, 0, 0, 1, 0,
0, 0, 1, 1, 0,
0, 1, 0, 1, 0,
1, 0, 0, 1, 0,
1, 1, 1, 1, 1,
0, 0, 0, 1, 0,
0, 0, 0, 1, 0,
};

const char glyph_5[] = {
0, 0, 0, 0, 0,
1, 1, 1, 1, 1,
1, 0, 0, 0, 0,
1, 1, 1, 1, 0,
0, 0, 0, 0, 1,
0, 0, 0, 0, 1,
1, 0, 0, 0, 1,
0, 1, 1, 1, 0,
};

const char glyph_6[] = {
0, 0, 0, 0, 0,
0, 0, 1, 1, 0,
0, 1, 0, 0, 0,
1, 0, 0, 0, 0,
1, 1, 1, 1, 0,
1, 0, 0, 0, 1,
1, 0, 0, 0, 1,
0, 1, 1, 1, 0,
};

const char glyph_7[] = {
0, 0, 0, 0, 0,
1, 1, 1, 1, 1,
1, 0, 0, 0, 1,
0, 0, 0, 1, 0,
0, 0, 1, 0, 0,
0, 1, 0, 0, 0,
0, 1, 0, 0, 0,
0, 1, 0, 0, 0,
};

const char *glyphs[] = {
glyph_0, glyph_1, glyph_2, glyph_3, glyph_4, glyph_5, glyph_6, glyph_7
};

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

void glyph(FILE *fp, const char *g, int xpos, int ypos, int c)
{
    int x, y;
    int pos;

    pos = 0;
    for(y = 0; y < GLYPH_HEIGHT; y++) {
        for(x = 0; x < GLYPH_WIDTH; x++) {
            if(g[pos]) {
                fprintf(fp, "%d %d %d pxpt\n", xpos + x, ypos + y, c);
            }
            pos++;
        }
    }
}

int main(int argc, char *argv[])
{
    FILE *fp;
    int x;
    int xoff, yoff;

    fp = fopen("test.rnt", "w");

    fprintf(fp, "# generated image using testimage program\n");

    for(x = 0; x < 8; x++) {
        square(fp, x * 32, 0, 32, 32 * (x + 1), x % 8);
    }

    xoff = 16 - (GLYPH_WIDTH / 2);
    yoff = 4;
    for(x = 0; x < 8; x++) {
        glyph(fp, glyphs[x], xoff + x * 32, yoff, 7 - x);
    }
    fprintf(fp, "\"out.png\" pxsave\n");
    fclose(fp);
    return 0;
}
