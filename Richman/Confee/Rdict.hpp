#ifndef Richman__Confee__Rdict___hpp
#define Richman__Confee__Rdict___hpp


#include "Richman/Confee/Rule.hpp"
#include "Richman/Confee/Vdict.hpp"

#include "Richman/Text/String.hpp"

#include <map>


namespace Richman {
namespace Confee {


	/* Base implementation of the rule for checking dictionaries (Vdict) */
	class Rdict : public Rule {
		std::map<Richman::Text::String, std::pair<bool, Rule *>> _map;

	public:
		/* Simple constructor */
		Rdict () = default;


		/* Copying constructor does not exist. Use the method <copy> instead. */
		Rdict (const Rdict &) = delete;


		/* Destroys all included rules */
		~Rdict () {
			for (const auto & rulePair : _map)
				delete rulePair.second.second;
		}


		/* @inherit */
		Rdict * copy () const {
			std::unique_ptr<Rdict> holder (new Rdict ());

			for (const auto & rulePair : _map)
				holder->setRule (rulePair.first, rulePair.second.second->copy (), rulePair.second.first);

			return holder.release ();
		}


		/* @inherit */
		bool operator== (const Rule & rule) const {
			if (this == &rule)
				return true;

			const Rdict * ptr = dynamic_cast<const Rdict *> (&rule);

			if (ptr == nullptr)
				return false;

			return operator== (*ptr);
		}


		/* @inherit */
		bool operator== (const Rdict & rdict) const {
			if (this == &rdict)
				return true;

			if (_map.size () != rdict._map.size ())
				return false;

			for (const auto & rulePair : _map) {
				const auto & otherIter = rdict._map.find (rulePair.first);
				if (otherIter == rdict._map.end () || otherIter->second.first != rulePair.second.first || *rulePair.second.second != *otherIter->second.second)
					return false;
			}

			return true;
		}


		/* @inherit */
		bool isValid (const Value & value) const {
			const Vdict * ptr = dynamic_cast<const Vdict *> (&value);

			if (ptr == nullptr)
				return false;

			return isValid (*ptr);
		}


		/* @inherit */
		bool isValid (const Vdict & vdict) const {
			bool result = true;

			vdict.forEachValue ([this, &result] (const Richman::Text::String & key, const Value & value) -> bool {
				if (!hasRule (key) || !getRule (key).isValid (value)) {
					result = false;
					return false;
				}

				return true;
			});

			if (result) {
				forEachRule ([this, &result, &vdict] (const Richman::Text::String & key, const Rule & rule, bool isRequired) -> bool {
					if (isRequired) {
						if (!vdict.hasValue (key) || !rule.isValid (vdict.getValue (key))) {
							result = false;
							return false;
						}
					}

					return true;
				});
			}

			return result;
		}


		/* Checks whether the rule, identified by the passed key, is a required one
		 * @key Key of the rule
		 *
		 * @return Whether the rule, identified by the passed key, is a required one
		 */
		bool isRequiredRule (const Richman::Text::String & key) const {
			const auto & found = _map.find (key);

			if (found == _map.end ())
				return false;

			return found->second.first;
		}


		/* Checks whether a rule with the passed key exists
		 * @key Key of the rule
		 *
		 * @return Whether a rule with the passed key exists
		 */
		bool hasRule (const Richman::Text::String & key) const {
			return _map.find (key) != _map.end ();
		}


		/* Returns an instance of the rule identified by the passed key
		 * @key Key of the rule
		 *
		 * Throws <Richman::Exception::NotFoundException> If the rule does not exist
		 *
		 * @return An instance of the rule identified by the passed key
		 */
		const Rule & getRule (const Richman::Text::String & key) const {
			const auto & found = _map.find (key);

			if (found == _map.end ())
				throw Richman::Exception::NotFoundException (key, __FILE__, __LINE__);

			return *found->second.second;
		}


		/* Initializes a new rule of the dictionary, identified by the passed key
		 * @key Key of the rule
		 * @rule The rule itself
		 * @isRequired If the rule must be applied and passed in order to the whole dictionary will be a valid
		 */
		void setRule (const Richman::Text::String & key, Rule * rule, bool isRequired = false) {
			std::unique_ptr<Rule> holder (rule);

			const auto & found = _map.find (key);

			if (found != _map.end ()) {
				if (found->second.second != rule)
					delete found->second.second;

				_map.erase (found);
			}

			_map[key] = std::make_pair (isRequired, holder.release ());
		}


		/* Applies the passed callback to each rule in the dictionary
		 * @callback Closure that takes two arguments: a key and a rule
		 *
		 * Closure is going to be applied for each rule until it returns false as a result
		 */
		void forEachRule (const std::function<bool (const Richman::Text::String &, const Rule &, bool)> & callback) const {
			for (const auto & rulePair : _map) {
				if (!callback (rulePair.first, *rulePair.second.second, rulePair.second.first))
					break;
			}
		}
	};

}}

#endif
