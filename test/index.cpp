#include <util.h>
#include <dirent.h>
#include <XMLDoc.h>
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

void index(IndexWriter &iw, const Analyzer &analyzer,
		const string &docDirPath, const string &indexPath) {
	static size_t count = 0;
	DIR *dir = opendir(docDirPath.c_str());
	assert (dir);

	struct dirent *ent;
	while ( (ent = readdir(dir)) ) {
		string fileName = ent->d_name;
		string fullPath = util::join("", {docDirPath, "/", fileName});
		if ( fileName.length() == 0 || fileName[0] == '.' ) continue;

		if ( util::isFile(fullPath) ) {
			string postfix = "newsML.xml";
//			string postfix = ".cpp";
			if ( fileName.rfind(postfix) == string::npos ||
					fileName.rfind(postfix) + postfix.length() != 
					fileName.length() ) continue;

			XMLDoc xmlDoc(fullPath);

			count ++;
			cerr << count << "\t";
			cerr << fullPath << endl;
			
			Document doc;
//			doc.setStaticScore(double(count));

//			ifstream in(fullPath);
//			TextField f1("content", in, analyzer);
//			StringField f2("fileName", fileName);

			TextField f1("title", xmlDoc.getTitle(), analyzer);
//			cout << title << endl;
			TextField f2("text", xmlDoc.getText(), analyzer);
//			cout << text << endl;
			StringField f3("filePath", fullPath);
//			cout << fullPath << endl;

			doc.addField(f1);
			doc.addField(f2);
			doc.addField(f3);

			iw.write(doc);
			
//			in.close();

//			if ( count % 1000 == 0 ) cerr << ".";
//			cout << count << endl;

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
	cerr << endl << "merging ..." << endl;
	iw.close();
	cerr << "Finish." << endl;
}

void littleIndex() {
	IndexWriter iw("../index");
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
