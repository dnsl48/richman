#ifndef Richman__Confee__Node___hpp
#define Richman__Confee__Node___hpp


#include "Richman/Confee/Subject.hpp"

#include "Richman/Text/String.hpp"

#include <cstddef>
#include <functional>
#include <map>


namespace Richman {
namespace Confee {


	/* Represents a bit of configuration
	 *
	 * Can have a list of included nodes as well as a list of included subjects.
	 * Nodes imply nested configuration levels whereas subjects are configured values.
	 */
	class Node {
		Richman::Text::String _id;

		std::map<Richman::Text::String, Node *> _nodes;
		std::map<Richman::Text::String, Subject *> _subjects;

	public:
		/* Initializes the node by its identifier */
		Node (const Richman::Text::String & identifier) :
			_id (identifier)
		{}


		/* Copying constructor does not exist. Use the method <copy> instead */
		Node (const Node &) = delete;


		/* Destroys all included nodes and subjects */
		~Node ();


		/* Returns the identifier of the node
		 *
		 * @return Node identifier
		 */
		const Richman::Text::String & getId () const {
			return _id;
		}


		/* Returns the amount of the included nodes
		 *
		 * @return The amount of the included nodes
		 */
		std::size_t getNodesCount () const {
			return _nodes.size ();
		}


		/* Returns the amount of the included subjects
		 *
		 * @return The amount of the included subjects
		 */
		std::size_t getSubjectsCount () const {
			return _subjects.size ();
		}


		/* Adds new included node
		 * @node Included node instance
		 *
		 * If another node with the same identifier already exists it is going to be destroyed
		 */
		void setNode (Node * node);


		/* Adds new subject
		 * @subject Subject instance
		 *
		 * If another subject with the same identifier already exists it is going to be destroyed
		 */
		void setSubject (Subject * subject);


		/* Returns a link on the included node that has the identifier passed
		 * @identifier Identifier of the included node
		 *
		 * Throws <Richman::Exception::NotFoundException> if the subnode does not exist
		 *
		 * @return Link on the included node
		 */
		const Node & getNode (const Richman::Text::String & identifier) const;


		/* Returns a link on the subject that has the identifier passed
		 * @identifier Identifier of the subject
		 *
		 * Throws <Richman::Exception::NotFoundException> if the subject does not exist
		 *
		 * @return Link on the subject
		 */
		const Subject & getSubject (const Richman::Text::String & identifier) const;


		/* Checks whether an included node with the passed identifier exist
		 * @identifier Identifier of an included node
		 *
		 * @return Whether an included node with the passed identifier exist
		 */
		bool hasNode (const Richman::Text::String & identifier) const {
			return _nodes.find (identifier) != _nodes.end ();
		}


		/* Checks whether a subject with the passed identifier exist
		 * @identifier Identifier of a subject
		 *
		 * @return Whether a subject with the passed identifier exist
		 */
		bool hasSubject (const Richman::Text::String & identifier) const {
			return _subjects.find (identifier) != _subjects.end ();
		}


		/* Applies the passed closure to each included node
		 * @callback Callback that consumes a link on a node
		 *
		 * Callback will be applied to each included node until it returns false as a result
		 */
		void forEachNode (const std::function<bool (const Node &)> & callback) const {
			for (const auto & nodePair : _nodes) {
				if (!callback (*nodePair.second))
					break;
			}
		}


		/* Applies the passed closure to each subject
		 * @callback Callback that consumes a link on a subject
		 *
		 * Callback will be applied to each subject until it returns false as a result
		 */
		void forEachSubject (const std::function<bool (const Subject &)> & callback) const {
			for (const auto & subjectPair : _subjects) {
				if (!callback (*subjectPair.second))
					break;
			}
		}


		/* Makes a new instance of the node with all copied guts
		 *
		 * @return A clone of the node
		 */
		Node * copy () const;


		/* Merges the node with a passed one and produces a new node that contains guts of the both
		 *
		 * @return An instance of a new node
		 */
		Node * merge (const Node &) const;


		/* Checks whether the node equals to a passed one
		 *
		 * @return Whether the node equals to a passed one
		 */
		bool operator== (const Node &) const;


		/* Checks whether the node does not equal to a passed one
		 *
		 * @return Whether the node does not equal to a passed one
		 */
		bool operator!= (const Node & node) const {
			return !operator==(node);
		}
	};

}}


#endif
