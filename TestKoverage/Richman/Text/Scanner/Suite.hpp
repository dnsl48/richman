#ifndef TestKoverage__Richman__Text__Scanner__Suite___hpp
#define TestKoverage__Richman__Text__Scanner__Suite___hpp


#include "Koverager/Suite.hpp"
#include "TestKoverage/Richman/Text/Scanner/BraceBaseCase.hpp"
#include "TestKoverage/Richman/Text/Scanner/EscapeBaseCase.hpp"
#include "TestKoverage/Richman/Text/Scanner/ParserBraceCase.hpp"
#include "TestKoverage/Richman/Text/Scanner/ParserLongEscapeCase.hpp"
#include "TestKoverage/Richman/Text/Scanner/ParserShortEscapeCase.hpp"
#include "TestKoverage/Richman/Text/Scanner/ParserStopCase.hpp"
#include "TestKoverage/Richman/Text/Scanner/StopBaseCase.hpp"
#include "TestKoverage/Richman/Text/Scanner/StringResourceBaseCase.hpp"
#include "TestKoverage/Richman/Text/Scanner/SymbolBaseCase.hpp"


namespace TestKoverage {
namespace Richman {
namespace Text {
namespace Scanner {

	class Suite : public Koverager::Suite {
	public:
		Suite () : Koverager::Suite ("Text Scanner suite") {
			addCase (new SymbolBaseCase ());
			addCase (new BraceBaseCase ());
			addCase (new StopBaseCase ());
			addCase (new EscapeBaseCase ());
			addCase (new StringResourceBaseCase ());
			addCase (new ParserStopCase ());
			addCase (new ParserShortEscapeCase ());
			addCase (new ParserLongEscapeCase ());
			addCase (new ParserBraceCase ());
		}
	};

}}}}

#endif
