#ifndef TestKoverage__Richman__Confee__Mock__SameValue___hpp
#define TestKoverage__Richman__Confee__Mock__SameValue___hpp


#include "Richman/Confee/Value.hpp"


namespace TestKoverage {
namespace Richman {
namespace Confee {
namespace Mock {


	class SameValue : public ::Richman::Confee::Value {
	public:
		SameValue * copy () const {
			return new SameValue ();
		}

		bool operator== (const ::Richman::Confee::Value & value) const {
			return true;
		}
	};


}}}}


#endif
