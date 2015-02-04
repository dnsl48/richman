#include "TestKoverage/Richman/Text/Scanner/ParserLongEscapeCase.hpp"

#include "Richman/Text/Scanner/Parser.hpp"
#include "Richman/Text/Scanner/StringResource.hpp"

#include "Richman/Text/String.hpp"


using Richman::Text::Scanner::Parser;
using Richman::Text::Scanner::StringResource;

using Richman::Text::String;

using TestKoverage::Richman::Text::Scanner::ParserLongEscapeCase;


void ParserLongEscapeCase::run () {
	StringResource resource ("Lorem' ipsum'  dolor");

	Parser<1, 0, 1> parser;
	parser.setStop (0, " ");
	parser.setEscapeLong (0, "'");
	parser.setEscapeLong (1, " "); // IT SHOULD DO NOTHING

	String s = parser.readSection (resource);

	assertEqual (13u, s.getLength (), "Parser long escape; check stop escaping; string length", __FILE__, __LINE__);
	assertEqualAlong ("Lorem' ipsum'", s.getPtr (), "Parser long escape; check stop escaping; string content", __FILE__, __LINE__);
	assertEqual (2u, parser.getGreedyCount (), "Parser long escape; check stop escaping; check greedy count", __FILE__, __LINE__);
	assertEqual (2u, parser.getGreedyLength (), "Parser long escape; check stop escaping; check greedy length", __FILE__, __LINE__);
	assertEqual (0u, parser.getSectionOffset ()[0], "Parser long escape; check stop escaping; check offset begin", __FILE__, __LINE__);
	assertEqual (13u, parser.getSectionOffset ()[1], "Parser long escape; check stop escaping; check offset ending", __FILE__, __LINE__);



	StringResource resource1 ("Lorem-- ipsum--  dolor");

	Parser<1, 0, 1> parser1;
	parser1.setStop (0, " ");
	parser1.setEscapeLong (0, "--");

	String s1 = parser1.readSection (resource1);

	assertEqual (15, s1.getLength (), "Parser long escape; check stop escaping; string length", __FILE__, __LINE__);
	assertEqualAlong ("Lorem-- ipsum--", s1.getPtr (), "Parser long escape; check stop escaping; string content", __FILE__, __LINE__);
	assertEqual (2, parser1.getGreedyCount (), "Parser long escape; check stop escaping; check greedy count", __FILE__, __LINE__);
	assertEqual (2, parser1.getGreedyLength (), "Parser long escape; check stop escaping; check greedy length", __FILE__, __LINE__);
	assertEqual (0, parser1.getSectionOffset ()[0], "Parser long escape; check stop escaping; check offset begin", __FILE__, __LINE__);
	assertEqual (15, parser1.getSectionOffset ()[1], "Parser long escape; check stop escaping; check offset ending", __FILE__, __LINE__);



	StringResource resource2 ("Lorem-- ip\\--sum--  dolor");

	Parser<1, 1, 1> parser2;
	parser2.setStop (0, " ");
	parser2.setEscapeLong (0, "--");
	parser2.setEscapeShort (0, "\\");

	String s2 = parser2.readSection (resource2);

	assertEqual (18, s2.getLength (), "Parser long escape; check stop escaping; string length", __FILE__, __LINE__);
	assertEqualAlong ("Lorem-- ip\\--sum--", s2.getPtr (), "Parser long escape; check stop escaping; string content", __FILE__, __LINE__);
	assertEqual (2, parser2.getGreedyCount (), "Parser long escape; check stop escaping; check greedy count", __FILE__, __LINE__);
	assertEqual (2, parser2.getGreedyLength (), "Parser long escape; check stop escaping; check greedy length", __FILE__, __LINE__);
	assertEqual (0, parser2.getSectionOffset ()[0], "Parser long escape; check stop escaping; check offset begin", __FILE__, __LINE__);
	assertEqual (18, parser2.getSectionOffset ()[1], "Parser long escape; check stop escaping; check offset ending", __FILE__, __LINE__);



	StringResource resource3 ("Lorem\\--  ipsum--  dolor");

	Parser<1, 1, 1> parser3;
	parser3.setStop (0, " ");
	parser3.setEscapeLong (0, "--");
	parser3.setEscapeShort (0, "\\");

	String s3 = parser3.readSection (resource3);

	assertEqual (8, s3.getLength (), "Parser long escape; check stop escaping; string length", __FILE__, __LINE__);
	assertEqualAlong ("Lorem\\--", s3.getPtr (), "Parser long escape; check stop escaping; string content", __FILE__, __LINE__);
	assertEqual (2, parser3.getGreedyCount (), "Parser long escape; check stop escaping; check greedy count", __FILE__, __LINE__);
	assertEqual (2, parser3.getGreedyLength (), "Parser long escape; check stop escaping; check greedy length", __FILE__, __LINE__);
	assertEqual (0, parser3.getSectionOffset ()[0], "Parser long escape; check stop escaping; check offset begin", __FILE__, __LINE__);
	assertEqual (8, parser3.getSectionOffset ()[1], "Parser long escape; check stop escaping; check offset ending", __FILE__, __LINE__);



	StringResource resource4 ("Lorem-- ip-sum--  dolor");

	Parser<1, 0, 1> parser4;
	parser4.setStop (0, " ");
	parser4.setEscapeLong (0, "--");

	String s4 = parser4.readSection (resource4);

	assertEqual (16, s4.getLength (), "Parser long escape; check stop escaping; string length", __FILE__, __LINE__);
	assertEqualAlong ("Lorem-- ip-sum--", s4.getPtr (), "Parser long escape; check stop escaping; string content", __FILE__, __LINE__);
	assertEqual (2, parser4.getGreedyCount (), "Parser long escape; check stop escaping; check greedy count", __FILE__, __LINE__);
	assertEqual (2, parser4.getGreedyLength (), "Parser long escape; check stop escaping; check greedy length", __FILE__, __LINE__);
	assertEqual (0, parser4.getSectionOffset ()[0], "Parser long escape; check stop escaping; check offset begin", __FILE__, __LINE__);
	assertEqual (16, parser4.getSectionOffset ()[1], "Parser long escape; check stop escaping; check offset ending", __FILE__, __LINE__);

}
