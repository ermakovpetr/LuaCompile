clear
echo "\x1b[1;31mstart compiling\x1b[0m\n"
make
echo "\x1b[1;31mfinish compiling\x1b[0m\n"
./Lua doc/lua/test_example/sort.lua
