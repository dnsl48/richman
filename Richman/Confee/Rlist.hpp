#ifndef Richman__Confee__Rlist___hpp
#define Richman__Confee__Rlist___hpp


#include "Richman/Confee/Rule.hpp"
#include "Richman/Confee/Vlist.hpp"

#include <cstddef>
#include <functional>
#include <map>


namespace Richman {
namespace Confee {


	/* Base implementation of the rule for checking lists (Vlist) */
	class Rlist : public Rule {
		bool _minSizeExists = false;
		bool _maxSizeExists = false;

		std::size_t _minSize = 0;
		std::size_t _maxSize = 0;

		Rule * _defaultRule = nullptr;
		std::map<std::size_t, Rule *> _rules;

	public:
		/* Simple constructor */
		Rlist () = default;


		/* Copying constructor does not exist. Use the method <copy> instead. */
		Rlist (const Rlist &) = delete;


		/* Destroys all included rules */
		~Rlist () {
			delete _defaultRule;

			for (auto & rulePair : _rules)
				delete rulePair.second;
		}


		/* @inherit */
		Rlist * copy () const {
			std::unique_ptr<Rlist> hatchery (new Rlist ());

			if (_minSizeExists)
				hatchery->setMinSize (_minSize);

			if (_maxSizeExists)
				hatchery->setMaxSize (_maxSize);

			if (_defaultRule != nullptr)
				hatchery->setDefaultRule (_defaultRule->copy ());

			for (const auto & rulePair : _rules)
				hatchery->setRule (rulePair.first, rulePair.second->copy ());

			return hatchery.release ();
		}


		/* @inherit */
		bool operator== (const Rule & rule) const {
			if (this == &rule)
				return true;

			const Rlist * ptr = dynamic_cast<const Rlist *> (&rule);

			if (ptr == nullptr)
				return false;

			return operator== (*ptr);
		}


		/* @inherit */
		bool operator== (const Rlist & rlist) const {
			if (this == &rlist)
				return true;

			if (_minSizeExists != rlist._minSizeExists || _minSize != rlist._minSize)
				return false;

			if (_maxSizeExists != rlist._maxSizeExists || _maxSize != rlist._maxSize)
				return false;

			if ((_defaultRule != nullptr) != (rlist._defaultRule != nullptr))
				return false;

			if (_rules.size () != rlist._rules.size ())
				return false;

			if (_defaultRule != nullptr && rlist._defaultRule != nullptr && *_defaultRule != *rlist._defaultRule)
				return false;

			for (const auto & rulePair : _rules) {
				const auto & iter = rlist._rules.find (rulePair.first);

				if (iter == rlist._rules.end () || *rulePair.second != *iter->second)
					return false;
			}

			return true;
		}


		/* Makes restriction on the minimal size of a list
		 * @size Minimal amount of values in a list
		 */
		void setMinSize (std::size_t size) {
			_minSizeExists = true;
			_minSize = size;
		}


		/* Makes restriction on the maximal size of a list
		 * @size Maximal amount of values in a list
		 */
		void setMaxSize (std::size_t size) {
			_maxSizeExists = true;
			_maxSize = size;
		}


		/* Sets the default rule that will be applied to any value until its specific rule is set
		 * @rule An instance of the default rule
		 */
		void setDefaultRule (Rule * rule) {
			if (_defaultRule != rule)
				delete _defaultRule;

			_defaultRule = rule;
		}


		/* Sets a specific rule for some index of a list
		 * @index Index of a list
		 * @rule An instance of the specific rule
		 */
		void setRule (const std::size_t & index, Rule * rule) {
			std::unique_ptr<Rule> holder (rule);

			const auto & found = _rules.find (index);

			if (found != _rules.end ()) {
				if (found->second != rule)
					delete found->second;
				_rules.erase (found);
			}

			_rules[index] = holder.release ();
		}


		/* Applies the passed callback to each rule
		 * @callback Closure that takes a rule
		 *
		 * Closure is going to be applied for each rule until it returns false as a result
		 */
		void forEachRule (const std::function<bool (const Rule &)> & callback) const {
			for (const auto & rulePair : _rules) {
				if (!callback (*rulePair.second))
					break;
			}
		}


		/* @inherit */
		bool isValid (const Value & value) const {
			const Vlist * ptr = dynamic_cast<const Vlist *> (&value);

			if (ptr == nullptr)
				return false;

			return isValid (*ptr);
		}


		/* @inherit */
		bool isValid (const Vlist & vlist) const {
			if (_minSizeExists && vlist.length () < _minSize)
				return false;

			if (_maxSizeExists && vlist.length () > _maxSize)
				return false;

			bool result = true;
			std::size_t counter = 0;
			vlist.forEachValue ([this, &counter, &result] (const Value & value) {
				const auto & iter = _rules.find (counter++);

				if (iter != _rules.end ()) {
					if (!iter->second->isValid (value))
						result = false;

				} else if (_defaultRule != nullptr && !_defaultRule->isValid (value))
					result = false;

				return result;
			});

			return result;
		}
	};

}}


#endif
