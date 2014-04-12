#include <cassert>
#include <dirent.h>
#include <util.h>
#include <IndexWriter.h>
#include <StringField.h>
#include <XMLDoc.h>
#include <Document.h>
#include <TextField.h>
#include <Analyzer.h>
#include <test.h>
namespace test {

static void twIndex(IndexWriter &iw, const Analyzer &analyzer,
		const string &path);


void twIndex(IndexWriter &iw, const Analyzer &analyzer,
		const string &docDirPath, const string &indexPath) {
	DIR *dir = opendir(docDirPath.c_str());
	assert (dir);

	struct dirent *ent;
	while ( (ent = readdir(dir)) ) {
		string fileName = ent->d_name;
		string fullPath = util::join("", {docDirPath, "/", fileName});
		if ( fileName.length() == 0 || fileName[0] == '.' ) continue;

		if ( util::isFile(fullPath) ) {
			cerr << fullPath << endl;
			twIndex(iw, analyzer, fullPath);

		} else if ( util::isDir(fullPath) ) {
			twIndex(iw, analyzer, fullPath, indexPath);
		}
	}

	closedir(dir);
}

void twIndex(const string &docDirPath, const string &indexPath) {
	IndexWriter iw(indexPath);
	Analyzer analyzer;
	twIndex(iw, analyzer, docDirPath, indexPath);
	cerr << endl << "merging ..." << endl;
	iw.close();
	cerr << "Finish." << endl;
}

void twIndex(IndexWriter &iw, const Analyzer &analyzer,
		const string &path) {

	ifstream in(path.c_str());
	static size_t count = 0;
	while ( !in.eof() ) {
		size_t offset = in.tellg();
		cerr << ++ count << ". ";
		map<string, string> record = twConvert(in);
		cerr << record["trecid"] << endl;

		Document doc;

		TextField f1("title", record["title"], analyzer);
		TextField f2("body", record["body"], analyzer);
		StringField f3("path", path);
		StringField f4("offset", to_string(offset));

		doc.addField(f1);
		doc.addField(f2);
		doc.addField(f3);
		doc.addField(f4);

		doc.setStaticScore(stod(record["pagerank"]));
		iw.write(doc);
	}
	in.close();
}


}
