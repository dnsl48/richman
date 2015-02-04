#ifndef TestKoverage__Richman__Text__Scanner__StringResourceBaseCase___hpp
#define TestKoverage__Richman__Text__Scanner__StringResourceBaseCase___hpp


#include "Koverager/Assertion.hpp"
#include "Koverager/Case.hpp"


namespace TestKoverage {
namespace Richman {
namespace Text {
namespace Scanner {

	class StringResourceBaseCase : public Koverager::Case, private Koverager::Assertion {
	public:
		StringResourceBaseCase () :
			Koverager::Case ("StringResourceBaseCase", "StringResource simplest test")
		{}

		void run ();
	};

}}}}

#endif
