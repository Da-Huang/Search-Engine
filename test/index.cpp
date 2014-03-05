#include <KernelTest.h>
#include <IndexWriter.h>
#include <StringField.h>
#include <Document.h>
#include <TextField.h>
#include <Analyzer.h>


static vector<vector<string>> tests = {
	{"This is a good day!", "", "It is a hot day.", "Hot day Today."},
	{"OK", "Today is a cold day.", "", "My day is a happy day."},
	{"BAD", "", "This is a test.", ""},
	{"USEFUL", "", "This goes right.", "The day comes."},
	{"SHIT", "", "", "It goes right this day."},
};


void KernelTest::index() {

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
	cout << iw.toString() << endl << endl;
	iw.close();
}


