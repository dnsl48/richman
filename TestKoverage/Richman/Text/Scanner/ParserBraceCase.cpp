#include "TestKoverage/Richman/Text/Scanner/ParserBraceCase.hpp"

#include "Richman/Text/Scanner/Parser.hpp"
#include "Richman/Text/Scanner/StringResource.hpp"

#include "Richman/Text/String.hpp"


using Richman::Text::Scanner::Parser;
using Richman::Text::Scanner::StringResource;

using Richman::Text::String;

using TestKoverage::Richman::Text::Scanner::ParserBraceCase;


void ParserBraceCase::run () {
	StringResource resource ("Lorem<!-- ipsum dolor <!-- sit --> amet --> consectetur");

	Parser<1, 0, 0, 1> parser;
	parser.setStop (0, " ");
	parser.setBrace (0, "<!--", "-->");
	parser.setBrace (1, "<!", "->"); // IT SHOULD DO NOTHING

	String s = parser.readSection (resource);

	assertEqual (43, s.getLength (), "Parser brace; check stop escaping; string length", __FILE__, __LINE__);
	assertEqualAlong ("Lorem<!-- ipsum dolor <!-- sit --> amet -->", s.getPtr (), "Parser brace; check stop escaping; string content", __FILE__, __LINE__);
	assertEqual (0, parser.getGreedyCount (), "Parser brace; check stop escaping; check greedy count", __FILE__, __LINE__);
	assertEqual (0, parser.getGreedyLength (), "Parser brace; check stop escaping; check greedy length", __FILE__, __LINE__);
	assertEqual (0, parser.getSectionOffset ()[0], "Parser brace; check stop escaping; check offset begin", __FILE__, __LINE__);
	assertEqual (43, parser.getSectionOffset ()[1], "Parser brace; check stop escaping; check offset ending", __FILE__, __LINE__);


	StringResource resource2 ("(Lorem)[ipsum](dolor[sit]amet)(consectertur[adipisicing)(elit(sed])do)");

	Parser<0, 0, 0, 2> parser2;
	parser2.setBrace (0, "(", ")");
	parser2.setBrace (1, "[", "]");


	String s2 = parser2.readSection (resource2);

	assertEqual (7, s2.getLength (), "Parser brace; check sequentially scanned braced scopes; scope1 string length", __FILE__, __LINE__);
	assertEqualAlong ("(Lorem)", s2.getPtr (), "Parser brace; check sequentially scanned braced scopes; scope1 string content", __FILE__, __LINE__);
	assertEqual (0, parser2.getGreedyCount (), "Parser brace; check sequentially scanned braced scopes; scope1 check greedy count", __FILE__, __LINE__);
	assertEqual (0, parser2.getGreedyLength (), "Parser brace; check sequentially scanned braced scopes; scope1 check greedy length", __FILE__, __LINE__);
	assertEqual (0, parser2.getSectionOffset ()[0], "Parser brace; check sequentially scanned braced scopes; scope1 check offset begin", __FILE__, __LINE__);
	assertEqual (7, parser2.getSectionOffset ()[1], "Parser brace; check sequentially scanned braced scopes; scope1 check offset ending", __FILE__, __LINE__);


	String s3 = parser2.readSection (resource2);

	assertEqual (7, s3.getLength (), "Parser brace; check sequentially scanned braced scopes; scope2 string length", __FILE__, __LINE__);
	assertEqualAlong ("[ipsum]", s3.getPtr (), "Parser brace; check sequentially scanned braced scopes; scope2 string content", __FILE__, __LINE__);
	assertEqual (0, parser2.getGreedyCount (), "Parser brace; check sequentially scanned braced scopes; scope2 check greedy count", __FILE__, __LINE__);
	assertEqual (0, parser2.getGreedyLength (), "Parser brace; check sequentially scanned braced scopes; scope2 check greedy length", __FILE__, __LINE__);
	assertEqual (7, parser2.getSectionOffset ()[0], "Parser brace; check sequentially scanned braced scopes; scope2 check offset begin", __FILE__, __LINE__);
	assertEqual (14, parser2.getSectionOffset ()[1], "Parser brace; check sequentially scanned braced scopes; scope2 check offset ending", __FILE__, __LINE__);


	String s4 = parser2.readSection (resource2);

	assertEqual (16, s4.getLength (), "Parser brace; check sequentially scanned braced scopes; scope3 string length", __FILE__, __LINE__);
	assertEqualAlong ("(dolor[sit]amet)", s4.getPtr (), "Parser brace; check sequentially scanned braced scopes; scope3 string content", __FILE__, __LINE__);
	assertEqual (0, parser2.getGreedyCount (), "Parser brace; check sequentially scanned braced scopes; scope3 check greedy count", __FILE__, __LINE__);
	assertEqual (0, parser2.getGreedyLength (), "Parser brace; check sequentially scanned braced scopes; scope3 check greedy length", __FILE__, __LINE__);
	assertEqual (14, parser2.getSectionOffset ()[0], "Parser brace; check sequentially scanned braced scopes; scope3 check offset begin", __FILE__, __LINE__);
	assertEqual (30, parser2.getSectionOffset ()[1], "Parser brace; check sequentially scanned braced scopes; scope3 check offset ending", __FILE__, __LINE__);


	String s5 = parser2.readSection (resource2);

	assertEqual (40, s5.getLength (), "Parser brace; check sequentially scanned braced scopes; scope4 string length", __FILE__, __LINE__);
	assertEqualAlong ("(consectertur[adipisicing)(elit(sed])do)", s5.getPtr (), "Parser brace; check sequentially scanned braced scopes; scope4 string content", __FILE__, __LINE__);
	assertEqual (0, parser2.getGreedyCount (), "Parser brace; check sequentially scanned braced scopes; scope4 check greedy count", __FILE__, __LINE__);
	assertEqual (0, parser2.getGreedyLength (), "Parser brace; check sequentially scanned braced scopes; scope4 check greedy length", __FILE__, __LINE__);
	assertEqual (30, parser2.getSectionOffset ()[0], "Parser brace; check sequentially scanned braced scopes; scope4 check offset begin", __FILE__, __LINE__);
	assertEqual (70, parser2.getSectionOffset ()[1], "Parser brace; check sequentially scanned braced scopes; scope4 check offset ending", __FILE__, __LINE__);




	StringResource resource3 ("Lorem( ipsum\\) dolor') sit' amet) consectetur");

	Parser<1, 1, 1, 1> parser3;
	parser3.setStop (0, " ");
	parser3.setBrace (0, "(", ")");
	parser3.setEscapeLong (0, "'");
	parser3.setEscapeShort (0, "\\");

	String s6 = parser3.readSection (resource3);

	assertEqual (33, s6.getLength (), "Parser brace; check stop escaping; string length", __FILE__, __LINE__);
	assertEqualAlong ("Lorem( ipsum\\) dolor') sit' amet)", s6.getPtr (), "Parser brace; check stop escaping; string content", __FILE__, __LINE__);
	assertEqual (0, parser3.getGreedyCount (), "Parser brace; check stop escaping; check greedy count", __FILE__, __LINE__);
	assertEqual (0, parser3.getGreedyLength (), "Parser brace; check stop escaping; check greedy length", __FILE__, __LINE__);
	assertEqual (0, parser3.getSectionOffset ()[0], "Parser brace; check stop escaping; check offset begin", __FILE__, __LINE__);
	assertEqual (33, parser3.getSectionOffset ()[1], "Parser brace; check stop escaping; check offset ending", __FILE__, __LINE__);
}
