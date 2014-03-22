#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <cstdio>
#include <cstdlib>
#include <cerrno>

#include <util.h>
#include <tinyxml2.h>
#include <IndexWriter.h>
#include <StringField.h>
#include <Document.h>
#include <TextField.h>
#include <Analyzer.h>
namespace test {


static vector<vector<string>> tests = {
	{"This is a good day!", "", "It is a hot day", "Hot day Today."},
	{"OK", "Today is a cold day.", "", "My day is a happy day"},
	{"BAD", "", "This is a test.", ""},
	{"USEFUL", "", "This goes right", "The day comes"},
	{"SHIT", "", "", "It goes right this day."},
};

using namespace tinyxml2;
void index(IndexWriter &iw, const Analyzer &analyzer,
		const string &docDirPath, const string &indexPath) {
	static size_t num = 0;
	DIR *dir;
	struct dirent *ent;
	if ( (dir = opendir(docDirPath.c_str())) == NULL ) {
		cerr << "Can't open " << docDirPath << endl;
		return;
	}

	while ( (ent = readdir(dir)) != NULL ) {
		string fullPath = docDirPath;
		fullPath += "/";
		fullPath += ent->d_name;
		string fileName = ent->d_name;
		if ( fileName.length() == 0 || fileName[0] == '.' ) continue;

		if ( util::isFile(fullPath) ) {
			string postfix = "newsML.xml";
//			string postfix = ".cpp";
			if ( fileName.rfind(postfix) == string::npos ||
					fileName.rfind(postfix) + postfix.length() != 
					fileName.length() ) continue;

			XMLDocument xmlDoc;  
			xmlDoc.LoadFile("test.xml");  
			XMLElement *newsitem = xmlDoc.RootElement();
			XMLElement *xmlText = newsitem->FirstChildElement("text");  
			XMLElement *p = xmlText->FirstChildElement("p");
			string text;
			while ( p ) {
				text += p->GetText();
				text += "\n";
				p = p->NextSiblingElement();
			}
			string title = newsitem->FirstChildElement("title")->GetText();

//			cout << fileName << endl;
			Document doc;

//			ifstream in(fullPath);
//			TextField f1("content", in, analyzer);
//			StringField f2("fileName", fileName);

			TextField f1("title", title, analyzer);
			TextField f2("text", text, analyzer);
			StringField f3("filePath", fullPath);

			doc.addField(f1);
			doc.addField(f2);
			doc.addField(f3);

			iw.write(doc);
//			in.close();

			if ( ++ num % 1000 == 0 ) cerr << ".";

		} else if ( util::isDir(fullPath) ) {
			index(iw, analyzer, fullPath, indexPath);
		}
	}

	closedir(dir);
//	cout << iw.toString() << "================" << endl;
}

void index(const string &docDirPath, const string &indexPath) {
	IndexWriter iw(indexPath);
	Analyzer analyzer;
	index(iw, analyzer, docDirPath, indexPath);
	cout << endl << "merging ..." << endl;
	iw.close();
	cerr << "Finish." << endl;
}

void littleIndex() {
	IndexWriter iw("/home/dhuang/index");
	Analyzer analyzer;
	for (size_t i = 0; i < tests.size(); i ++) {
		StringField field0 = StringField("title", tests[i][0]);
		Document doc = Document();
		doc.addField(field0);
		for (size_t j = 1; j < tests[i].size(); j ++) {
			doc.addField(
					*new TextField(string(1, 'a' + j - 1), 
						tests[i][j], analyzer));
		}
		iw.write(doc);
	}
//	cout << iw.toString() << endl << endl;
	iw.close();
}


}
