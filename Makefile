EXECUTABLE=fxp-sort.exe

CC="C:\MinGW\bin\gcc.exe"
LDFLAGS="-pedantic"

src=$(wildcard *.c)
obj=$(src:.c=.o)

all: default

default: $(obj)
	$(CC) -o $(EXECUTABLE) $^ $(LDFLAGS)
