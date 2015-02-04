#ifndef TestKoverage__Richman__Text__Scanner__BraceBaseCase___hpp
#define TestKoverage__Richman__Text__Scanner__BraceBaseCase___hpp


#include "Koverager/Assertion.hpp"
#include "Koverager/Case.hpp"


namespace TestKoverage {
namespace Richman {
namespace Text {
namespace Scanner {

	class BraceBaseCase : public Koverager::Case, private Koverager::Assertion {
	public:
		BraceBaseCase () :
			Koverager::Case ("BraceBaseCase", "Brace initialization test")
		{}

		void run ();
	};

}}}}


#endif
