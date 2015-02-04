#ifndef TestKoverage__Richman__Confee__RboolBaseCase___hpp
#define TestKoverage__Richman__Confee__RboolBaseCase___hpp


#include "Koverager/Assertion.hpp"
#include "Koverager/Case.hpp"


namespace TestKoverage {
namespace Richman {
namespace Confee {

	class RboolBaseCase : public Koverager::Case, private Koverager::Assertion {
	public:
		RboolBaseCase () :
			Koverager::Case ("RboolBaseCase", "Rbool essentials test case")
		{}

		void run ();
	};

}}}

#endif
