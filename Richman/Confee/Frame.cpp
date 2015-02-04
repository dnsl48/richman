#include "Richman/Confee/Frame.hpp"

#include "Richman/Exception/NotFoundException.hpp"

#include <memory>


using Richman::Confee::Frame;
using Richman::Confee::Node;


Frame::~Frame () {
	for (const auto & nodePair : _nodes)
		delete nodePair.second;
}


void Frame::setNode (Node * node) {
	std::unique_ptr<Node> holder (node);

	const auto & found = _nodes.find (node->getId ());

	if (found != _nodes.end ()) {
		if (found->second != node)
			delete found->second;
		_nodes.erase (found);
	}

	_nodes[node->getId ()] = holder.release ();
}


bool Frame::hasNode (const Richman::Text::String & identifier) const {
	return _nodes.find (identifier) != _nodes.end ();
}


const Node & Frame::getNode (const Richman::Text::String & identifier) const {
	const auto & found = _nodes.find (identifier);

	if (found == _nodes.end ())
		throw Richman::Exception::NotFoundException (identifier, __FILE__, __LINE__);

	return *found->second;
}
