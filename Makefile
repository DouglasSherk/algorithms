headers = -I"./headers"

hash_table:
	g++ -isystem ${GTEST_DIR}/include -pthread test/hash_table.cpp libgtest.a $(headers) -o bin/hash_table && ./bin/hash_table

list:
	g++ -isystem ${GTEST_DIR}/include -L${GTEST_DIR} -lgtest -pthread $(headers) test/list.cpp -o bin/list && ./bin/list

queue:
	g++ -isystem ${GTEST_DIR}/include -L${GTEST_DIR} -lgtest -pthread $(headers) test/queue.cpp -o bin/queue && ./bin/queue

vector:
	g++ -isystem ${GTEST_DIR}/include -L${GTEST_DIR} -lgtest -pthread $(headers) test/vector.cpp -o bin/vector && ./bin/vector

all:
	make hash_table && make list

run:
	./bin/hash_table
	./bin/list
