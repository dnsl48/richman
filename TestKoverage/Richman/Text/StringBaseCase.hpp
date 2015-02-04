#ifndef TestKoverage__Richman__Text__StringBaseCase___hpp
#define TestKoverage__Richman__Text__StringBaseCase___hpp


#include "Koverager/Assertion.hpp"
#include "Koverager/Case.hpp"


namespace TestKoverage {
namespace Richman {
namespace Text {

	class StringBaseCase : public Koverager::Case, private Koverager::Assertion {
	public:
		StringBaseCase () :
			Koverager::Case ("StringBaseCase", "String base testcase")
		{}

		void run ();
	};

}}}

#endif
