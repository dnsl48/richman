#ifndef TestKoverage__Richman__Confee__VnumberBaseCase___hpp
#define TestKoverage__Richman__Confee__VnumberBaseCase___hpp


#include "Koverager/Assertion.hpp"
#include "Koverager/Case.hpp"


namespace TestKoverage {
namespace Richman {
namespace Confee {

	class VnumberBaseCase : public Koverager::Case, private Koverager::Assertion {
	public:
		VnumberBaseCase () :
			Koverager::Case ("VnumberBaseCase", "Vnumber essentials")
		{}

		void run ();
	};

}}}

#endif
