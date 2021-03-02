LIB_DIR = -L /home/w/lib/systemc-2.3.3/lib-linux64/
INC_DIR = -I /home/w/lib/systemc-2.3.3/include/
LIB = -lsystemc -Wl,-rpath,/home/w/lib/systemc-2.3.3/lib-linux64/
SRC = main.cpp bmp.cpp tb.cpp hscaler.cpp
SRCH = $(SRC:.cpp=.h)
OBJ = $(SRC:.cpp=.o)
go = g++ -o
gc = g++ -c

hsc: $(OBJ)
	$(go) hsc $(OBJ) $(LIB_DIR) $(INC_DIR) $(LIB)
main.o: $(SRC)
	$(gc) main.cpp $(LIB_DIR) $(INC_DIR) $(LIB) 
bmp.o: bmp.cpp bmp.h 
	$(gc) bmp.cpp
tb.o: tb.cpp bmp.cpp tb.h bmp.h
	$(gc) tb.cpp $(LIB_DIR) $(INC_DIR) $(LIB)
hscaler.o: hscaler.cpp hscaler.h
	$(gc) hscaler.cpp $(LIB_DIR) $(INC_DIR) $(LIB) 
clean:                                                                  
	rm -rf hsc $(OBJ)
