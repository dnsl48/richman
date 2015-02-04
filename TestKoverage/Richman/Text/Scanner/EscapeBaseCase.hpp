#ifndef TestKoverage__Richman__Text__Scanner__EscapeBaseCase___hpp
#define TestKoverage__Richman__Text__Scanner__EscapeBaseCase___hpp


#include "Koverager/Assertion.hpp"
#include "Koverager/Case.hpp"


namespace TestKoverage {
namespace Richman {
namespace Text {
namespace Scanner {

	class EscapeBaseCase : public Koverager::Case, private Koverager::Assertion {
	public:
		EscapeBaseCase () :
			Koverager::Case ("EscapeBaseCase", "Escape initialization test")
		{}

		void run ();
	};

}}}}


#endif
