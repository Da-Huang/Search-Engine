#include <cassert>
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


}
