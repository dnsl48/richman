#include "Richman/Confee/Node.hpp"

#include "Richman/Confee/Exception/MergeNodesException.hpp"

#include "Richman/Exception/NotFoundException.hpp"

#include <memory>


using Richman::Confee::Node;
using Richman::Confee::Subject;


Node::~Node () {
	for (auto & nodePair : _nodes)
		delete nodePair.second;

	for (auto & subjectPair : _subjects)
		delete subjectPair.second;
}


void Node::setNode (Node * node) {
	std::unique_ptr<Node> holder (node);

	const auto & found = _nodes.find (node->getId ());

	if (found != _nodes.end ()) {
		if (found->second != node)
			delete found->second;
		_nodes.erase (found);
	}

	_nodes[node->getId ()] = holder.release ();
}


void Node::setSubject (Subject * subject) {
	std::unique_ptr<Subject> holder (subject);

	const auto & found = _subjects.find (subject->getId ());

	if (found != _subjects.end ()) {
		if (found->second != subject)
			delete found->second;
		_subjects.erase (found);
	}

	_subjects[subject->getId ()] = holder.release ();
}


const Node & Node::getNode (const Richman::Text::String & identifier) const {
	const auto & found = _nodes.find (identifier);

	if (found == _nodes.end ())
		throw Richman::Exception::NotFoundException (identifier, __FILE__, __LINE__);

	return *found->second;
}


const Subject & Node::getSubject (const Richman::Text::String & identifier) const {
	const auto & found = _subjects.find (identifier);

	if (found == _subjects.end ())
		throw Richman::Exception::NotFoundException (identifier, __FILE__, __LINE__);

	return *found->second;
}


Node * Node::copy () const {
	std::unique_ptr<Node> clone (new Node (getId ()));

	for (const auto & nodePair : _nodes)
		clone->setNode (nodePair.second->copy ());

	for (const auto & subjectPair : _subjects)
		clone->setSubject (subjectPair.second->copy ());

	return clone.release ();
}


Node * Node::merge (const Node & node) const {
	if (this == &node)
		return copy ();


	if (getId () != node.getId ()) {
		std::unique_ptr<Node> former (copy ());
		std::unique_ptr<Node> latter (node.copy ());

		throw Richman::Confee::Exception::MergeNodesException (former.release (), latter.release (), "The nodes, are being merged, have incompatible identifiers", __FILE__, __LINE__);
	}


	std::unique_ptr<Node> merged (new Node (getId ()));


	forEachNode ([&merged, &node] (const Node & inode) {
		if (node.hasNode (inode.getId ()))
			merged->setNode (inode.merge (node.getNode (inode.getId ())));
		else
			merged->setNode (inode.copy ());

		return true;
	});

	node.forEachNode ([&merged] (const Node & node) {
		if (!merged->hasNode (node.getId ()))
			merged->setNode (node.copy ());

		return true;
	});


	forEachSubject ([&merged, &node] (const Subject & subject) {
		if (node.hasSubject (subject.getId ()))
			merged->setSubject (subject.merge (node.getSubject (subject.getId ())));
		else
			merged->setSubject (subject.copy ());

		return true;
	});

	node.forEachSubject ([&merged] (const Subject & subject) {
		if (!merged->hasSubject (subject.getId ()))
			merged->setSubject (subject.copy ());

		return true;
	});


	return merged.release ();
}



bool Node::operator== (const Node & node) const {
	if (this == &node)
		return true;

	if (getId () != node.getId ())
		return false;

	if (getNodesCount () != node.getNodesCount ())
		return false;

	if (getSubjectsCount () != node.getSubjectsCount ())
		return false;

	for (const auto & nodePair : _nodes) {
		if (!node.hasNode (nodePair.first) || node.getNode (nodePair.first) != *nodePair.second)
			return false;
	}

	for (const auto & subjectPair : _subjects) {
		if (!node.hasSubject (subjectPair.first) || node.getSubject (subjectPair.first) != *subjectPair.second)
			return false;
	}

	return true;
}
