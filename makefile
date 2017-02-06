SOURCES=simulator.cpp operator.cpp agent.cpp object.cpp
OBJECTS=$(subst .cpp,.o,$(SOURCES))

FLAGS=-std=c++11 -fPIC
PYBIND_FLAGS=-shared -I pybind11/include `python-config --cflags --ldflags` 
RM=rm -f

rpg.so: pybind_test.o $(OBJECTS)
	g++ $(FLAGS) $(PYBIND_FLAGS) pybind_test.o $(OBJECTS) -o rpg.so

simulator.test: main.o $(OBJECTS)
	g++ $(FLAGS) -o simulator.test main.o $(OBJECTS)

pybind_test.o: simulator.h pybind_test.cpp
	g++ $(FLAGS) $(PYBIND_FLAGS) -c pybind_test.cpp

main.o: simulator.h main.cpp
	g++ $(FLAGS) -c main.cpp

simulator.o: simulator.h simulator.cpp
	g++ $(FLAGS) -c simulator.cpp

operator.o: operator.h operator.cpp
	g++ $(FLAGS) -c operator.cpp

agent.o: agent.h operator.h agent.cpp
	g++ $(FLAGS) -c agent.cpp

object.o: object.h object.cpp
	g++ $(FLAGS) -c object.cpp


clean:
	$(RM) $(OBJECTS)

