SRCS=main.cpp simulator.cpp operator.cpp agent.cpp object.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

RM=rm -f


simulator.test: $(OBJS)
	g++ -std=c++11 -o simulator.test $(OBJS)

simulator.o: simulator.h simulator.cpp
	g++ -std=c++11 -c simulator.cpp

operator.o: operator.h operator.cpp
	g++ -std=c++11 -c operator.cpp

agent.o: agent.h operator.h agent.cpp
	g++ -std=c++11 -c agent.cpp

object.o: object.h object.cpp
	g++ -std=c++11 -c object.cpp


clean:
	$(RM) $(OBJS)
