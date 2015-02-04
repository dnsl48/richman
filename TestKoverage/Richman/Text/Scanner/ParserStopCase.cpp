#include "TestKoverage/Richman/Text/Scanner/ParserStopCase.hpp"

#include "Richman/Text/Scanner/Parser.hpp"
#include "Richman/Text/Scanner/StringResource.hpp"

#include "Richman/Text/String.hpp"


using Richman::Text::Scanner::Parser;
using Richman::Text::Scanner::StringResource;

using Richman::Text::String;

using TestKoverage::Richman::Text::Scanner::ParserStopCase;


void ParserStopCase::run () {
	StringResource resource (getLorem ());

	Parser<1> parser;
	parser.setStop (0, " ");
	parser.setStop (1, "Lorem"); // IT SHOULD DO NOTHING

	String s = parser.readSection (resource);

	assertEqual (5, s.getLength (), "Parser stop; read section; check length", __FILE__, __LINE__);
	assertEqualAlong ("Lorem", s.getPtr (), "Parser stop; read section; check content", __FILE__, __LINE__);
	assertEqual (1, parser.getGreedyCount (), "Parser stop; read section; check greedy count", __FILE__, __LINE__);
	assertEqual (1, parser.getGreedyLength (), "Parser stop; read section; check greedy length", __FILE__, __LINE__);
	assertEqual (0, parser.getSectionOffset ()[0], "Parser stop; read section; check offset begin", __FILE__, __LINE__);
	assertEqual (5, parser.getSectionOffset ()[1], "Parser stop; read section; check offset ending", __FILE__, __LINE__);


	StringResource resource2 ("Lorem    ipsum");

	Parser<1> parser2;
	parser2.setStop (0, "  ");

	String s2 = parser2.readSection (resource2);

	assertEqual (5, s2.getLength (), "Parser stop; read section2; check length", __FILE__, __LINE__);
	assertEqualAlong ("Lorem", s2.getPtr (), "Parser stop; read section2; check content", __FILE__, __LINE__);
	assertEqual (2, parser2.getGreedyCount (), "Parser stop; read section2; check greedy count", __FILE__, __LINE__);
	assertEqual (4, parser2.getGreedyLength (), "Parser stop; read section2; check greedy length", __FILE__, __LINE__);
	assertEqual (0, parser2.getSectionOffset ()[0], "Parser stop; read section2; check offset begin", __FILE__, __LINE__);
	assertEqual (5, parser2.getSectionOffset ()[1], "Parser stop; read section2; check offset ending", __FILE__, __LINE__);


	StringResource resource3 (getLorem ());

	Parser<1> parser3;
	parser3.setStop (0, " ipsum");

	String s3 = parser3.readSection (resource3);

	assertEqual (5, s.getLength (), "Parser stop; read section3; check length", __FILE__, __LINE__);
	assertEqualAlong ("Lorem", s.getPtr (), "Parser stop; read section3; check content", __FILE__, __LINE__);
	assertEqual (1, parser3.getGreedyCount (), "Parser stop; read section3; check greedy count", __FILE__, __LINE__);
	assertEqual (6, parser3.getGreedyLength (), "Parser stop; read section3; check greedy length", __FILE__, __LINE__);
	assertEqual (0, parser3.getSectionOffset ()[0], "Parser stop; read section3; check offset begin", __FILE__, __LINE__);
	assertEqual (5, parser3.getSectionOffset ()[1], "Parser stop; read section3; check offset ending", __FILE__, __LINE__);




	StringResource resource4 ("Lorem ipsum dolor sit amet");

	Parser<1> parser4;
	parser4.setStop (0, " sit ");

	String s4 = parser4.readSection (resource4);

	assertEqual (17, s4.getLength (), "Parser stop; read section3; check length", __FILE__, __LINE__);
	assertEqualAlong ("Lorem ipsum dolor", s4.getPtr (), "Parser stop; read section3; check content", __FILE__, __LINE__);
	assertEqual (1, parser4.getGreedyCount (), "Parser stop; read section3; check greedy count", __FILE__, __LINE__);
	assertEqual (5, parser4.getGreedyLength (), "Parser stop; read section3; check greedy length", __FILE__, __LINE__);
	assertEqual (0, parser4.getSectionOffset ()[0], "Parser stop; read section3; check offset begin", __FILE__, __LINE__);
	assertEqual (17, parser4.getSectionOffset ()[1], "Parser stop; read section3; check offset ending", __FILE__, __LINE__);
}




