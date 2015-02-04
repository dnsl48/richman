#ifndef Richman__Confee__Vbool___hpp
#define Richman__Confee__Vbool___hpp


#include "Richman/Confee/Value.hpp"


namespace Richman {
namespace Confee {


	/* Base implementation of the value for booleans and the null */
	class Vbool : public Value {
	public:
		enum Bool : char {True = 1, False = 2, Null = 4};

	private:
		Bool _value = Null;

	public:
		/* Initializes the object with the value
		 * @value Should pick a single value from the enum <Bool>
		 */
		Vbool (const Bool & value = Null) :
			_value (value)
		{}


		/* Returns the value
		 *
		 * @return The value
		 */
		const Bool & getValue () const {
			return _value;
		}


		/* @inherit */
		Vbool * copy () const {
			return new Vbool (_value);
		}


		/* @inherit */
		bool operator== (const Value & value) const {
			if (this == &value)
				return true;

			const Vbool * ptr = dynamic_cast<const Vbool *> (&value);

			if (ptr == nullptr)
				return false;

			return operator== (*ptr);
		}


		/* @inherit */
		bool operator== (const Vbool & vbool) const {
			return getValue () == vbool.getValue ();
		}
	};

}}


#endif
