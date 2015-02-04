#ifndef TestKoverage__Richman__Confee__RlistBaseCase___hpp
#define TestKoverage__Richman__Confee__RlistBaseCase___hpp


#include "Koverager/Assertion.hpp"
#include "Koverager/Case.hpp"


namespace TestKoverage {
namespace Richman {
namespace Confee {

	class RlistBaseCase : public Koverager::Case, private Koverager::Assertion {
	public:
		RlistBaseCase () :
			Koverager::Case ("RlistBaseCase", "Rlist essentials")
		{}

		void run ();
	};

}}}

#endif
