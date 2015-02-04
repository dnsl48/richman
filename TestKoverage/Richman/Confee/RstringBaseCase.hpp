#ifndef TestKoverage__Richman__Confee__RstringBaseCase___hpp
#define TestKoverage__Richman__Confee__RstringBaseCase___hpp


#include "Koverager/Assertion.hpp"
#include "Koverager/Case.hpp"


namespace TestKoverage {
namespace Richman {
namespace Confee {

	class RstringBaseCase : public Koverager::Case, private Koverager::Assertion {
	public:
		RstringBaseCase () :
			Koverager::Case ("RstringBaseCase", "Rstring essentials")
		{}

		void run ();
	};

}}}

#endif
