#ifndef TestKoverage__Richman__Text__Scanner__SymbolBaseCase___hpp
#define TestKoverage__Richman__Text__Scanner__SymbolBaseCase___hpp


#include "Koverager/Assertion.hpp"
#include "Koverager/Case.hpp"


namespace TestKoverage {
namespace Richman {
namespace Text {
namespace Scanner {

	class SymbolBaseCase : public Koverager::Case, private Koverager::Assertion {
	public:
		SymbolBaseCase () : Koverager::Case ("SymbolBaseCase", "Simplest test of Symbol entity") {}

		void run ();
	};

}}}}


#endif
