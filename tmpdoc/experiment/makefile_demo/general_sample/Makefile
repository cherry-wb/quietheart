test for use.
  1 TARGET=main
  2 SOURCES=main.c myfile.c
  3 OBJECTS=main.o myfile.o
  4 CC=gcc
  5 
  6 default:$(TARGET)
  7 
  8 $(TARGET):$(OBJECTS)
  9     ${CC} $^ -o $@
 10 
 11 $(OBJECTS):%.o:%.c
 12 
 13 .PHONY:clean
 14 clean:
 15     rm -f ${TARGET} ${OBJECTS}
