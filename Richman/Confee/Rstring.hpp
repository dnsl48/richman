#ifndef Richman__Confee__Rstring___hpp
#define Richman__Confee__Rstring___hpp


#include "Richman/Confee/Rule.hpp"
#include "Richman/Confee/Vstring.hpp"


namespace Richman {
namespace Confee {


	/* Base implementation of the rule for checking strings */
	class Rstring : public Rule {
	public:
		/* @inherit */
		Rstring * copy () const {
			return new Rstring ();
		}


		/* @inherit */
		bool operator== (const Rule & rule) const {
			if (this == &rule)
				return true;

			const Rstring * ptr = dynamic_cast<const Rstring *> (&rule);

			if (ptr == nullptr)
				return false;

			return operator== (*ptr);
		}


		/* @inherit */
		bool operator== (const Rstring & rule) const {
			return true;
		}


		/* @inherit */
		bool isValid (const Value & value) const {
			const Vstring * ptr = dynamic_cast<const Vstring *> (&value);

			if (ptr == nullptr)
				return false;

			return isValid (*ptr);
		}


		/* @inherit */
		bool isValid (const Vstring & value) const {
			return true;
		}
	};

}}


#endif
