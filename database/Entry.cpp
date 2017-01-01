#include "Entry.h"

Entry::Entry(const std::string& columnName, const std::string& value):columnName(columnName), value(value) {

}


std::string Entry::getColumnName() {
 	return this->columnName;
}
std::string Entry::getValue() {
	return this->value;
}
