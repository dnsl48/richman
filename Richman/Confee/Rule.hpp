#ifndef Richman__Confee__Rule___hpp
#define Richman__Confee__Rule___hpp


#include "Richman/Confee/Value.hpp"


namespace Richman {
namespace Confee {


	/* Represents a rule that can check values by some included rules */
	class Rule {
	public:
		/* Does nothing */
		virtual ~Rule () {}


		/* Makes a new copy of the rule and returns it
		 *
		 * @return A cloned instance of the rule
		 */
		virtual Rule * copy () const = 0;


		/* Checks whether the rule equals to the passed one
		 *
		 * @return Whether the rule equals to the passed one
		 */
		virtual bool operator== (const Rule &) const = 0;


		/* Checks whether the rule does not equal to the passed one
		 * @rule An instance of the rule to perform the check with
		 *
		 * @return Whether the rule does not equal to the passed one
		 */
		virtual bool operator!= (const Rule & rule) const {
			return !operator== (rule);
		}


		/* Checks whether the passed value meets the rule
		 *
		 * @return Whether the passed value meets the rule
		 */
		virtual bool isValid (const Value &) const = 0;
	};

}}


#endif
