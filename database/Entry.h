#ifndef Entry_H
#define Entry_H
#include <string>

class Entry {
	private:	
		std::string columnName;
		std::string value;
	public:
		Entry(const std::string&, const std::string&);
		std::string getColumnName();
		std::string getValue();
};

#endif
