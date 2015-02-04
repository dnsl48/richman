#ifndef TestKoverage__Richman__Confee__RboxBaseCase___hpp
#define TestKoverage__Richman__Confee__RboxBaseCase___hpp


#include "Koverager/Assertion.hpp"
#include "Koverager/Case.hpp"


namespace TestKoverage {
namespace Richman {
namespace Confee {

	class RboxBaseCase : public Koverager::Case, private Koverager::Assertion {
	public:
		RboxBaseCase () :
			Koverager::Case ("RboxBaseCase", "Rbox essentials test")
		{}

		void run ();
	};

}}}

#endif
