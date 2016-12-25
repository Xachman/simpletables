#include <stdio.h>
#include <sqlite3.h>


int main(void) {
	sqlite3 *db;
	char *zErrMsg =0;
   	int rc;

	rc = sqlite3_open("test.db", &db);

	if(rc) {
		printf("Can't open database: %s\n", sqlite3_errmsg(db));
		return(0);
	}else{
		printf("Opened database successfully\n");
	}
	sqlite3_close(db);
}
