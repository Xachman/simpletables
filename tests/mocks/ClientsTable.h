#ifndef CLIENTSMOCK_H
#define CLIENTSMOCK_H
#include "../../database/Column.h"
#include "../../database/Table.h"
#include <string>
#include <vector>

class ClientsTable : public Table {
	public:
		std::vector<Column> columns();
		bool autoincrement();
		std::string tableName();
};

#endif
