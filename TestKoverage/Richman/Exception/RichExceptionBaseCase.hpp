#ifndef TestKoverage__Richman__Exception__RichExceptionBaseCase___hpp
#define TestKoverage__Richman__Exception__RichExceptionBaseCase___hpp


#include "Koverager/Assertion.hpp"
#include "Koverager/Case.hpp"


namespace TestKoverage {
namespace Richman {
namespace Exception {

	class RichExceptionBaseCase : public Koverager::Case, private Koverager::Assertion {
	public:
		RichExceptionBaseCase () :
			Koverager::Case ("RichExceptionBaseCase", "RichException base testcase")
		{}

		void run ();
	};

}}}

#endif
