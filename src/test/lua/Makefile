all: lua.cpp
	g++ -fPIC -o lua lua.cpp ../../../build/lib/lua/liblua.a -lm -Wl,-E -ldl

clean:
	rm lua
