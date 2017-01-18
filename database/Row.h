#ifndef Row_H
#define Row_H
#include "Entry.h"
#include <vector>
#include <string>

class Row {
	private:
		std::vector<Entry> entries;
	public:
		Entry& findEntry(const std::string&);
		Entry& findEntryIndex(const int&);
		std::size_t size();
		void add(Entry);
};
#endif
