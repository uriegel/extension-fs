#include "std_utils.h"
using namespace std;

const vector<wstring> split(const wstring& s, wchar_t delim) {
	wstringstream wss(s);
	wstring item;
	vector<wstring> elems;
	while (getline(wss, item, delim))
		elems.push_back(move(item));

	return move(elems);
}
