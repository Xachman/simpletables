#include "database/DatabaseHelper.h"


#ifdef DATABASEHELPER_H
extern "C" {
#endif


DatabaseHelper dataBaseHelper(const std::string& path) {
	DatabaseHelper dbh(path);

	return dbh;
}






#ifdef DATABASEHELPER_H
}
#endif
