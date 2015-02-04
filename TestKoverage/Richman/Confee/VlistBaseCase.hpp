#ifndef TestKoverage__Richman__Confee__VlistBaseCase___hpp
#define TestKoverage__Richman__Confee__VlistBaseCase___hpp


#include "Koverager/Assertion.hpp"
#include "Koverager/Case.hpp"


namespace TestKoverage {
namespace Richman {
namespace Confee {

	class VlistBaseCase : public Koverager::Case, private Koverager::Assertion {
	public:
		VlistBaseCase () :
			Koverager::Case ("VlistBaseCase", "Vlist essentials")
		{}

		void run ();
	};

}}}

#endif
