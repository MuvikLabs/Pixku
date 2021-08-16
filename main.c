#include <stdio.h>
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "lodepng.h"

#define WIDTH 256
#define HEIGHT 256
#define NCOLORS 8

typedef struct {
    unsigned char r, g, b, a;
} color;

static unsigned char buf[WIDTH*HEIGHT];
static color pal[NCOLORS];
static color imgdata[WIDTH*HEIGHT];

static int set_color(int p, unsigned char r, unsigned char g, unsigned char b)
{
    if(p < 0 || p >= NCOLORS) return 0;
    pal[p].r = r;
    pal[p].g = g;
    pal[p].b = b;
    pal[p].a = 255;
    return 1;
}

static void default_palette(void)
{
    /*
     * These colors were sourced from:
     * https://lospec.com/palette-list/dawnbringers-8-color
     */

    set_color(0, 0x00, 0x00, 0x00);
    set_color(1, 0x55, 0x41, 0x5f);
    set_color(2, 0x64, 0x69, 0x64);
    set_color(3, 0xd7, 0x73, 0x55);
    set_color(4, 0x50, 0x8c, 0xd7);
    set_color(5, 0x64, 0xb9, 0x64);
    set_color(6, 0xe6, 0xc8, 0x6e);
    set_color(7, 0xdc, 0xf5, 0xff);
}

static int pxpt(int x, int y, int clr)
{
    if(x < 0 || x >= WIDTH) return 0;
    if(y < 0 || y >= HEIGHT) return -1;
    if(clr < 0 || clr >= NCOLORS) return -2;

    buf[y * WIDTH + x] = clr;
    return 1;
}

static void zero_out_buffers(void)
{
    int x, y;
    for(y = 0; y < HEIGHT; y++) {
        for(x = 0; x < WIDTH; x++) {
            buf[y * WIDTH + x] = 0;
        }
    }
}

int pxsave(const char *filename)
{
    int x, y, pos;

    pos = 0;
    for(y = 0; y < HEIGHT; y++) {
        for(x = 0; x < WIDTH; x++) {
            imgdata[pos] = pal[buf[pos]];
            pos++;
        }
    }
    lodepng_encode32_file(filename, (unsigned char *)imgdata, WIDTH, HEIGHT);
    return 1;
}

/* pxpt(x, y, c) */

static int l_pxpt(lua_State *L)
{
    int x;
    int y;
    int c;
    int rc;

    x = luaL_checkinteger(L, 1);
    y = luaL_checkinteger(L, 2);
    c = luaL_checkinteger(L, 3);
    rc = pxpt(x, y, c);

    if(rc <= 0) {
        switch(rc) {
            case 0:
                luaL_error(L, "x value %d out of range\n", x);
                break;
            case -1:
                luaL_error(L, "y value %d out of range\n", y);
                break;
            case -2:
                luaL_error(L, "color value %d out of range\n", c);
                break;
        }
    }

    return 0;
}

/* pxclr(c, r, g, b) */

static int l_pxclr(lua_State *L)
{
    int r;
    int g;
    int b;
    int c;
    int rc;

    c = luaL_checkinteger(L, 1);
    r = luaL_checkinteger(L, 2);
    g = luaL_checkinteger(L, 3);
    b = luaL_checkinteger(L, 4);

    rc = set_color(c, r, g, b);


    if (rc <= 0) luaL_error(L, "Problem with pixclr");
    return 0;
}

/* pxsave(filename) */
static int l_pxsave(lua_State *L)
{
    const char *filename;

    filename = luaL_checkstring(L, 1);
    pxsave(filename);
    return 0;
}

static const luaL_Reg pixkulib[] = {
    {"pt", l_pxpt},
    {"clr", l_pxclr},
    {"save", l_pxsave},
    {NULL, NULL}
};

int sglua_main(int argc, char **argv, void (*loader)(lua_State*));

static int open_pixku(lua_State *L)
{
    luaL_newlib(L, pixkulib);
    return 1;
}

static void pixku_loader(lua_State *L)
{
    default_palette();
    zero_out_buffers();
    luaL_requiref(L, "pixku", open_pixku, 1);
}

int main(int argc, char *argv[])
{
    return sglua_main(argc, argv, pixku_loader);
}
