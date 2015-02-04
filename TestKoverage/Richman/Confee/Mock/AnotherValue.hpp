#ifndef TestKoverage__Richman__Confee__Mock__AnotherValue___hpp
#define TestKoverage__Richman__Confee__Mock__AnotherValue___hpp


#include "Richman/Confee/Value.hpp"


namespace TestKoverage {
namespace Richman {
namespace Confee {
namespace Mock {


	class AnotherValue : public ::Richman::Confee::Value {
	public:
		AnotherValue * copy () const {
			return new AnotherValue ();
		}

		bool operator== (const ::Richman::Confee::Value & value) const {
			return this == &value;
		}
	};


}}}}


#endif
