#include <cassert>
#include <string.h>
#include <util.h>
#include <test.h>
namespace test {


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

bool nextNumber(istream &in, size_t &number) {
	const static size_t NUM_LEN = strlen("<num>");
	string line;
	while ( getline(in, line) ) {
		line = util::trim(line);
		if ( line.substr(0, NUM_LEN) == "<num>" ) {
			if ( line.length() == NUM_LEN ) {
				getline(in, line);
			}
			for (size_t i = 0; i < line.length(); i ++) {
				if ( '0' <= line[i] && line[i] <= '9' ) {
					number = stol(line.substr(i));
					return true;
				}
			}
			return false;
		}
	}
	return false;
}

string nextTitle(istream &in) {
	const static size_t NUM_LEN = strlen("<title>");
	string line;
	while ( getline(in, line) ) {
		line = util::trim(line);
		if ( line.substr(0, NUM_LEN) == "<title>" ) {
			if ( line.length() == NUM_LEN ) {
				getline(in, line);
				line = util::trim(line);

			} else {
				line = line.substr(NUM_LEN);
				line = util::trim(line);
			}
			return line;
		}
	}
	return "";
}


}
