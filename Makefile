all:
	@g++ -std=c++17 main.cpp -o play -I include -Lusr/lib/x86_64-linux-gnu/ -L/usr/local/Cellar/sdl2/2.0.20/lib/ -L/usr/local/Cellar/sdl2_image/2.0.5/lib/ -L/usr/local/Cellar/sdl2_ttf/2.0.18_1/lib/ -lSDL2 -lSDL2_image -lSDL2_ttf
	@# @g++ -std=c++17 main.cpp -o play -I include -Ldependencies/macos -Ldependencies/linux -lSDL2-2.0.0
clean:
	@rm play