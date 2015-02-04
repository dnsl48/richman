#ifndef Richman__Confee__Vstring___hpp
#define Richman__Confee__Vstring___hpp


#include "Richman/Confee/Value.hpp"

#include "Richman/Text/String.hpp"


namespace Richman {
namespace Confee {


	/* Represents a string value */
	class Vstring : public Value {
		Richman::Text::String _string;

	public:
		/* Initializes the object with a string value
		 * @string The value
		 */
		Vstring (const Richman::Text::String & string):
			_string (string)
		{}


		/* Returns the value
		 *
		 * @return The value
		 */
		const Richman::Text::String & getString () const {
			return _string;
		}


		/* @inherit */
		Vstring * copy () const {
			return new Vstring (_string);
		}


		/* @inherit */
		bool operator== (const Value & value) const {
			if (this == &value)
				return true;

			const Vstring * ptr = dynamic_cast<const Vstring *> (&value);

			if (ptr == nullptr)
				return false;

			return operator== (*ptr);
		}


		/* @inherit */
		bool operator== (const Vstring & value) const {
			if (this == &value)
				return true;

			return _string == value.getString ();
		}
	};

}}


#endif
