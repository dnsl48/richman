#ifndef Richman__Confee__Vlist___hpp
#define Richman__Confee__Vlist___hpp


#include "Richman/Confee/Value.hpp"

#include <cstddef>
#include <functional>
#include <list>
#include <memory>


namespace Richman {
namespace Confee {


	/* Represents a list of values */
	class Vlist : public Value {
		std::list<Value *> _list;

	public:
		/* Initializes included entities */
		Vlist () = default;


		/* Copying constructor does not exist. Use the method <copy> insdead */
		Vlist (const Vlist &) = delete;


		/* Destroys all included entities */
		~Vlist () {
			for (Value * value : _list)
				delete value;
		}


		/* @inherit */
		Vlist * copy () const {
			std::unique_ptr<Vlist> holder (new Vlist ());

			for (const Value * value : _list)
				holder->push (value->copy ());

			return holder.release ();
		}


		/* @inherit */
		bool operator== (const Value & value) const {
			if (this == &value)
				return true;

			const Vlist * ptr = dynamic_cast<const Vlist *> (&value);

			if (ptr == nullptr)
				return false;

			return operator== (*ptr);
		}


		/* @inherit */
		bool operator== (const Vlist & vlist) const {
			if (this == &vlist)
				return true;

			if (length () != vlist.length ())
				return false;

			for (const Value * value : _list) {
				bool flag = false;

				vlist.forEachValue ([&value, &flag] (const Value & val) {
					if (val == *value) {
						flag = true;
						return false;
					}

					return true;
				});

				if (!flag)
					return false;
			}

			return true;
		}


		/* Returns the amount of elements in the list
		 *
		 * @return The amount of elements in the list
		 */
		std::size_t length () const {
			return _list.size ();
		}


		/* Applies the passed callback to each value in the list
		 * @callback Closure that takes a value as the argument
		 *
		 * Closure is going to be applied for each value until it returns false as a result
		 */
		void forEachValue (const std::function<bool (const Value &)> & callback) const {
			for (const Value * value : _list) {
				if (!callback (*value))
					break;
			}
		}

		/* Appends the value to the list
		 * @element The element to be appended
		 */
		void push (Value * element) {
			_list.push_back (element);
		}
	};

}}

#endif
