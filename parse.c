#include <stdio.h>
#include "runt.h"
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
    if(y < 0 || y >= HEIGHT) return 0;
    if(clr < 0 || clr >= NCOLORS) return 0;

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

static runt_int rproc_pxpt(runt_vm *vm, runt_ptr p)
{
    runt_int rc;
    runt_int x;
    runt_int y;
    runt_int c;
    runt_stacklet *s;

    rc = runt_ppop(vm, &s);
    RUNT_ERROR_CHECK(rc);
    c = s->f;

    rc = runt_ppop(vm, &s);
    RUNT_ERROR_CHECK(rc);
    y = s->f;

    rc = runt_ppop(vm, &s);
    RUNT_ERROR_CHECK(rc);
    x = s->f;

    rc = pxpt(x, y, c);

    if(!rc) return RUNT_NOT_OK;

    return RUNT_OK;
}

static runt_int rproc_pxclr(runt_vm *vm, runt_ptr p)
{
    runt_int rc;
    runt_int r;
    runt_int g;
    runt_int b;
    runt_int c;
    runt_stacklet *s;

    rc = runt_ppop(vm, &s);
    RUNT_ERROR_CHECK(rc);
    b = s->f;

    rc = runt_ppop(vm, &s);
    RUNT_ERROR_CHECK(rc);
    g = s->f;

    rc = runt_ppop(vm, &s);
    RUNT_ERROR_CHECK(rc);
    r = s->f;

    rc = runt_ppop(vm, &s);
    RUNT_ERROR_CHECK(rc);
    c = s->f;

    rc = set_color(c, r, g, b);

    if(!rc) return RUNT_NOT_OK;
    return RUNT_OK;
}

static runt_int rproc_pxsave(runt_vm *vm, runt_ptr p)
{
    const char *filename;
    runt_int rc;
    runt_stacklet *s;

    rc = runt_ppop(vm, &s);
    RUNT_ERROR_CHECK(rc);
    filename = runt_to_string(s->p);

    pxsave(filename);
    return RUNT_OK;
}

static void load_pixku(runt_vm *vm)
{
    default_palette();
    zero_out_buffers();
    runt_keyword_define(vm, "pxpt", 4, rproc_pxpt, NULL);
    runt_keyword_define(vm, "pxclr", 5, rproc_pxclr, NULL);
    runt_keyword_define(vm, "pxsave", 6, rproc_pxsave, NULL);
}

static runt_int loader(runt_vm *vm)
{
    runt_load_stdlib(vm);
    load_pixku(vm);
    return runt_is_alive(vm);
}

int main(int argc, char *argv[])
{
    return irunt_begin(argc, argv, loader);
}
