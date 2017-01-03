#include "DatabaseHelper.h"
#include "SqliteDBH.h"
#include <string>
#include <sstream>

DatabaseHelper::DatabaseHelper(const std::string& path):dbh(path), path(path) {
}

void DatabaseHelper::open() {
	this->dbh.open();
}


bool DatabaseHelper::createTable(Table& table) {
	this->dbh.execute(table.createTableSql());

	std::vector<Row> rows = this->dbh.execute("SELECT name FROM sqlite_master WHERE type='table' AND name='"+table.tableName()+"'");
	for(int i = 0; i < rows.size(); i++) {
		if(rows[i].findEntry("name").getValue() == table.tableName()) {
			return true;
		}
	}
	return false;
}

std::vector<Row> DatabaseHelper::getAll(Table& table) {

	std::vector<Row> rows = this->dbh.execute("SELECT * FROM "+table.tableName());
	return rows;
}


Row DatabaseHelper::getById(int id, Table& table) {
	std::stringstream ss;
	ss << id;
	std::vector<Row> rows = this->dbh.execute("SELECT * FROM "+table.tableName()+" WHERE id="+ss.str());
	return rows[0];
}
std::string DatabaseHelper::insert(Row& row, Table& table) {
	std::vector<Column> columns = table.columns();
	std::stringstream columnSql;
	std::stringstream valueSql;
	for(int i = 0; i < columns.size(); i++) {
		Column column = columns[i];
		columnSql << column.name();
		std::string val="";
		try {
			val = row.findEntry(column.name()).getValue();	
		} catch (const std::exception& e) {

		}

		if(column.type() != "INT") {
			val = "'"+val+"'";
		}
		if((i+1) < columns.size()) {
			columnSql << ",";
			valueSql << ",";
		}
		
	}

	this->dbh.execute("INSERT INTO "+table.tableName()+" ("+columnSql.str()+") VALUES ("+valueSql.str()+");");
	
	std::vector<Row> rows = this->dbh.execute("SELECT * FROM "+table.tableName()+" ORDER BY id DESC LIMIT 1");
	try {
		return rows[0].findEntry("id").getValue();
	} catch(const std::exception& e) {
		return "0";
	}
}
void DatabaseHelper::close() {
	this->dbh.close();
}
