#include "Richman/Confee/Subject.hpp"

#include "Richman/Confee/Exception/MergeSubjectsException.hpp"

#include <memory>


using Richman::Confee::Exception::MergeSubjectsException;

using Richman::Confee::Rule;
using Richman::Confee::Subject;
using Richman::Confee::Value;

using Richman::Text::String;


Subject::~Subject () {
	delete _rule;
	delete _value;
	delete _defaultValue;

	for (auto & attribute : _attributes)
		delete attribute.second;
}


Subject * Subject::copy () const {
	std::unique_ptr<Subject> clone (new Subject (getId (), getRule ().copy (), isRequired ()));

	if (hasValue ())
		clone->setValue (getValue ().copy ());

	if (hasDefaultValue ())
		clone->setDefaultValue (getDefaultValue ().copy ());

	forEachAttribute ([&clone] (const Subject & attribute) -> bool {
		clone->setAttribute (attribute.copy ());
		return true;
	});

	return clone.release ();
}


Subject * Subject::merge (const Subject & subject) const {
	if (this == &subject)
		return copy ();

	if (getId () != subject.getId ()) {
		std::unique_ptr<Subject> former (copy ());
		std::unique_ptr<Subject> latter (subject.copy ());

		throw MergeSubjectsException (former.release (), latter.release (), "The subjects, are being merged, have incompatible identifiers", __FILE__, __LINE__);
	}

	if (getRule () != subject.getRule ()) {
		std::unique_ptr<Subject> former (copy ());
		std::unique_ptr<Subject> latter (subject.copy ());

		throw MergeSubjectsException (former.release (), latter.release (), "Trying to merge the subjects with incompatible rules", __FILE__, __LINE__);
	}

	if (hasDefaultValue () && subject.hasDefaultValue () && getDefaultValue () != subject.getDefaultValue ()) {
		std::unique_ptr<Subject> former (copy ());
		std::unique_ptr<Subject> latter (subject.copy ());

		throw MergeSubjectsException (former.release (), latter.release (), "Trying to merge the subjects with incompatible default values", __FILE__, __LINE__);
	}

	if (hasValue () && subject.hasValue () && getValue () != subject.getValue ()) {
		std::unique_ptr<Subject> former (copy ());
		std::unique_ptr<Subject> latter (subject.copy ());

		throw MergeSubjectsException (former.release (), latter.release (), "Trying to merge the subjects with incompatible values", __FILE__, __LINE__);
	}

	std::unique_ptr<Subject> merged (new Subject (getId (), getRule ().copy (), isRequired () || subject.isRequired ()));

	if (hasDefaultValue ())
		merged->setDefaultValue (getDefaultValue ().copy ());
	else if (subject.hasDefaultValue ())
		merged->setDefaultValue (subject.getDefaultValue ().copy ());

	if (hasValue ())
		merged->setValue (getValue ().copy ());
	else if (subject.hasValue ())
		merged->setValue (subject.getValue ().copy ());

	forEachAttribute ([&merged, &subject] (const Subject & attribute) -> bool {
		if (subject.hasAttribute (attribute.getId ()))
			merged->setAttribute (attribute.merge (subject.getAttribute (attribute.getId ())));
		else
			merged->setAttribute (attribute.copy ());

		return true;
	});

	subject.forEachAttribute ([&merged] (const Subject & attribute) -> bool {
		if (!merged->hasAttribute (attribute.getId ()))
			merged->setAttribute (attribute.copy ());

		return true;
	});

	return merged.release ();
}


bool Subject::operator== (const Subject & other) const {
	if (this == &other)
		return true;

	if (getId () != other.getId ())
		return false;

	if (getAttributesCount () != other.getAttributesCount ())
		return false;

	if (hasValue () != other.hasValue ())
		return false;

	if (getRule () != other.getRule ())
		return false;

	if (hasValue () && getValue () != other.getValue ())
		return false;

	for (const auto & attribute : _attributes) {
		if (!other.hasAttribute (attribute.second->getId ()) || *attribute.second != other.getAttribute (attribute.second->getId ()))
			return false;
	}

	return true;
}
