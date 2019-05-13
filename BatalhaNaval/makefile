TARGET = bb

CC = g++
CFLAGS= -std=gnu++14 -Wall -Wextra -g

RM = rm

DEPS = $(wildcard *.h)
OBJS = $(patsubst %.cpp, %.o, $(wildcard *.cpp))

all: bb

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

run: $(TARGET)
	./$(TARGET) ${ARGS}

clean:
	$(shell find . -type f -name '*.o' -exec $(RM) {} \;)
	$(shell find . -type f -executable -exec $(RM) {} \;)
