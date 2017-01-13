SOURCE=lib/base64_enc.c lib/websocket.c lib/sha1.c lib/sqlite/sqlite3.h main.c 
CC = g++
WIN32CC = i686-w64-mingw32-g++
LDFLAGS=-lpthread -ldl
INCLUDES=lib/sqlite
OBJECTS= main.o
CPPFILES = main.cpp
CLASSFILES = Util database/Table database/Entry database/Row database/SqliteDBH database/DatabaseHelper
DEPCLASSES = database/Column
LIBFLAGS = -lsqlite3
FLAGS = $(LIBFLAGS)
EXEC = main.exe
TESTFLAGS = $(FLAGS)

#all: $(OBJECTS)                                                       
#	$(CC) $(CPPFILES) $(FLAGS) -o $(EXEC)

testcases: 
	$(CC) tests/Main.cpp  $(foreach CLASSFILES, $(CLASSFILES), ${CLASSFILES:=.cpp} tests/${CLASSFILES:=Tests.cpp}) $(foreach DEPCLASSES, $(DEPCLASSES), $(DEPCLASSES).cpp) $(TESTFLAGS) -o tests.exe; ./tests.exe;


windows32:
	$(WIN32CC)  WinMain.cpp $(foreach CLASSFILES, $(CLASSFILES), $(CLASSFILES).cpp) $(foreach DEPCLASSES, $(DEPCLASSES), $(DEPCLASSES).cpp) resource.o  -Isqlite3/ -Lsqlite3/ -static-libgcc -static-libstdc++ -lsqlite3 -mwindows -Wl,-subsystem,windows -lcomdlg32  -o dist/windows32/win32.exe;

single_objects: 
	 $(foreach DEPCLASSES, $(DEPCLASSES), $(CC) -c -Wall -Werror -fpic $(DEPCLASSES).cpp -o objects/$(DEPCLASSES).o;) $(foreach CLASSFILES, $(CLASSFILES), $(CC) -c -Wall -Werror -fpic $(CLASSFILES).cpp -o objects/$(CLASSFILES).o;)

create_lib: 
	$(CC) -shared -o dist/linux/libsimpletables.so $(foreach DEPCLASSES, $(DEPCLASSES), objects/$(DEPCLASSES).o) $(foreach CLASSFILES, $(CLASSFILES),  objects/$(CLASSFILES).o)
 
