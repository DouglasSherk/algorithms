headers = -I"./headers/algorithms" -I"./headers/adt"
flags = -g -isystem ${GTEST_DIR}/include -L${GTEST_DIR} -lgtest -pthread $(headers)

hash_table:
	g++ -isystem ${GTEST_DIR}/include -L${GTEST_DIR} -lgtest -pthread $(headers) test/adt/hash_table.cpp -o bin/hash_table && ./bin/hash_table

list:
	g++ -isystem ${GTEST_DIR}/include -L${GTEST_DIR} -lgtest -pthread $(headers) test/adt/list.cpp -o bin/list && ./bin/list

queue:
	g++ -isystem ${GTEST_DIR}/include -L${GTEST_DIR} -lgtest -pthread $(headers) test/adt/queue.cpp -o bin/queue && ./bin/queue

vector:
	g++ -isystem ${GTEST_DIR}/include -L${GTEST_DIR} -lgtest -pthread $(headers) test/adt/vector.cpp -o bin/vector && ./bin/vector

knapsack:
	g++ $(flags) test/algorithms/knapsack.cpp -o bin/knapsack && ./bin/knapsack

all:
	make hash_table && make list

run:
	./bin/hash_table
	./bin/list
