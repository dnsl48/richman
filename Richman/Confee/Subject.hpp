#ifndef Richman__Confee__Subject___hpp
#define Richman__Confee__Subject___hpp


#include "Richman/Confee/Rule.hpp"
#include "Richman/Confee/Value.hpp"

#include "Richman/Exception/NotFoundException.hpp"
#include "Richman/Exception/UninitializedException.hpp"

#include "Richman/Text/String.hpp"

#include <cstddef>
#include <functional>
#include <map>
#include <memory>


namespace Richman {
namespace Confee {


	/* Represents a single value of a configuration */
	class Subject {
		Richman::Text::String _id;

		Richman::Confee::Rule * _rule;

		bool _isRequired;

		Richman::Confee::Value * _value = nullptr;

		Richman::Confee::Value * _defaultValue = nullptr;

		std::map<Richman::Text::String, Subject *> _attributes;


	public:
		/* Initializes the subject with its identifier, rule and requirement
		 * @identifier The identifier of the subject
		 * @rule The rule that should check the values of the subject
		 * @isRequired Whether the subject must be filled by a value
		 */
		Subject (const Richman::Text::String & identifier, Rule * rule, bool isRequired = false) :
			_id (identifier),
			_rule (rule),
			_isRequired (isRequired)
		{}


		/* Copying constructor does not exist. Use the method <copy> instead */
		Subject (const Subject &) = delete;


		/* Destroys all included entities */
		~Subject ();


		/* Makes a new instance of the subject with all copied guts
		 *
		 * @return A clone of the subject
		 */
		Subject * copy () const;


		/* Merges the subject with a passed one and produces a new subject that contains guts of the both
		 *
		 * @return An instance of a new subject
		 */
		Subject * merge (const Subject &) const;


		/* Returns the identifier of the subject
		 *
		 * @return The identifier of the subject
		 */
		const Richman::Text::String & getId () const {
			return _id;
		}


		/* Returns whether the subject must be filled with a value
		 *
		 * @return Whether the subject must be filled with a value
		 */
		const bool & isRequired () const {
			return _isRequired;
		}


		/* Returns the rule that checks subject's values
		 *
		 * @return The rule that checks subject's values
		 */
		const Richman::Confee::Rule & getRule () const {
			return *_rule;
		}


		/* Returns the amount of the set attributes
		 *
		 * @return The amount of the set attributes
		 */
		std::size_t getAttributesCount () const {
			return _attributes.size ();
		}


		/* Returns whether the subject has an attribute with the passed identifier
		 * @identifier The identifier of the attribute to be checked
		 *
		 * @return Whether the subject has an attribute with the passed identifier
		 */
		bool hasAttribute (const Richman::Text::String & identifier) const {
			return _attributes.find (identifier) != _attributes.end ();
		}


		/* Returns a link on the attribute that has the identifier passed
		 * @identifier Identifier of the attribute
		 *
		 * Throws <Richman::Exception::NotFoundException> if the attribute does not exist
		 *
		 * @return Link on the attribute
		 */
		const Subject & getAttribute (const Richman::Text::String & identifier) const {
			const auto & found = _attributes.find (identifier);

			if (found == _attributes.end ())
				throw Richman::Exception::NotFoundException (identifier, __FILE__, __LINE__);

			return *found->second;
		}


		/* Adds new attribute. The subject can have any number of other subjects as its attributes.
		 * @attribute Attribute instance
		 *
		 * If another attribute with the same identifier already exists it is going to be destroyed
		 */
		void setAttribute (Subject * attribute) {
			std::unique_ptr<Subject> attr (attribute);

			const auto & found = _attributes.find (attribute->getId ());

			if (found != _attributes.end ()) {
				if (found->second != attribute)
					delete found->second;
				_attributes.erase (found);
			}

			_attributes[attribute->getId ()] = attr.release ();
		}


		/* Applies the passed closure to each attribute
		 * @callback Callback that consumes a link on an attribute
		 *
		 * Callback will be applied to each attribute until it returns false as a result
		 */
		void forEachAttribute (const std::function<bool (const Subject &)> & callback) const {
			for (const auto & attribute : _attributes) {
				if (!callback (*attribute.second))
					break;
			}
		}


		/* Checks whether the subject has a value set
		 *
		 * @return Whether the subject has a value set
		 */
		bool hasValue () const {
			return _value != nullptr;
		}


		/* Checks whether the subject has the default value
		 *
		 * @return Whether the subject has the default value
		 */
		bool hasDefaultValue () const {
			return _defaultValue != nullptr;
		}


		/* Sets the passed value as the value of the subject
		 * @value The value to be set
		 *
		 * If the subject already has another value, it is going to be destroyed
		 */
		void setValue (Value * value) {
			if (_value != value)
				delete _value;

			_value = value;
		}


		/* Sets the passed value as the default value of the subject
		 * @value The value to be set
		 *
		 * If the subject already has another default value, it is going to be destroyed
		 */
		void setDefaultValue (Value * value) {
			if (_defaultValue != value)
				delete _defaultValue;

			_defaultValue = value;
		}


		/* Returns the instance of the subject's value
		 *
		 * Throws <Richman::Exception::UninitializedException> if the value hasn't been set
		 *
		 * @return The instance of the subject's value
		 */
		const Value & getValue () const {
			if (_value == nullptr)
				throw Richman::Exception::UninitializedException ("Value hasn't been initialized yet", __FILE__, __LINE__);

			return *_value;
		}


		/* Returns the instance of the subject's default value
		 *
		 * Throws <Richman::Exception::UninitializedException> if the default value hasn't been set
		 *
		 * @return The instance of the subject's default value
		 */
		const Value & getDefaultValue () const {
			if (_defaultValue == nullptr)
				throw Richman::Exception::UninitializedException ("Default value hasn't been initialized yet", __FILE__, __LINE__);

			return *_defaultValue;
		}


		/* Checks whether the subject equals to another one
		 *
		 * @return Whether the subject equals to another one
		 */
		bool operator== (const Subject &) const;


		/* Checks whether the subject does not equal to another one
		 *
		 * @return Whether the subject does not equal to another one
		 */
		bool operator!= (const Subject & subject) const {
			return !operator== (subject);
		}
	};

}}


#endif
