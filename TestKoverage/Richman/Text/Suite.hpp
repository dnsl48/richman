#ifndef TestKoverage__Richman__Text__Suite___hpp
#define TestKoverage__Richman__Text__Suite___hpp


#include "Koverager/Suite.hpp"
#include "TestKoverage/Richman/Text/StringBaseCase.hpp"


namespace TestKoverage {
namespace Richman {
namespace Text {

	class Suite : public Koverager::Suite {
	public:
		Suite () : Koverager::Suite ("Text suite") {
			addCase (new StringBaseCase ());
		}
	};

}}}

#endif
