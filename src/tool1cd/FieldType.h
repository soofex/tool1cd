/*
    Tool1CD library provides access to 1CD database files.
    Copyright © 2009-2017 awa
    Copyright © 2017-2018 E8 Tools contributors

    This file is part of Tool1CD Library.

    Tool1CD Library is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Tool1CD Library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with Tool1CD Library.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef TOOL1CD_PROJECT_FIELDTYPE_H
#define TOOL1CD_PROJECT_FIELDTYPE_H

#include "Constants.h"
#include "Parse_tree.h"

class Table;

struct field_type_declaration {
	type_fields type {type_fields::tf_binary};
	bool null_exists {false};
	int32_t length {0};
	int32_t precision {0};
	bool case_sensitive {false};

	static field_type_declaration parse_tree(Tree *field_tree);
};


class FieldType {
public:
	virtual type_fields get_type() const = 0;
	virtual int32_t get_length() const = 0;
	virtual int32_t get_size() const = 0;
	virtual int32_t get_precision() const = 0;
	virtual bool get_case_sensitive() const = 0;
	virtual std::string get_presentation_type() const = 0;

	virtual std::string get_presentation(
			const char *rec,
			bool EmptyNull,
			wchar_t Delimiter,
			bool ignore_showGUID,
			bool detailed) const = 0;

	virtual bool get_binary_value(char *buf, const std::string &value) const = 0;

	virtual std::string get_XML_presentation(
			const char *rec,
			const Table *parent,
			bool ignore_showGUID) const = 0;

	virtual uint32_t get_sort_key(
			const char* rec,
			unsigned char* SortKey,
			int32_t maxlen) const = 0;


	static FieldType *create_type_manager(
			const field_type_declaration &type_declaration,
				  bool                    can_be_guid = false);
	static FieldType *Version8();

	// TODO: убрать это куда-нибудь
	static bool showGUIDasMS; // Признак, что GUID надо преобразовывать по стилю MS (иначе по стилю 1С)
	static bool showGUID;

};


#endif //TOOL1CD_PROJECT_FIELDTYPE_H
