#include <string>
#include "Column.h"

class Table {
	private:
		virtual bool autoincrement() = 0;
		virtual std::string tableName() = 0;
		virtual std::vector<Column> columns() = 0;
	public:
		std::string createTableSql();
};
