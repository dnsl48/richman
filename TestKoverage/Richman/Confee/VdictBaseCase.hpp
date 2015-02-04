#ifndef TestKoverage__Richman__Confee__VdictBaseCase___hpp
#define TestKoverage__Richman__Confee__VdictBaseCase___hpp


#include "Koverager/Assertion.hpp"
#include "Koverager/Case.hpp"


namespace TestKoverage {
namespace Richman {
namespace Confee {

	class VdictBaseCase : public Koverager::Case, private Koverager::Assertion {
	public:
		VdictBaseCase () :
			Koverager::Case ("VdictBaseCase", "Vdict essentials test")
		{}

		void run ();
	};

}}}

#endif
