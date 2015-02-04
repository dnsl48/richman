#ifndef Richman__Confee__Frame___hpp
#define Richman__Confee__Frame___hpp


#include "Richman/Confee/Node.hpp"

#include "Richman/Text/String.hpp"

#include <map>


namespace Richman {
namespace Confee {


	/* The highest level of the configuration is a Frame that contains a number of nodes */
	class Frame {
		std::map<Richman::Text::String, Node *> _nodes;


	public:
		/* Default constructor does nothing */
		Frame () = default;


		/* Copying constructor does not exist */
		Frame (const Frame &) = delete;


		/* Destroys all the nodes when the frame is being destructed */
		~Frame ();


		/* Adds a new node to the frame. If there already is a node with the same name, the old one will be destroyed */
		void setNode (Node *);


		/* Checks whether a node with the passed identifier exists in the frame
		 *
		 * @return Whether a node with the passed identifier exists in the frame
		 */
		bool hasNode (const Richman::Text::String &) const;


		/* Returns a node that has an identifier similar to the passed one
		 *
		 * @return An instance of a node that has an identifier similar to the passed one
		 */
		const Node & getNode (const Richman::Text::String &) const;
	};

}}


#endif
