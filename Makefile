SOURCE=lib/base64_enc.c lib/websocket.c lib/sha1.c lib/sqlite/sqlite3.h main.c 
CC = g++
LDFLAGS=-lpthread -ldl
INCLUDES=lib/sqlite
OBJECTS= main.o
CPPFILES = main.cpp
CLASSFILES = Util database/Table database/Entry database/Row database/SqliteDBH
DEPCLASSES = database/Column.cpp
FLAGS = -lsqlite3
EXEC = main.exe
TESTFLAGS = $(FLAGS)

all: $(OBJECTS)                                                       
	$(CC) $(CPPFILES) $(FLAGS) -o $(EXEC)

testcases: 
	$(CC) tests/Main.cpp  $(foreach CLASSFILES, $(CLASSFILES), ${CLASSFILES:=.cpp} tests/${CLASSFILES:=Tests.cpp}) $(DEPCLASSES) $(TESTFLAGS) -o tests.exe; ./tests.exe;

