#include "TestKoverage/Richman/Text/Scanner/StopBaseCase.hpp"

#include "Richman/Text/Scanner/Stop.hpp"


using TestKoverage::Richman::Text::Scanner::StopBaseCase;

using Richman::Text::Scanner::Stop;


void StopBaseCase::run () {
	Stop stop ("@stop-symbol", false, true, false, true);

	assertEqual ('@', stop.getSymbol ().getFirst (), "Stop initialization; check the first symbol", __FILE__, __LINE__);
	assertEqual ("@stop-symbol", stop.getSymbol ().getString (), "Stop initialization; check the string", __FILE__, __LINE__);

	assertFalse (stop.getTraits ().skip, "Stop initialization; check trait skip", __FILE__, __LINE__);
	assertTrue (stop.getTraits ().greedy, "Stop initialization; check trait greedy", __FILE__, __LINE__);
	assertFalse (stop.getTraits ().escapeShort, "Stop initialization; check trait escapeShort", __FILE__, __LINE__);
	assertTrue (stop.getTraits ().escapeLong, "Stop initialization; check trait escapeLong", __FILE__, __LINE__);
}
