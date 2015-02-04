#ifndef TestKoverage__Richman__Confee__NodeBaseCase___hpp
#define TestKoverage__Richman__Confee__NodeBaseCase___hpp


#include "Koverager/Assertion.hpp"
#include "Koverager/Case.hpp"


namespace TestKoverage {
namespace Richman {
namespace Confee {

	class NodeBaseCase : public Koverager::Case, private Koverager::Assertion {
	public:
		NodeBaseCase () :
			Koverager::Case ("NodeBaseCase", "Node essentials")
		{}

		void run ();
	};

}}}

#endif
