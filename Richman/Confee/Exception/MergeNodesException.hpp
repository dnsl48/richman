#ifndef Richman__Confee__Exception__MergeNodesException___hpp
#define Richman__Confee__Exception__MergeNodesException___hpp


#include "Richman/Confee/Exception/ConfeeException.hpp"
#include "Richman/Confee/Node.hpp"

#include "Richman/Text/String.hpp"

#include <cstddef>
#include <memory>


namespace Richman {
namespace Confee {
namespace Exception {

	/* Represents exceptions that could be thrown by the algorithm merging two nodes
	 *
	 * If two nodes aren't appropriate to be merged by some reasons, MergeNodesException will be thrown
	 * initialized by appropriate message and copies of nodes that was being merged.
	 */
	class MergeNodesException : public ConfeeException {
		std::shared_ptr<Node> _former;
		std::shared_ptr<Node> _latter;

	public:
		/* Initializes the instance by copies of two nodes, error message and its place
		 * @former Copy of the former node that was being merged
		 * @latter Copy of the latter node that was being merged
		 * @message The message describing the error
		 * @file The name of a file produced the exception
		 * @line The number of a line produced the exception
		 */
		MergeNodesException (Node * former, Node * latter, Text::String && message, Text::String && file, std::size_t line):
			ConfeeException (message, file, line),
			_former (former),
			_latter (latter)
		{}


		/* Getter for the former node
		 *
		 * @return The former node that was being merged
		 */
		const Node & getFormer () const {
			return *_former.get ();
		}


		/* Getter for the latter node
		 *
		 * @return The latter node that was being merged
		 */
		const Node & getLatter () const {
			return *_latter.get ();
		}
	};

}}}


#endif
