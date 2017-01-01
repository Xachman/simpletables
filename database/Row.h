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
		void add(Entry);
};
#endif
