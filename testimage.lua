glyph_0 = {
0, 0, 0, 0, 0,
0, 1, 1, 1, 0,
1, 0, 0, 0, 1,
1, 0, 0, 1, 1,
1, 0, 1, 0, 1,
1, 1, 0, 0, 1,
1, 0, 0, 0, 1,
0, 1, 1, 1, 0,
}

glyph_1 = {
0, 0, 0, 0, 0,
0, 0, 1, 0, 0,
0, 1, 1, 0, 0,
0, 0, 1, 0, 0,
0, 0, 1, 0, 0,
0, 0, 1, 0, 0,
0, 0, 1, 0, 0,
0, 1, 1, 1, 0,
}

glyph_2 = {
0, 0, 0, 0, 0,
0, 1, 1, 1, 0,
1, 0, 0, 0, 1,
0, 0, 0, 0, 1,
0, 0, 0, 1, 0,
0, 0, 1, 0, 0,
0, 1, 0, 0, 0,
1, 1, 1, 1, 1,
}

glyph_3 = {
0, 0, 0, 0, 0,
1, 1, 1, 1, 1,
0, 0, 0, 1, 0,
0, 0, 1, 0, 0,
0, 0, 0, 1, 0,
0, 0, 0, 0, 1,
1, 0, 0, 0, 1,
0, 1, 1, 1, 0,
}

glyph_4 = {
0, 0, 0, 0, 0,
0, 0, 0, 1, 0,
0, 0, 1, 1, 0,
0, 1, 0, 1, 0,
1, 0, 0, 1, 0,
1, 1, 1, 1, 1,
0, 0, 0, 1, 0,
0, 0, 0, 1, 0,
}

glyph_5 = {
0, 0, 0, 0, 0,
1, 1, 1, 1, 1,
1, 0, 0, 0, 0,
1, 1, 1, 1, 0,
0, 0, 0, 0, 1,
0, 0, 0, 0, 1,
1, 0, 0, 0, 1,
0, 1, 1, 1, 0,
};

glyph_6 = {
0, 0, 0, 0, 0,
0, 0, 1, 1, 0,
0, 1, 0, 0, 0,
1, 0, 0, 0, 0,
1, 1, 1, 1, 0,
1, 0, 0, 0, 1,
1, 0, 0, 0, 1,
0, 1, 1, 1, 0,
}

glyph_7 = {
0, 0, 0, 0, 0,
1, 1, 1, 1, 1,
1, 0, 0, 0, 1,
0, 0, 0, 1, 0,
0, 0, 1, 0, 0,
0, 1, 0, 0, 0,
0, 1, 0, 0, 0,
0, 1, 0, 0, 0,
};

glyph_table = {
    glyph_0, glyph_1, glyph_2, glyph_3, glyph_4, glyph_5, glyph_6, glyph_7
}

function square(xpos, ypos, w, h, c)
    for y = 0, h-1 do
        for x = 0, w-1 do
            pixku.pt(x + xpos, y + ypos, c)
        end
    end
end
glyph_width = 5
glyph_height = 8

function glyph(g, xpos, ypos, c)
    local pos = 1
    for y = 0, glyph_height - 1 do
        for x = 0, glyph_width - 1 do
            if (g[pos] == 1) then
                pixku.pt(xpos + x, ypos + y, c)
            end
            pos = pos + 1
        end
    end
end

for x=0,7 do
    square(x * 32, 0, 32, 32 * (x + 1), x % 8)
end

local xoff = 16 - (glyph_width - 2)
local yoff = 4

g = glyph_table[1]

for x=0,7 do
    glyph(glyph_table[x + 1], xoff + x*32, yoff, 7 - x)
end

pixku.save("out.png")