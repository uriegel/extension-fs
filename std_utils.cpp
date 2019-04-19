#include "std_utils.h"
#include <algorithm>
#include <string>
#include <cctype>
using namespace std;

const vector<wstring> split(const wstring& s, wchar_t delim) {
	wstringstream wss(s);
	wstring item;
	vector<wstring> elems;
	while (getline(wss, item, delim))
		elems.push_back(move(item));

	return move(elems);
}

int findString(const wstring &text, const wstring& searchText) {
    auto it = search(text.begin(), text.end(),
        searchText.begin(), searchText.end(),
        [](auto ch1, auto ch2) { return toupper(ch1) == toupper(ch2); }
    );
	auto pos = static_cast<int>(it - text.begin());
	return pos < text.length() ? pos : -1;
}

