#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <cstdio>
#include <cstdlib>
#include <cerrno>

#include <util.h>
#include <IndexWriter.h>
#include <StringField.h>
#include <XMLDoc.h>
#include <Document.h>
#include <TextField.h>
#include <Analyzer.h>
namespace test {


void twIndex(IndexWriter &iw, const Analyzer &analyzer,
		const string &docDirPath, const string &indexPath) {
	static size_t count = 0;
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

			XMLDoc xmlDoc(fullPath);

			count ++;
			cerr << count << "\t";
			cerr << fullPath << endl;
			
			Document doc;

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
			twIndex(iw, analyzer, fullPath, indexPath);
		}
	}

	closedir(dir);
//	cout << iw.toString() << "================" << endl;
}

void twIndex(const string &docDirPath, const string &indexPath) {
	IndexWriter iw(indexPath);
	Analyzer analyzer;
	twIndex(iw, analyzer, docDirPath, indexPath);
	cerr << endl << "merging ..." << endl;
	iw.close();
	cerr << "Finish." << endl;
}


}
