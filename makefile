SIM_PATH=simulator/
SIM_SRCS=python_wrapper.cpp main.cpp simulator.cpp operator.cpp agent.cpp object.cpp
SRCS=$(addprefix $(SIM_PATH),$(SIM_SRCS))

TRAIN_PATH=trainer/
PY_PKG=$(TRAIN_PATH)rpg.so

OBJS=$(subst .cpp,.o,$(SRCS))

FLAGS=-std=c++11 -fPIC
PYBIND_FLAGS=-shared -I $(SIM_PATH)pybind11/include `python-config --cflags --ldflags` 
RM=rm -f

$(PY_PKG): $(OBJS)
	g++ $(FLAGS) $(PYBIND_FLAGS) $(OBJS) -o $(PY_PKG)

$(SIM_PATH)simulator.test: $(OBJS)
	g++ $(FLAGS) -o $(SIM_PATH)simulator.test $(OBJS)

$(SIM_PATH)python_wrapper.o: $(SIM_PATH)simulator.h $(SIM_PATH)python_wrapper.cpp
	g++ $(FLAGS) $(PYBIND_FLAGS) -c $(SIM_PATH)python_wrapper.cpp -o $(SIM_PATH)python_wrapper.o

$(SIM_PATH)main.o: $(SIM_PATH)simulator.h $(SIM_PATH)main.cpp
	g++ $(FLAGS) -c $(SIM_PATH)main.cpp -o $(SIM_PATH)main.o

$(SIM_PATH)simulator.o: $(SIM_PATH)simulator.h $(SIM_PATH)simulator.cpp
	g++ $(FLAGS) -c $(SIM_PATH)simulator.cpp -o $(SIM_PATH)simulator.o

$(SIM_PATH)operator.o: $(SIM_PATH)operator.h $(SIM_PATH)operator.cpp
	g++ $(FLAGS) -c $(SIM_PATH)operator.cpp -o $(SIM_PATH)operator.o

$(SIM_PATH)agent.o: $(SIM_PATH)agent.h $(SIM_PATH)operator.h $(SIM_PATH)agent.cpp
	g++ $(FLAGS) -c $(SIM_PATH)agent.cpp -o $(SIM_PATH)agent.o

$(SIM_PATH)object.o: $(SIM_PATH)object.h $(SIM_PATH)object.cpp
	g++ $(FLAGS) -c $(SIM_PATH)object.cpp -o $(SIM_PATH)object.o


clean:
	$(RM) $(OBJS) 

