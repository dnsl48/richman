#ifndef TestKoverage__Richman__Text__Scanner__StopBaseCase___hpp
#define TestKoverage__Richman__Text__Scanner__StopBaseCase___hpp


#include "Koverager/Assertion.hpp"
#include "Koverager/Case.hpp"


namespace TestKoverage {
namespace Richman {
namespace Text {
namespace Scanner {

	class StopBaseCase : public Koverager::Case, private Koverager::Assertion {
	public:
		StopBaseCase () :
			Koverager::Case ("StopBaseCase", "Stop initialization test")
		{}

		void run ();
	};

}}}}


#endif
