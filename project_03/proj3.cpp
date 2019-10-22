#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <sstream>
#include <fstream>
#include <codecvt>
#include <algorithm>
#include <array>
#include <iostream>
#include <functional>
#include <map>
#include <set>
#include <unordered_map>
#include <cwchar>
#include <locale>
#include <time.h>

#define TESTS 1000

using namespace std;

typedef basic_string<wchar_t> wstring;

static locale l1("es_ES.utf8");

struct modified_whitespace: std::ctype<wchar_t> {
	bool do_is(mask m, char_type c) const {
		if ((m & space) && c == L' ') {
			return true; // space will be classified as whitespace
		}
		if ((m & space) && c == L',') {
			return true; // comma will be classified as whitespace
		}
		if ((m & space) && c == L'.') {
			return true; // point will be classified as whitespace
		}
		if ((m & space) && c == L'-') {
			return true; // dash will be classified as whitespace
		}
		return ctype::do_is(m, c); // leave the rest to the parent class
	}
};

struct comp {
	template<typename T>
	bool operator()(const T &l, const T &r) const {
		if (l.second != r.second)
			return l.second > r.second;

		return l.first > r.first;
	}
};

/**
 * Starts or restarts the time counter.
 * @param time time counter variable
 */
void startClock(timespec &time) {
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time);
}

/**
 * Gets current time. Does not reset the time counter.
 * @param time time counter variable
 * @return Time since the start of the time counter in ms.
 */
double getTimeMs(timespec &time) {
	timespec curr_time;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &curr_time);
	double t = (curr_time.tv_sec - time.tv_sec) * 1000;
	t += (double) (curr_time.tv_nsec - time.tv_nsec) / 1000000;
	return t;
}

// Read the contents of a textfile using a spanish locale
wstring getFileContent(const char *filename) {
	wifstream wif(filename);
	wif.imbue(l1);
	wstringstream wss;
	wss << wif.rdbuf();
	return wss.str();
}

// reads the file and returns all the words as a vector
vector<wstring> readFile(const char *filename) {
	vector<wstring> result;
	wstring token;
	wstring fileContent = getFileContent(filename);
	wistringstream resultStream(fileContent);
	modified_whitespace *my_ws = new modified_whitespace;
	resultStream.imbue(locale(l1, my_ws));
	while (resultStream >> token) {
		std::transform(token.begin(), token.end(), token.begin(), ::tolower);
		result.push_back(token);
	}
	return result;
}

map<wstring, int> countWordsMap(vector<wstring> const &input) {
	map<wstring, int> result;
	for (auto const &i : input) {
		result[i]++;
	}
	return result;
}

unordered_map<wstring, int> countWordsUmap(vector<wstring> const &input) {
	unordered_map<wstring, int> result;
	for (auto const &i : input) {
		result[i]++;
	}
	return result;
}

typedef pair<wstring, int> pairs;
set<pairs, comp> getTopWords(vector<wstring> const &input,
		unsigned int numOfWords = 30) {
	map<wstring, int> unsorted = countWordsMap(input);
	set<pairs, comp> set(unsorted.begin(), unsorted.end());
	if (set.size() < numOfWords) {
		return set;
	}
	set.erase(next(set.begin(), numOfWords), set.end());
	return set;
}

int main() {
	std::locale::global(std::locale("es_ES.utf8"));
	modified_whitespace *my_ws = new modified_whitespace;
	std::wcout.imbue(std::locale(l1, my_ws));

	vector<wstring> text1 = readFile("./texto1.txt");
	vector<wstring> text2 = readFile("./texto2.txt");
	map<wstring, int> text1Map = countWordsMap(text1);
	wcout << L"Outputting counting result of the 1st text:" << endl;
	for (auto const &item : text1Map) {
		wcout << item.first << L" : " << item.second << endl;
	}
	wcout << endl << L"Calculating the average duration (map), please wait..."
			<< endl;
	// Testing counting the words using map
	double timeSum = 0;
	timespec time;
	map<wstring, int> text2Map;
	for (int i = 0; i < TESTS; ++i) {
		startClock(time);
		//CODE TO BE TEMPORALY TESTED
		text2Map = countWordsMap(text2);
		//END
		timeSum += getTimeMs(time);
	}
	wcout << L"Time when using the map(ms): " << timeSum / TESTS << endl;
	wcout << endl
			<< L"Calculating the average duration (unordered map), please wait..."
			<< endl;
	// Testing counting the words using unordered map
	timeSum = 0;
	unordered_map<wstring, int> text2Umap;
	for (int i = 0; i < TESTS; ++i) {
		startClock(time);
		//CODE TO BE TEMPORALY TESTED
		text2Umap = countWordsUmap(text2);
		//END
		timeSum += getTimeMs(time);
	}
	wcout << L"Time when using the unordered map(ms): " << timeSum / TESTS
			<< endl;
	wcout << endl << L"Outputting the 30 most used words in the text:" << endl;
	// Outputing the top 30 used words
	set<pairs, comp> topThirty = getTopWords(text2);
	for (auto const &item : topThirty) {
		wcout << item.first << L" : " << item.second << endl;
	}

	return 0;

}

