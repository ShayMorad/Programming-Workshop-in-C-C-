.PHONY: tweets, snake

FLAGS = -Wall -Wextra -Wvla -std=c99
CC = gcc


tweets: tweets_generator.o markov_chain.o linked_list.o
	$(CC) $^ -o tweets_generator

snake: snakes_and_ladders.o markov_chain.o linked_list.o
	$(CC) $^ -o snakes_and_ladders

tweets_generator.o: tweets_generator.c
	$(CC) $(FLAGS) -c $^ -o $@

snakes_and_ladders.o: snakes_and_ladders.c
	$(CC) $(FLAGS) -c $^ -o $@

markov_chain.o: markov_chain.c markov_chain.h
	$(CC) $(FLAGS) -c $< -o $@

linked_list.o: linked_list.c linked_list.h
	$(CC) $(FLAGS) -c $< -o $@

