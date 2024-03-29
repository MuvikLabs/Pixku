OBJ+=lodepng/lodepng.o
CFLAGS += -Ilodepng -std=c89 -Wall -pedantic
OBJ+=main.o

LUA_PATH=lua
LUA_CORE_O=	lapi.o lcode.o lctype.o ldebug.o ldo.o ldump.o lfunc.o lgc.o llex.o \
	lmem.o lobject.o lopcodes.o lparser.o lstate.o lstring.o ltable.o \
	ltm.o lundump.o lvm.o lzio.o
LUA_LIB_O=	lauxlib.o lbaselib.o lbitlib.o lcorolib.o ldblib.o liolib.o \
	lmathlib.o loslib.o lstrlib.o ltablib.o lutf8lib.o loadlib.o linit.o
LUA_BASE_O= $(LUA_CORE_O) $(LUA_LIB_O) lua.o

CFLAGS+=-DLUA_USE_C89 -DLUA_COMPAT_5_2
CFLAGS+=-I$(LUA_PATH)

OBJ += $(addprefix $(LUA_PATH)/, $(LUA_BASE_O))

default: pixku testimage

pixku: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

clean:
	$(RM) pixku $(OBJ) testimage
