#include "TestKoverage/Richman/Confee/NodeBaseCase.hpp"

#include "Richman/Confee/Exception/MergeNodesException.hpp"

#include "Richman/Confee/Node.hpp"
#include "Richman/Confee/Rbool.hpp"
#include "Richman/Confee/Subject.hpp"

#include "Richman/Exception/NotFoundException.hpp"


using Richman::Confee::Exception::MergeNodesException;

using Richman::Confee::Node;
using Richman::Confee::Rbool;
using Richman::Confee::Subject;

using Richman::Exception::NotFoundException;

using TestKoverage::Richman::Confee::NodeBaseCase;


void NodeBaseCase::run () {
	Node node1 ("node1");

	assertTrue (node1.getId () == "node1", "Node essentials; getId", __FILE__, __LINE__);
	assertEqual (0, node1.getNodesCount (), "Node essentials; getNodesCount", __FILE__, __LINE__);
	assertEqual (0, node1.getSubjectsCount (), "Node essentials; getSubjectsCount", __FILE__, __LINE__);
	assertFalse (node1.hasNode ("node2"), "Node essentials; hasNode", __FILE__, __LINE__);
	assertFalse (node1.hasSubject ("subject"), "Node essentials; hasSubject", __FILE__, __LINE__);
	assertFalse (node1 != node1, "Node essentials; inequal", __FILE__, __LINE__);

	Node * subnode1 = new Node ("subnode1");
	Subject * subject1 = new Subject ("subject1", new Rbool ());
	Node node2 ("node2");
	node2.setNode (subnode1);
	node2.setNode (subnode1);
	node2.setNode (new Node ("subnode1"));
	node2.setNode (new Node ("subnode2"));
	node2.setSubject (subject1);
	node2.setSubject (subject1);
	node2.setSubject (new Subject ("subject1", new Rbool ()));
	node2.setSubject (new Subject ("subject2", new Rbool ()));

	int cntr = 0;
	node2.forEachNode ([&cntr] (const Node & node) -> bool {
		if (cntr++ > 0)
			return false;
		return true;
	});

	cntr = 0;
	node2.forEachSubject ([&cntr] (const Subject & node) -> bool {
		if (cntr++ > 0)
			return false;
		return true;
	});


	try {
		node1.getNode ("node3");
		assertTrue (false, "Node essentials; getNode", __FILE__, __LINE__);
	} catch (NotFoundException & exception) {
		assertTrue (exception.getMessage () == "node3", "Node essentials; getNode", __FILE__, __LINE__);
	}


	try {
		node1.getSubject ("subject3");
		assertTrue (false, "Node essentials; getSubject", __FILE__, __LINE__);
	} catch (NotFoundException & exception) {
		assertTrue (exception.getMessage () == "subject3", "Node essentials; getSubject", __FILE__, __LINE__);
	}

	Node * node3 = new Node ("node3");
	Subject * subject3 = new Subject ("subject3", new Rbool ());
	node1.setNode (node3);
	node1.setSubject (subject3);

	assertTrue (node1.getNode ("node3") == *node3, "Node essentials; getNode", __FILE__, __LINE__);
	assertTrue (node1.getSubject ("subject3") == *subject3, "Node essentials; getSubject", __FILE__, __LINE__);


	Node node4 ("node4");

	Node * node5 = node4.copy ();
	assertTrue (node4 == *node5, "Node essentials; copy", __FILE__, __LINE__);
	delete node5;

	node4.setNode (new Node ("node5"));
	node4.setSubject (new Subject ("subject5", new Rbool ()));

	Node * node6 = node4.copy ();
	assertTrue (node4 == *node6, "Node essentials; copy", __FILE__, __LINE__);
	delete node6;


	Node node7 ("node7");
	Node node8 ("node8");
	assertTrue (node7 != node8, "Node essentials; equal", __FILE__, __LINE__);

	Node node9 ("node7");
	node7.setNode (new Node ("subnode"));
	assertTrue (node7 != node9, "Node essentials; equal", __FILE__, __LINE__);

	node9.setNode (new Node ("subnode1"));
	assertTrue (node7 != node9, "Node essentials; equal", __FILE__, __LINE__);

	node9.setNode (new Node ("subnode"));
	node7.setNode (new Node ("subnode1"));
	node7.setSubject (new Subject ("subject", new Rbool ()));
	assertTrue (node7 != node9, "Node essentials; equal", __FILE__, __LINE__);

	node9.setSubject (new Subject ("subject1", new Rbool ()));
	assertTrue (node7 != node9, "Node essentials; equal", __FILE__, __LINE__);


	Node node10 ("node");

	try {
		Node * merged1 = node10.merge (node10);
		assertTrue (node10 == *merged1, "Node essentials; merge", __FILE__, __LINE__);
		delete merged1;
	} catch (MergeNodesException & exception) {
		assertTrue (false, "node10 can't merge itself with itself", __FILE__, __LINE__);
	}


	Node node11 ("another node id");

	try {
		delete node10.merge (node11);
		assertTrue (false, "Node essentials; merge", __FILE__, __LINE__);
	} catch (MergeNodesException & exception) {
		assertTrue (exception.getFormer () == node10, "Node essentials; merge", __FILE__, __LINE__);
		assertTrue (exception.getLatter () == node11, "Node essentials; merge", __FILE__, __LINE__);
	}


	Node node12 ("node");
	Node node13 ("node");

	Node * merged2 = node12.merge (node13);
	assertTrue (node12 == *merged2, "Node essentials; merge", __FILE__, __LINE__);
	assertTrue (node13 == *merged2, "Node essentials; merge", __FILE__, __LINE__);
	delete merged2;

	node12.setNode (new Node ("subnode1"));
	node12.setSubject (new Subject ("subject1", new Rbool ()));

	Node * merged3 = node12.merge (node13);
	assertTrue (node12 == *merged3, "Node essentials; merge", __FILE__, __LINE__);
	assertFalse (node13 == *merged3, "Node essentials; merge", __FILE__, __LINE__);
	delete merged3;

	node13.setNode (new Node ("subnode1"));
	node13.setSubject (new Subject ("subject1", new Rbool ()));

	Node * merged4 = node12.merge (node13);
	assertTrue (node12 == *merged4, "Node essentials; merge", __FILE__, __LINE__);
	assertTrue (node13 == *merged4, "Node essentials; merge", __FILE__, __LINE__);
	delete merged4;

	node13.setNode (new Node ("subnode2"));
	node13.setSubject (new Subject ("subject2", new Rbool ()));

	Node * merged5 = node12.merge (node13);
	assertFalse (node12 == *merged5, "Node essentials; merge", __FILE__, __LINE__);
	assertTrue (node13 == *merged5, "Node essentials; merge", __FILE__, __LINE__);
	delete merged5;
}
