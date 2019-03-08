OBJOUT := ./out/
EXEOUT := ./out/
INCLUDE_DIR := ../async_logging/ -I../muduo_client/
LIB := -lpthread
SRC_DIR = ../async_logging/ ../muduo_client/

SRC := $(wildcard *.cpp)
SRC += $(wildcard ../async_logging/*.cpp)
SRC += $(wildcard ../muduo_client/*.cpp)
OBJ := $(patsubst %.cpp,%.o,$(SRC))
TARGET := test.out

#CC := arm-oe-linux-gnueabi-g++
CC := g++
CFLAGS := -I$(INCLUDE_DIR)

all: $(TARGET)
$(TARGET) : $(OBJ)
	@echo "SRC : " $(SRC) 
	@echo "OBJ : " $(OBJ) 
	@echo "TARGET : " $(TARGET) 
	#$(CC) -C $(SRC_DIR)
	$(CC) $(CFLAGS) ../async_logging/*.o ../muduo_client/*.o ./*.o -g -o $(TARGET) $(LIB) -std=c++11
	#mv $^ $(OBJOUT)
	@echo "Compiling" $@ "end\n"

%.o : %.c
	@echo "Compiling" $< "..."
	$(CC) $(CFLAGS) -c $^ -o $@ $(LIB)
	@echo "Compiling" $@ "end\n"

%.o : %.cpp
	@echo "Compiling" $< "..."
	$(CC) $(CFLAGS) -c $^ -o $@ $(LIB) -std=c++11
	@echo "Compiling" $@ "end\n"

.PHONY: clean

clean:
	rm -rf $(TARGET)
	rm -rf ../async_logging/*.o ../muduo_client/*.o
	rm -rf ./*.o
