#ifndef Richman__Confee__Rbox___hpp
#define Richman__Confee__Rbox___hpp


#include "Richman/Confee/Rule.hpp"
#include "Richman/Confee/Vbox.hpp"


namespace Richman {
namespace Confee {


	/* Base implementation of the rule for checking Vbox */
	template <typename T>
	class Rbox : public Rule {
	public:
		/* @inherit */
		Rbox<T> * copy () const {
			return new Rbox<T> ();
		}


		/* @inherit */
		bool operator== (const Rule & rule) const {
			if (this == &rule)
				return true;

			const Rbox<T> * ptr = dynamic_cast<const Rbox<T> *> (&rule);

			if (ptr == nullptr)
				return false;

			return operator== (*ptr);
		}


		/* @inherit */
		bool operator== (const Rbox<T> & rbox) const {
			return true;
		}


		/* @inherit */
		bool isValid (const Value & value) const {
			return dynamic_cast<const Vbox<T> *> (&value) != nullptr;
		}
	};

}}


#endif
