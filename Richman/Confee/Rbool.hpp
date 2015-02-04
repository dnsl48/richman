#ifndef Richman__Confee__Rbool___hpp
#define Richman__Confee__Rbool___hpp


#include "Richman/Confee/Rule.hpp"
#include "Richman/Confee/Vbool.hpp"


namespace Richman {
namespace Confee {


	/* Base implementation of the rule for booleans */
	class Rbool : public Rule {
		char _rule;

	public:
		/* Base constructor allows to pass three values: true, false and null
		 * @mask Bitwise mask of the allowed value
		 */
		Rbool (char mask = Vbool::True | Vbool::False | Vbool::Null) :
			_rule (mask)
		{}


		/* @inherit */
		Rbool * copy () const {
			return new Rbool (_rule);
		}


		/* @inherit */
		bool operator== (const Rule & rule) const {
			if (this == &rule)
				return true;

			const Rbool * ptr = dynamic_cast<const Rbool *> (&rule);

			if (ptr == nullptr)
				return false;

			return operator== (*ptr);
		}

		/* @inherit */
		bool operator== (const Rbool & rbool) const {
			return _rule == rbool._rule;
		}

		/* @inherit */
		bool isValid (const Value & value) const {
			const Vbool * ptr = dynamic_cast<const Vbool *> (&value);

			if (ptr == nullptr)
				return false;

			return isValid (*ptr);
		}

		/* @inherit */
		bool isValid (const Vbool & vbool) const {
			return (vbool.getValue () & _rule) != 0;
		}
	};

}}


#endif
