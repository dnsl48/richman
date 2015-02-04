#ifndef Richman__Confee__Vdict___hpp
#define Richman__Confee__Vdict___hpp


#include "Richman/Confee/Value.hpp"

#include "Richman/Exception/NotFoundException.hpp"

#include "Richman/Text/String.hpp"

#include <functional>
#include <map>
#include <memory>


namespace Richman {
namespace Confee {


	/* Represents a dictionary of key->value pairs */
	class Vdict : public Value {
		std::map<Richman::Text::String, Value *> _map;

	public:
		/* Initializes included entities */
		Vdict () = default;


		/* Copying constructor does not exist. Use the method <copy> insdead */
		Vdict(const Vdict &) = delete;


		/* Destroys all included entities */
		~Vdict () {
			for (auto & valPair : _map)
				delete valPair.second;
		}


		/* @inherit */
		Vdict * copy () const {
			std::unique_ptr<Vdict> holder (new Vdict ());

			for (const auto & valPair : _map)
				holder->setValue (valPair.first, valPair.second->copy ());

			return holder.release ();
		}


		/* @inherit */
		bool operator== (const Value & value) const {
			if (this == &value)
				return true;

			const Vdict * ptr = dynamic_cast<const Vdict *> (&value);

			if (ptr == nullptr)
				return false;

			return operator== (*ptr);
		}


		/* @inherit */
		bool operator== (const Vdict & vdict) const {
			if (this == &vdict)
				return true;

			if (_map.size () != vdict._map.size ())
				return false;

			for (const auto & valPair : _map) {
				const auto & otherIter = vdict._map.find (valPair.first);
				if (otherIter == vdict._map.end () || *otherIter->second != *valPair.second)
					return false;
			}

			return true;
		}


		/* Checks whether a value with the passed key exists
		 * @key Key of the value
		 *
		 * @return Whether a value with the passed key exists
		 */
		bool hasValue (const Richman::Text::String & key) const {
			return _map.find (key) != _map.end ();
		}


		/* Returns an instance of the value identified by the passed key
		 * @key Key of the value
		 *
		 * Throws <Richman::Exception::NotFoundException> If the value does not exist
		 *
		 * @return An instance of the value identified by the passed key
		 */
		const Value & getValue (const Richman::Text::String & key) const {
			const auto & found = _map.find (key);

			if (found == _map.end ())
				throw Richman::Exception::NotFoundException (key, __FILE__, __LINE__);

			return *found->second;
		}


		/* Initializes a new value of the dictionary, identified by the passed key
		 * @key Key of the value
		 * @value The value itself
		 */
		void setValue (const Richman::Text::String & key, Value * value) {
			std::unique_ptr<Value> holder (value);

			const auto & found = _map.find (key);

			if (found != _map.end ()) {
				if (found->second != value)
					delete found->second;
				_map.erase (found);
			}

			_map[key] = holder.release ();
		}


		/* Applies the passed callback to each value in the dictionary
		 * @callback Closure that takes two arguments: a key and a value
		 *
		 * Closure is going to be applied for each value until it returns false as a result
		 */
		void forEachValue (const std::function<bool (const Richman::Text::String &, const Value &)> & callback) const {
			for (const auto & valPair : _map) {
				if (!callback (valPair.first, *valPair.second))
					break;
			}
		}
	};

}}

#endif
