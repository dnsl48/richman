#include "TestKoverage/Richman/Text/Scanner/ParserShortEscapeCase.hpp"

#include "Richman/Text/Scanner/Parser.hpp"
#include "Richman/Text/Scanner/StringResource.hpp"

#include "Richman/Text/String.hpp"


using Richman::Text::Scanner::Parser;
using Richman::Text::Scanner::StringResource;

using Richman::Text::String;

using TestKoverage::Richman::Text::Scanner::ParserShortEscapeCase;


void ParserShortEscapeCase::run () {
	StringResource resource ("Lorem\\ ip\\sum  dolor");

	Parser<1, 1> parser;
	parser.setStop (0, " ");
	parser.setEscapeShort (0, "\\");
	parser.setEscapeShort (1, " "); // IT SHOULD DO NOTHING

	String s = parser.readSection (resource);

	assertEqual (13, s.getLength (), "Parser short escape; check stop escaping; string length", __FILE__, __LINE__);
	assertEqualAlong ("Lorem\\ ip\\sum", s.getPtr (), "Parser short escape; check stop escaping; string content", __FILE__, __LINE__);
	assertEqual (2, parser.getGreedyCount (), "Parser short escape; check stop escaping; check greedy count", __FILE__, __LINE__);
	assertEqual (2, parser.getGreedyLength (), "Parser short escape; check stop escaping; check greedy length", __FILE__, __LINE__);
	assertEqual (0, parser.getSectionOffset ()[0], "Parser short escape; check stop escaping; check offset begin", __FILE__, __LINE__);
	assertEqual (13, parser.getSectionOffset ()[1], "Parser short escape; check stop escaping; check offset ending", __FILE__, __LINE__);


	StringResource resource1 ("Lorem<!-- ipsum  dolor");

	Parser<1, 1> parser1;
	parser1.setStop (0, " ");
	parser1.setEscapeShort (0, "<!--");

	String s1 = parser1.readSection (resource1);

	assertEqual (15, s1.getLength (), "Parser short escape; check stop escaping; string length", __FILE__, __LINE__);
	assertEqualAlong ("Lorem<!-- ipsum", s1.getPtr (), "Parser short escape; check stop escaping; string content", __FILE__, __LINE__);
	assertEqual (2, parser1.getGreedyCount (), "Parser short escape; check stop escaping; check greedy count", __FILE__, __LINE__);
	assertEqual (2, parser1.getGreedyLength (), "Parser short escape; check stop escaping; check greedy length", __FILE__, __LINE__);
	assertEqual (0, parser1.getSectionOffset ()[0], "Parser short escape; check stop escaping; check offset begin", __FILE__, __LINE__);
	assertEqual (15, parser1.getSectionOffset ()[1], "Parser short escape; check stop escaping; check offset ending", __FILE__, __LINE__);



	StringResource resource2 ("Lorem<!-- ipsum<!--<!--  dolor");

	Parser<1, 1> parser2;
	parser2.setStop (0, " ");
	parser2.setEscapeShort (0, "<!--");

	String s2 = parser2.readSection (resource2);

	assertEqual (23, s2.getLength (), "Parser short escape; check escape escaping; string length", __FILE__, __LINE__);
	assertEqualAlong ("Lorem<!-- ipsum<!--<!--", s2.getPtr (), "Parser short escape; check escape escaping; string content", __FILE__, __LINE__);
	assertEqual (2, parser2.getGreedyCount (), "Parser short escape; check escape escaping; check greedy count", __FILE__, __LINE__);
	assertEqual (2, parser2.getGreedyLength (), "Parser short escape; check escape escaping; check greedy length", __FILE__, __LINE__);
	assertEqual (0, parser2.getSectionOffset ()[0], "Parser short escape; check escape escaping; check offset begin", __FILE__, __LINE__);
	assertEqual (23, parser2.getSectionOffset ()[1], "Parser short escape; check escape escaping; check offset ending", __FILE__, __LINE__);



	StringResource resource3 ("Lorem<!-ipsum<!--  dolor");

	Parser<1, 1> parser3;
	parser3.setStop (0, " ");
	parser3.setEscapeShort (0, "<!--");

	String s3 = parser3.readSection (resource3);

	assertEqual (18, s3.getLength (), "Parser short escape; check stop escaping; string length", __FILE__, __LINE__);
	assertEqualAlong ("Lorem<!-ipsum<!-- ", s3.getPtr (), "Parser short escape; check stop escaping; string content", __FILE__, __LINE__);
	assertEqual (1, parser3.getGreedyCount (), "Parser short escape; check stop escaping; check greedy count", __FILE__, __LINE__);
	assertEqual (1, parser3.getGreedyLength (), "Parser short escape; check stop escaping; check greedy length", __FILE__, __LINE__);
	assertEqual (0, parser3.getSectionOffset ()[0], "Parser short escape; check stop escaping; check offset begin", __FILE__, __LINE__);
	assertEqual (18, parser3.getSectionOffset ()[1], "Parser short escape; check stop escaping; check offset ending", __FILE__, __LINE__);
}
