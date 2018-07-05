all:movie_recommender

movie_recommender: src/movie_recommender.c distances.o preferences.o
	gcc -Iinclude -o movie_recommender ./src/movie_recommender.c distances.o preferences.o

distances.o: src/distances.c include/distances.h
	gcc -Iinclude -c src/distances.c

preferences.o: ./src/preferences.c ./include/preferences.h
	gcc -Iinclude -c src/preferences.c

clean: 
	rm movie_recommender distances.o preferences.o

