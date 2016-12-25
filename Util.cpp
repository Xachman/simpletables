#include <string>
#include <sys/stat.h>
#include "Util.h"

bool Util::fileExist(const std::string& name) {
	struct stat buffer;   
	return (stat (name.c_str(), &buffer) == 0); 
}
