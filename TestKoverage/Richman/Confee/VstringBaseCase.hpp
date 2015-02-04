#ifndef TestKoverage__Richman__Confee__VstringBaseCase___hpp
#define TestKoverage__Richman__Confee__VstringBaseCase___hpp


#include "Koverager/Assertion.hpp"
#include "Koverager/Case.hpp"


namespace TestKoverage {
namespace Richman {
namespace Confee {

	class VstringBaseCase : public Koverager::Case, private Koverager::Assertion {
	public:
		VstringBaseCase () :
			Koverager::Case ("VstringBaseCase", "Vstring essentials")
		{}

		void run ();
	};

}}}

#endif
