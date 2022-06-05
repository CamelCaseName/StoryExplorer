#ifndef EEK_PARSER_H
#define EEK_PARSER_H
#include "parser.hpp"


class eek_parser : parser {
public:
	node_data parse(string text);
	bool preferred_extension(const string& extension);
private:
	node_data data;
};

#endif // !EEK_PARSER_H
