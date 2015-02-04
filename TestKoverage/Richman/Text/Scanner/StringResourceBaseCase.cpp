#include "TestKoverage/Richman/Text/Scanner/StringResourceBaseCase.hpp"

#include "Richman/Text/Scanner/StringResource.hpp"

#include <cstring>


using TestKoverage::Richman::Text::Scanner::StringResourceBaseCase;

using Richman::Text::Scanner::StringResource;


void StringResourceBaseCase::run () {
	const char * string = getLorem ();
	std::size_t length = getLoremLength ();

	StringResource resource (string);
	assertTrue (resource.hasNext (), "Has next symbol for reading", __FILE__, __LINE__);

	resource.skipNext (length);
	assertFalse (resource.hasNext (), "Shouldn't have a symbol for reading after the end", __FILE__, __LINE__);
	assertTrue (resource.hasPrev (), "Should have a symbol for reading before the end", __FILE__, __LINE__);

	resource.skipPrev (length - 1);
	assertTrue (resource.hasNext (), "Should have some symbols for reading after skipping previous symbols", __FILE__, __LINE__);
	assertEqual (1u, resource.getOffset (), "Should be in position after the first symbol", __FILE__, __LINE__);

	resource.setOffset (5);
	assertEqual (5u, resource.getOffset (), "Should be in position where it has been just set", __FILE__, __LINE__);
	assertEqual (1u, resource.skipSpaces (), "Should be one space in the position 6", __FILE__, __LINE__);
	assertEqual (6u, resource.getOffset (), "Should be in position after the skipped space", __FILE__, __LINE__);
	assertEqual ('i', resource.readChar (), "The first symbol in the word \"ipsum\" is 'i'", __FILE__, __LINE__);
	assertEqual ('d', resource.sliceNextChar (5), "After the five symbols (\"psum \") should be the word \"dolor\" with the first character 'd'", __FILE__, __LINE__);
	assertEqual ('m', resource.slicePrevChar (3), "In a three symbols before (\"dolor\") should be the word \"ipsum\" with the last character 'm'", __FILE__, __LINE__);
	assertEqualAlong ("m i", resource.slicePrevPtr (3), "Before 3 symbols should be the string \"m i\"", __FILE__, __LINE__);

	resource.setOffset (0);
	assertTrue (resource.hasNext (6), "Should have next 6 symbols to read", __FILE__, __LINE__);
	assertEqualAlong ("ipsum", resource.sliceNextPtr (6), "After the 6 symbols (\"Lorem \") should be the word \"ipsum\"", __FILE__, __LINE__);
	assertEqual ('i', resource.sliceNextChar (6), "After the 6 symbols (\"Lorem \") should be the char 'i'", __FILE__, __LINE__);
}
