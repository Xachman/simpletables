#include "Row.h"
#include "Entry.h"
#include <string>

Entry& Row::findEntry(const std::string& columnName) {
	for(int i = 0; i < this->entries.size(); i++) {
		Entry& cEntry = this->entries[i];
		if(columnName == cEntry.getColumnName()) {
			return cEntry;
		}	
	}
	throw "No Entry Found";

}

void Row::add(Entry en) {
	this->entries.push_back(en);
}
