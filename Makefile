all:
	@g++ -std=c++17 main.cpp -o play -I include -L -l
clean:
	@rm play