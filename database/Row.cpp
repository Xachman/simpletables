#include "Row.h"
#include "Entry.h"
#include <string>

Entry& Row::findEntry(const std::string& columnName) {
	for(std::size_t i = 0; i < this->entries.size(); i++) {
		Entry& cEntry = this->entries[i];
		if(columnName == cEntry.getColumnName()) {
			return cEntry;
		}	
	}
	throw "No Entry Found";

}

Entry& Row::findEntryIndex(const int& index) {
	for(std::size_t i = 0; i < this->entries.size(); i++) {
		Entry& cEntry = this->entries[i];
		if(index == i) {
			return cEntry;
		}	
	}
	throw "No Entry Found";

}

std::size_t Row::size() {
	return this->entries.size();
}

void Row::add(Entry en) {
	this->entries.push_back(en);
}
