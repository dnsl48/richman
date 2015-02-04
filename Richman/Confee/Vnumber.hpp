#ifndef Richman__Confee__Vnumber___hpp
#define Richman__Confee__Vnumber___hpp


#include "Richman/Confee/Value.hpp"


namespace Richman {
namespace Confee {


	/* Represents a numeric value */
	class Vnumber : public Value {
	public:
		typedef long double Numeric;

	private:
		Numeric _value = 0.0L;

	public:
		/* Initializes the object with a number
		 * @value The value
		 */
		Vnumber (Numeric value):
			_value (value)
		{}


		/* @inherit */
		Vnumber * copy () const {
			return new Vnumber (_value);
		}


		/* @inherit */
		bool operator== (const Value & value) const {
			if (this == &value)
				return true;

			const Vnumber * ptr = dynamic_cast<const Vnumber *> (&value);

			if (ptr == nullptr)
				return false;

			return operator== (*ptr);
		}


		/* @inherit */
		bool operator== (const Vnumber & value) const {
			if (this == &value)
				return true;

			return _value == value.getNumber ();
		}


		/* Returns the value
		 *
		 * @return The value
		 */
		const Numeric & getNumber () const {
			return _value;
		}
	};

}}


#endif
