all:Anime.cpp
	g++ Anime.cpp -std=c++11 -o anime `pkg-config opencv --cflags --libs`
	./anime
