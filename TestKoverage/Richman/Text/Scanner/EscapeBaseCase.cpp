#include "TestKoverage/Richman/Text/Scanner/EscapeBaseCase.hpp"

#include "Richman/Text/Scanner/Escape.hpp"


using TestKoverage::Richman::Text::Scanner::EscapeBaseCase;

using Richman::Text::Scanner::Escape;


void EscapeBaseCase::run () {
	Escape escape ("\\esc");

	assertEqual ('\\', escape.getSymbol ().getFirst (), "Escape initialization; check the first symbol", __FILE__, __LINE__);
	assertEqual ("\\esc", escape.getSymbol ().getString () , "Escape initialization; check the string", __FILE__, __LINE__);
}
