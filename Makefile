all:
	g++ src/cocor/*.cpp src/*.cpp -o Lua $(CFLAGS)

clean:
	rm -f Lua

