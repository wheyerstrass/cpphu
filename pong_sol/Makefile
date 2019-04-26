TARGET			=	main
CXXFLAGS		=	`pkg-config --cflags glfw3` -std=c++17 -Wall -pedantic -O3 -fdiagnostics-color
INCLUDE_PATH	=	-I../sgfx/include
LIB_PATH		=	-L../sgfx/lib
LIBS			=	-lsgfx `pkg-config --static --libs glfw3` -lGL -lGLEW

SRCS			=	src/*.cpp
OBJS			=	$(patsubst %.cpp,%.o,$(wildcard $(SRCS)))


all: $(TARGET) test

$(TARGET): $(OBJS) 
	$(CXX) $(OBJS) -o $(TARGET) $(LIB_PATH) $(LIBS)
	./$(TARGET)
	
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE_PATH) -c $< -o $@

clean:
	rm $(TARGET) $(OBJS)

.PHONY: shared clean test
