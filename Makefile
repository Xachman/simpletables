SOURCE=lib/base64_enc.c lib/websocket.c lib/sha1.c lib/sqlite/sqlite3.h main.c 
CC = g++
LDFLAGS=-lpthread -ldl
INCLUDES=lib/sqlite
OBJECTS= main.o
CPPFILES = main.cpp
CLASSFILES = Util
FLAGS = -lsqlite3
EXEC = main.exe


all: $(OBJECTS)                                                       
	$(CC) $(CPPFILES) $(FLAGS) -o $(EXEC)

testscases: 
	$(foreach CLASSFILES, $(CLASSFILES), $(CC) ${CLASSFILES:=.cpp} tests/${CLASSFILES:=Tests.cpp}  $(TESTFLAGS) -o ${CLASSFILES:=Tests.exe}; ./$(CLASSFILES)Tests.exe;)

