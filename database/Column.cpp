#include "Column.h"

Column::Column(const std::string& name, const std::string& type) {
	this->mName = name;
	this->mType = type;
}

std::string Column::name() {
	return this->mName;
}

std::string Column::type() {
	return this->mType;
}
