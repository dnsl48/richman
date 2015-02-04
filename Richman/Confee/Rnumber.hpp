#ifndef Richman__Confee__Rnumber___hpp
#define Richman__Confee__Rnumber___hpp


#include "Richman/Confee/Rule.hpp"
#include "Richman/Confee/Vnumber.hpp"

#include <memory>


namespace Richman {
namespace Confee {


	/* Base implementation of the rule for checking numbers */
	class Rnumber : public Rule {
		bool _minExists = false;
		bool _maxExists = false;

		Vnumber::Numeric _min = 0;
		Vnumber::Numeric _max = 0;

	public:
		/* Sets the minimal value for a number
		 * @limit Minimal value
		 */
		void setMinLimit (Vnumber::Numeric limit) {
			_minExists = true;
			_min = limit;
		}


		/* Sets the maximal value for a number
		 * @limit Maximal value
		 */
		void setMaxLimit (Vnumber::Numeric limit) {
			_maxExists = true;
			_max = limit;
		}


		/* @inherit */
		Rnumber * copy () const {
			std::unique_ptr<Rnumber> hatchery (new Rnumber ());

			if (_minExists)
				hatchery->setMinLimit (_min);

			if (_maxExists)
				hatchery->setMaxLimit (_max);

			return hatchery.release ();
		}


		/* @inherit */
		bool operator== (const Rule & rule) const {
			if (this == &rule)
				return true;

			const Rnumber * ptr = dynamic_cast<const Rnumber *> (&rule);

			if (ptr == nullptr)
				return false;

			return operator== (*ptr);
		}


		/* @inherit */
		bool operator== (const Rnumber & rule) const {
			if (this == &rule)
				return true;

			return _minExists == rule._minExists && _maxExists == rule._maxExists && _min == rule._min && _max == rule._max;
		}


		/* @inherit */
		bool isValid (const Value & value) const {
			const Vnumber * ptr = dynamic_cast<const Vnumber *> (&value);

			if (ptr == nullptr)
				return false;

			return isValid (*ptr);
		}


		/* @inherit */
		bool isValid (const Vnumber & value) const {
			if (_minExists && value.getNumber () < _min)
				return false;

			if (_maxExists && value.getNumber () > _max)
				return false;

			return true;
		}
	};

}}

#endif
