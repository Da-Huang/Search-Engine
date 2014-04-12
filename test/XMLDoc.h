#ifndef _XML_DOC_
#define _XML_DOC_


#include <string>
#include <tinyxml2.h>

using namespace std;
using namespace tinyxml2;


class XMLDoc {
private:
	XMLDocument xmlDoc;
public:
	XMLDoc(const string &path) {
		xmlDoc.LoadFile(path.c_str());
	}
	inline string getTitle() {
		const XMLElement *newsitem = xmlDoc.RootElement();
		const XMLElement *xmlTitle = newsitem ? 
			newsitem->FirstChildElement("title") : NULL;
		string title = xmlTitle && xmlTitle->GetText() ? 
			xmlTitle->GetText() : "";
		return title;
	}
	inline string getText() {
		XMLElement *newsitem = xmlDoc.RootElement();
		XMLElement *xmlText = newsitem ? 
			newsitem->FirstChildElement("text") : NULL;  
		XMLElement *p = xmlText ? 
			xmlText->FirstChildElement("p") : NULL;
		string text;
		while ( p ) {
			if ( p->GetText() ) {
				text += p->GetText();
				text += "\n";
			}
			p = p->NextSiblingElement();
		}
		return text;
	}
};


#endif
