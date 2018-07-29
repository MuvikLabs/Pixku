# Pixku

![Pixku](pixku.png)

An 8 color environment for pixel art generation, built on top of Runt.

## Compilation

First run `git submodule init` and `git submodule update` to get the Runt
submodule.

Next, compile all programs with `make`. This will make the pixku binary.

To test if things are running okay, run `./pixku test.rnt`. This should produce
a file called "out.png" which should be identical to the image "pixku.png".

## Usage

Pixku is controlled via [Runt](https://www.github.com/MuvikLabs/runt),
which is a [stack-based language](http://wiki.c2.com/?StackBasedLanguage).

Pixku has special words defined.

The word `pxpt` will draw a pixel point at a given XY location with a specified
palette color. The command `1 2 3 pxpt` will draw a pixel at location (1, 2)
with color number 3. The default colors and their numeric values can be seen in
the test image "pixku.png".

The word `pxclr` will set the particular color in the color palette.
The command `0 255 128 64 pxclr` will set color 0 to be the RGB color
(255, 128, 64).

The word `pxsave` will save the contents to a PNG file. The command
`"out.png" pxsave` will write to a file called "out.png".

## Examples

The best way to interact with Pixku is to write programs that write Pixku
programs. [A small program in C](testimage.c) was used to generate the
test program which generates the example image included in this repository.