all:
	g++ -o kmeans main.cpp kmeans.cpp kmeans.h kimages.cpp kimages.h -O1 -lpthread -lX11
clean:
	rm kmeans
