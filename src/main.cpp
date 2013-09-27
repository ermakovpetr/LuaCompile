#include "cocor/Parser.h"
#include "cocor/Scanner.h"
#include <sys/timeb.h>
#include <wchar.h>

using namespace Lua;

int main (int argc, char *argv[]) {
	printf("\x1b[1;4;5;31;43m  Start LuaCompiler >\x1b[0m\n");

	if (argv[1] != "") {
		//wchar_t *fileName = coco_string_create(argv[1]);
		wchar_t *fileName = coco_string_create("/home/petr/Dropbox/Project/LuaCompiler/LuaCompiler/doc/lua/test_example/sort.lua");
		Lua::Scanner *scanner = new Lua::Scanner(fileName);
		Lua::Parser *parser = new Lua::Parser(scanner);
		parser->Parse();
		coco_string_delete(fileName);
		delete parser;
		delete scanner;
	} else
		printf("\x1b[1;4;5;31mNo source file specified\x1b[0m\n");

	printf("\x1b[1;4;5;31;43m< Stop  LuaCompiler  \x1b[0m\n");
	return 0;

}
