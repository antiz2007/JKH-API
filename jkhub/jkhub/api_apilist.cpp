#include "api_local.h"

using namespace std;

APIList& APIList::Add(string a, string b) {
	z.insert(make_pair(a, b));
	return *this;
}

string APIList::Serialize() {
	string retVal = "";
	for(auto it = z.begin(); it != z.end(); ++it) {
		if(it != z.begin())
			retVal += "&";
		retVal += it->first;
		retVal += "=";
		retVal += it->second;
	}
	return retVal;
}