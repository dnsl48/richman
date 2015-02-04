#ifndef TestKoverage__Richman__Confee__VboolBaseCase___hpp
#define TestKoverage__Richman__Confee__VboolBaseCase___hpp


#include "Koverager/Assertion.hpp"
#include "Koverager/Case.hpp"


namespace TestKoverage {
namespace Richman {
namespace Confee {

	class VboolBaseCase : public Koverager::Case, private Koverager::Assertion {
	public:
		VboolBaseCase () :
			Koverager::Case ("VboolBaseCase", "Vbool essentials test case")
		{}

		void run ();
	};

}}}

#endif
