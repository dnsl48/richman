#ifndef TestKoverage__Richman__Exception__Suite___hpp
#define TestKoverage__Richman__Exception__Suite___hpp


#include "Koverager/Suite.hpp"
#include "TestKoverage/Richman/Exception/RichExceptionBaseCase.hpp"


namespace TestKoverage {
namespace Richman {
namespace Exception {

	class Suite : public Koverager::Suite {
	public:
		Suite () : Koverager::Suite ("Exception suite") {
			addCase (new RichExceptionBaseCase ());
		}
	};

}}}

#endif
