#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <cstdio>
#include <cstdlib>
#include <cerrno>

#include <KernelTest.h>
#include <IndexWriter.h>
#include <StringField.h>
#include <Document.h>
#include <TextField.h>
#include <Analyzer.h>


static vector<vector<string>> tests = {
	{"This is a good day!", "", "It is a hot day", "Hot day Today."},
	{"OK", "Today is a cold day.", "", "My day is a happy day"},
	{"BAD", "", "This is a test.", ""},
	{"USEFUL", "", "This goes right", "The day comes"},
	{"SHIT", "", "", "It goes right this day."},
};

extern void littleTest();

bool isFile(const string &path) {
	struct stat st;
	int ret = stat(path.c_str(), &st);
	return ret >= 0 && S_ISREG(st.st_mode);
}

void KernelTest::index(const string &docDirPath, const string &indexPath) {
//	littleTest(); return;
	DIR *dir;
	struct dirent *ent;
	if ( (dir = opendir(docDirPath.c_str())) == NULL ) {
		cerr << "Can't open " << docDirPath << endl;
		return;
	}

	IndexWriter iw(indexPath);
	Analyzer analyzer;

	while ( (ent = readdir(dir)) != NULL ) {
		string fullPath = docDirPath;
		fullPath += "/";
		fullPath += ent->d_name;
		string fileName = ent->d_name;
		if ( isFile(fullPath) ) {
			Document doc = Document();

			ifstream in(fullPath);
			TextField f1("content", in, analyzer);
			StringField f2("fileName", fileName);
			StringField f3("filePath", fullPath);

			doc.addField(f1);
			doc.addField(f2);
			doc.addField(f3);

			iw.write(doc);
			in.close();
		}
	}

	closedir(dir);
	iw.close();
}


void littleTest() {
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


