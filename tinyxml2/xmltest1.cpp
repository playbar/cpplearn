#if defined( _MSC_VER )
#if !defined( _CRT_SECURE_NO_WARNINGS )
		#define _CRT_SECURE_NO_WARNINGS		// This test file is not intended to be secure.
	#endif
#endif

#include "tinyxml2.h"
#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <sys/stat.h>
#include <sys/types.h>


using namespace tinyxml2;
using namespace std;

int main( int argc, const char ** argv )
{
    // Test: Programmatic DOM
    // Build:
    //		<element>
    //			<!--comment-->
    //			<sub attrib="0" />
    //			<sub attrib="1" />
    //			<sub attrib="2" >& Text!</sub>
    //		<element>

    XMLDocument* doc = new XMLDocument();
    doc->InsertFirstChild(doc->NewDeclaration());

    XMLElement* element = doc->NewElement( "layer" );
    element->SetAttribute("name", "testaa");
    doc->InsertEndChild(element);

    XMLElement* sub[3] = {
            doc->NewElement( "sub" ),
            doc->NewElement( "sub" ),
            doc->NewElement( "sub" )
    };

    for( int i=0; i<3; ++i ) {
        sub[i]->SetAttribute( "attrib", i );
    }
    element->InsertEndChild( sub[2] );

    int dummyValue = 1000;
    XMLNode* comment = element->InsertFirstChild( doc->NewComment( "comment" ) );
    comment->SetUserData(&dummyValue);
    element->InsertAfterChild( comment, sub[0] );
    element->InsertAfterChild( sub[0], sub[1] );
//    sub[2]->InsertFirstChild( doc->NewText( "& Text!" ));

    XMLElement* subEle = sub[2]->InsertNewChildElement("style");
    subEle->SetAttribute("Path", "test");
    subEle->SetAttribute("code", 5);


    doc->Print();


//    // And now deletion:
//    element->DeleteChild( sub[2] );
//    doc->DeleteNode( comment );
//
//    element->FirstChildElement()->SetAttribute( "attrib", true );
//    element->LastChildElement()->DeleteAttribute( "attrib" );
//
//
//    const int defaultIntValue = 10;
//    const int replacementIntValue = 20;
//    int value1 = defaultIntValue;
//    int value2 = doc->FirstChildElement()->LastChildElement()->IntAttribute( "attrib", replacementIntValue );
//    XMLError result = doc->FirstChildElement()->LastChildElement()->QueryIntAttribute( "attrib", &value1 );
//
//    doc->Print();
//
//    {
//        XMLPrinter streamer;
//        doc->Print( &streamer );
//        printf( "%s", streamer.CStr() );
//    }
//    {
//        XMLPrinter streamer( 0, true );
//        doc->Print( &streamer );
//    }
//    doc->SaveFile( "./pretty.xml" );
//    doc->SaveFile( "./compact.xml", true );
    delete doc;

    return 0;
}
