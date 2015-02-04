#ifndef TestKoverage__Richman__Confee__RdictBaseCase___hpp
#define TestKoverage__Richman__Confee__RdictBaseCase___hpp


#include "Koverager/Assertion.hpp"
#include "Koverager/Case.hpp"


namespace TestKoverage {
namespace Richman {
namespace Confee {

	class RdictBaseCase : public Koverager::Case, private Koverager::Assertion {
	public:
		RdictBaseCase () :
			Koverager::Case ("RdictBaseCase", "Rdict essentials test")
		{}

		void run ();
	};

}}}

#endif
