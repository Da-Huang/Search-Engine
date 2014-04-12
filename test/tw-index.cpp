#include <cassert>
#include <dirent.h>
#include <util.h>
#include <IndexWriter.h>
#include <StringField.h>
#include <XMLDoc.h>
#include <Document.h>
#include <TextField.h>
#include <Analyzer.h>
namespace test {

static void twIndex(IndexWriter &iw, const Analyzer &analyzer,
		const string &path);
static map<string, string> twConvert(istream &in);


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

		iw.write(doc);
	}
	in.close();
}

map<string, string> twConvert(istream &in) {
	map<string, string> res;
	string line;
	string key, value;
	size_t split;

	util::getline(in, line, "\x1e\n");
	split = line.find('=');
	assert (split != string::npos);
	key = line.substr(0, split);
	value = line.substr(split + 1);
	assert (key == "body");
	res[key] = value;

	util::getline(in, line, "\x1e\n");
	split = line.find('=');
	assert (split != string::npos);
	key = line.substr(0, split);
	value = line.substr(split + 1);
	assert (key == "desc");
	res[key] = value;

	util::getline(in, line, "\x1e\n");
	split = line.find('=');
	assert (split != string::npos);
	key = line.substr(0, split);
	value = line.substr(split + 1);
	assert (key == "keyword");
	res[key] = value;

	util::getline(in, line, "\x1e\n");
	split = line.find('=');
	assert (split != string::npos);
	key = line.substr(0, split);
	value = line.substr(split + 1);
	assert (key == "norm_pagerank");
	res[key] = value;

	util::getline(in, line, "\x1e\n");
	split = line.find('=');
	assert (split != string::npos);
	key = line.substr(0, split);
	value = line.substr(split + 1);
	assert (key == "pagerank");
	res[key] = value;

	util::getline(in, line, "\x1e\n");
	split = line.find('=');
	assert (split != string::npos);
	key = line.substr(0, split);
	value = line.substr(split + 1);
	assert (key == "raw_anchor");
	res[key] = value;

	util::getline(in, line, "\x1e\n");
	split = line.find('=');
	assert (split != string::npos);
	key = line.substr(0, split);
	value = line.substr(split + 1);
	assert (key == "rawid");
	res[key] = value;

	util::getline(in, line, "\x1e\n");
	split = line.find('=');
	assert (split != string::npos);
	key = line.substr(0, split);
	value = line.substr(split + 1);
	assert (key == "scored_anchor");
	res[key] = value;

	util::getline(in, line, "\x1e\n");
	split = line.find('=');
	assert (split != string::npos);
	key = line.substr(0, split);
	value = line.substr(split + 1);
	assert (key == "spamlevel");
	res[key] = value;

	util::getline(in, line, "\x1e\n");
	split = line.find('=');
	assert (split != string::npos);
	key = line.substr(0, split);
	value = line.substr(split + 1);
	assert (key == "title");
	res[key] = value;

	util::getline(in, line, "\x1e\n");
	split = line.find('=');
	assert (split != string::npos);
	key = line.substr(0, split);
	value = line.substr(split + 1);
	assert (key == "trecid");
	res[key] = value;
	
	util::getline(in, line, "\x1e\n");
	split = line.find('=');
	assert (split != string::npos);
	key = line.substr(0, split);
	value = line.substr(split + 1);
	assert (key == "url");
	res[key] = value;

	util::getline(in, line, "\x1f\n");
	return res;
}


}
