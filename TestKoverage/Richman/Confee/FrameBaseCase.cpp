#include "TestKoverage/Richman/Confee/FrameBaseCase.hpp"


#include "Richman/Confee/Node.hpp"
#include "Richman/Confee/Frame.hpp"

#include "Richman/Exception/NotFoundException.hpp"


using Richman::Confee::Node;
using Richman::Confee::Frame;

using Richman::Exception::NotFoundException;

using TestKoverage::Richman::Confee::FrameBaseCase;


void FrameBaseCase::run () {
	Frame frame;

	Node * node1 = new Node ("node1");

	frame.setNode (node1);
	frame.setNode (node1);

	assertTrue (frame.getNode ("node1") == *node1, "Frame essentials; getNode", __FILE__, __LINE__);
	assertTrue (frame.hasNode ("node1"), "Frame essentials; hasNode", __FILE__, __LINE__);

	frame.setNode (new Node ("node1"));

	try {
		frame.getNode ("node2");
		assertTrue (false, "Frame essentials; getNode", __FILE__, __LINE__);
	} catch (NotFoundException & exception) {
		assertTrue (exception.getMessage () == "node2", "Frame essentials; getNode", __FILE__, __LINE__);
	}
}
