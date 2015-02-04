#ifndef Richman__Confee__Value___hpp
#define Richman__Confee__Value___hpp


namespace Richman {
namespace Confee {


	/* Represents a single value of a configuration */
	class Value {
	public:
		/* Does nothing */
		virtual ~Value () {}


		/* Makes a new copy of the value and returns it
		 *
		 * @return A cloned instance of the value
		 */
		virtual Value * copy () const = 0;


		/* Checks whether the value equals to the passed one
		 *
		 * @return Whether the value equals to the passed one
		 */
		virtual bool operator== (const Value &) const = 0;


		/* Checks whether the value does not equal to the passed one
		 * @value An instance of the value to perform the check with
		 *
		 * @return Whether the value does not equal to the passed one
		 */
		virtual bool operator!= (const Value & value) const {
			return !operator== (value);
		}
	};

}}


#endif
