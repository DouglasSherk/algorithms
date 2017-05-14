headers = -I"./headers/algorithms" -I"./headers/adt"
flags = -g -ggdb -std=c++14 -isystem ${GTEST_DIR}/include -L${GTEST_DIR} -lgtest -pthread $(headers)

# Data structures

avl_tree:
	g++ $(flags) test/adt/avl_tree.cpp -o bin/avl_tree && ./bin/avl_tree

bs_tree:
	g++ $(flags) test/adt/bs_tree.cpp -o bin/bs_tree && ./bin/bs_tree

hash_table:
	g++ $(flags) test/adt/hash_table.cpp -o bin/hash_table && ./bin/hash_table

list:
	g++ $(flags) test/adt/list.cpp -o bin/list && ./bin/list

priority_queue:
	g++ $(flags) test/adt/priority_queue.cpp -o bin/priority_queue && ./bin/priority_queue

queue:
	g++ $(flags) test/adt/queue.cpp -o bin/queue && ./bin/queue

vector:
	g++ $(flags) test/adt/vector.cpp -o bin/vector && ./bin/vector

# Algorithms

knapsack:
	g++ $(flags) test/algorithms/knapsack.cpp -o bin/knapsack && ./bin/knapsack

# All

all:
	make avl_tree
	make bs_tree
	make hash_table
	make list
	make priority_queue
	make queue
	make vector
	make knapsack

run:
	./bin/avl_tree
	./bin/bs_tree
	./bin/hash_table
	./bin/list
	./bin/priority_queue
	./bin/queue
	./bin/vector
	./bin/knapsack
