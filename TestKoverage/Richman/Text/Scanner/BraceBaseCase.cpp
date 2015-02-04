#include "TestKoverage/Richman/Text/Scanner/BraceBaseCase.hpp"

#include "Richman/Text/Scanner/Brace.hpp"


using TestKoverage::Richman::Text::Scanner::BraceBaseCase;

using Richman::Text::Scanner::Brace;


void BraceBaseCase::run () {
	Brace brace ("(", ")", true, false, true, false);

	assertEqual ("(", brace.getOpenSymbol ().getString (), "Brace initialization; check the open symbol string", __FILE__, __LINE__);
	assertEqual ('(', brace.getOpenSymbol ().getFirst (), "Brace initialization; check the open symbol first char", __FILE__, __LINE__);
	assertEqual (1u, brace.getOpenSymbol ().getLength (), "Brace initialization; check the open symbol length", __FILE__, __LINE__);

	assertEqual (")", brace.getCloseSymbol ().getString (), "Brace initialization; check the close symbol string", __FILE__, __LINE__);
	assertEqual (')', brace.getCloseSymbol ().getFirst (), "Brace initialization; check the close symbol first char", __FILE__, __LINE__);
	assertEqual (1u, brace.getCloseSymbol ().getLength (), "Brace initialization; check the close symbol length", __FILE__, __LINE__);

	assertTrue (brace.getTraits ().escapeShort, "Brace initialization; check traits; escape short", __FILE__, __LINE__);
	assertFalse (brace.getTraits ().escapeLong, "Brace initialization; check traits; escape long", __FILE__, __LINE__);
	assertTrue (brace.getTraits ().escapeStop, "Brace initialization; check traits; escape stop", __FILE__, __LINE__);
	assertFalse (brace.getTraits ().stop, "Brace initialization; check traits; stop", __FILE__, __LINE__);
}
