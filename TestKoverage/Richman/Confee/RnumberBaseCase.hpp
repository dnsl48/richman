#ifndef TestKoverage__Richman__Confee__RnumberBaseCase___hpp
#define TestKoverage__Richman__Confee__RnumberBaseCase___hpp


#include "Koverager/Assertion.hpp"
#include "Koverager/Case.hpp"


namespace TestKoverage {
namespace Richman {
namespace Confee {

	class RnumberBaseCase : public Koverager::Case, private Koverager::Assertion {
	public:
		RnumberBaseCase () :
			Koverager::Case ("RnumberBaseCase", "Rnumber essentials")
		{}

		void run ();
	};

}}}

#endif
