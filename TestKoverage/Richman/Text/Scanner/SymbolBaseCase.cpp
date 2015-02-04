#include "TestKoverage/Richman/Text/Scanner/SymbolBaseCase.hpp"

#include "Richman/Text/Scanner/Symbol.hpp"


using TestKoverage::Richman::Text::Scanner::SymbolBaseCase;

using Richman::Text::Scanner::Symbol;


void SymbolBaseCase::run () {
	Symbol empty;

	assertEqual ("", empty.getString (), "Empty symbol; check the string", __FILE__, __LINE__);
	assertEqual ('\0', empty.getFirst (), "Empty symbol; check the first char", __FILE__, __LINE__);
	assertEqual (0, empty.getLength (), "Empty symbol; check the length", __FILE__, __LINE__);


	Symbol openBrace ("(");

	assertEqual ("(", openBrace.getString (), "Open brace; check the string", __FILE__, __LINE__);
	assertEqual ('(', openBrace.getFirst (), "Open brace; check the first char", __FILE__, __LINE__);
	assertEqual (1, openBrace.getLength (), "Open brace; check the length", __FILE__, __LINE__);


	Symbol openBraceEqualAutoLength ("(=");

	assertEqual ("(=", openBraceEqualAutoLength.getString (), "OpenBrace-Equal auto-length; check the string", __FILE__, __LINE__);
	assertEqual ('(', openBraceEqualAutoLength.getFirst (), "OpenBrace-Equal auto-length; check the first char", __FILE__, __LINE__);
	assertEqual (2, openBraceEqualAutoLength.getLength (), "OpenBrace-Equal auto-length; check the length", __FILE__, __LINE__);
}
