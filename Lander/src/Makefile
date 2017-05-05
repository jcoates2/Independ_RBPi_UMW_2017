CFLAGS+=-O3 -march=armv6 -mfpu=vfp -mfloat-abi=hard -Wall

all:
	g++ -std=c++11 -lsigil -lGLESv2 -I/usr/local/include -L/opt/vc/lib -R/opt/vc/lib main.cpp game_object.cpp game_object.h level.cpp level.h -o Lander.out
library:
	LD_LIBRARY_PATH=/opt/vc/lib
	export LD_LIBRARY_PATH
clean:
	-rm *.out
