#ifndef TestKoverage__Richman__Confee__VboxBaseCase___hpp
#define TestKoverage__Richman__Confee__VboxBaseCase___hpp


#include "Koverager/Assertion.hpp"
#include "Koverager/Case.hpp"


namespace TestKoverage {
namespace Richman {
namespace Confee {

	class VboxBaseCase : public Koverager::Case, private Koverager::Assertion {
	public:
		VboxBaseCase () :
			Koverager::Case ("VboxBaseCase", "Vbox essentials test")
		{}

		void run ();
	};

}}}

#endif
