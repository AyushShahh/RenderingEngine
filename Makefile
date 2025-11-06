%:
	g++ -I src/include -L src/lib -o $@ $@.cpp renderer.cpp -lmingw32 -lSDL2main -lSDL2