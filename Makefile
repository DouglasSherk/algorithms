headers = -I"./headers/algorithms" -I"./headers/adt"
flags = -g -ggdb -std=c++14 -isystem ${GTEST_DIR}/include -L${GTEST_DIR} -lgtest -pthread $(headers)

hash_table:
	g++ $(flags) test/adt/hash_table.cpp -o bin/hash_table && ./bin/hash_table

list:
	g++ $(flags) test/adt/list.cpp -o bin/list && ./bin/list

queue:
	g++ $(flags) test/adt/queue.cpp -o bin/queue && ./bin/queue

vector:
	g++ $(flags) test/adt/vector.cpp -o bin/vector && ./bin/vector

knapsack:
	g++ $(flags) test/algorithms/knapsack.cpp -o bin/knapsack && ./bin/knapsack

all:
	make hash_table && make list

run:
	./bin/hash_table
	./bin/list
