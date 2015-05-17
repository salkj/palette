all:
	g++ -o kmeans main.cpp kmeans.cpp kmeans.h kimages.cpp kimages.h -O3 -lpthread -lX11
clean:
	RM kmeans
