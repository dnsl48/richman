#ifndef Richman__Confee__Vbox___hpp
#define Richman__Confee__Vbox___hpp


#include "Richman/Confee/Value.hpp"

#include <memory>


namespace Richman {
namespace Confee {


	/* A Box for any externally defined value */
	template <typename T>
	class Vbox : public Value {
		std::shared_ptr<T> _box;

	public:
		/* Initializes the object with the value
		 * @value The value of the box
		 */
		Vbox (T * value) :
			_box (value)
		{}


		/* @inherit */
		Vbox<T> * copy () const {
			return new Vbox<T> (*this);
		}


		/* @inherit */
		bool operator== (const Value & value) const {
			if (this == &value)
				return true;

			const Vbox<T> * ptr = dynamic_cast<const Vbox<T> *> (&value);

			if (ptr == nullptr)
				return false;

			return operator== (*ptr);
		}


		/* @inherit */
		bool operator== (const Vbox<T> & vbox) const {
			return _box.get () == vbox._box.get ();
		}


		/* Returns the value
		 *
		 * @return The value
		 */
		const T & getValue () const {
			return *_box.get ();
		}
	};

}}


#endif
