#ifndef Column_H
#define Column_H
#include <string>

class Column {
	private:
		std::string mType;
		std::string mName;
	public:
		Column(const std::string&,const std::string&);
		std::string name();
		std::string type();
};

#endif

