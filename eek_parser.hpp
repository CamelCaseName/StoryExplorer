#ifndef EEK_PARSER_H
#define EEK_PARSER_H
#include "parser.hpp"

class eek_parser : parser {
public:
	node_data parse(std::string text);
	std::string preferred_extension = "story|character";
private:
	node_data data;
};

#endif // !EEK_PARSER_H
