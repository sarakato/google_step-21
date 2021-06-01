#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

/* ファイル読み込み */
void get_words(string filename, vector<string>& dictionary){ 
	ifstream ifs(filename);

	if (!ifs) {
		cout << "error : failed to open the text file." << endl;
	}

	string tmp;
	while (getline(ifs, tmp))
		dictionary.push_back(tmp);
}

/* 辞書をソートし新しい辞書を作成 */
void sort_dictionary(vector<string> dictionary, vector<pair<string,int> >& sorted_dictionary){ 
	for (int i = 0; i < dictionary.size(); i++) {
		sort(dictionary[i].begin(), dictionary[i].end()); 
		sorted_dictionary.push_back(make_pair(dictionary[i],i)); // ソート済みの単語と元の場所(index)のペアを追加
	}
	sort(sorted_dictionary.begin(), sorted_dictionary.end());
}

/* ソートした辞書を書き出し */
void out_words(string filename, vector<pair<string,int> > dictionary){
	ofstream ifs(filename);

	if (!ifs) {
		cout << "error : failed to open the text file." << endl;
	}

	for (int i = 0; i < dictionary.size(); i++) {
		ifs << dictionary[i].first << " " << dictionary[i].second << endl;
	}

    ifs.close();
}

/* 辞書を二分探索して見つかったアナグラムを表示 */
void anagram(string word, vector<string> dictionary, vector<pair<string,int> > sorted_dictionary){
	sort(word.begin(), word.end());

	auto iter = lower_bound(sorted_dictionary.begin(), sorted_dictionary.end(), make_pair(word, 0));
	int idx = distance(sorted_dictionary.begin(), iter);
	
	/* 見つかった場合 */
    if (iter != sorted_dictionary.end() && sorted_dictionary[idx].first == word) {
		cout << dictionary[sorted_dictionary[idx].second] << endl; // まず見つけたものを出力

		int idxri = idx+1;
		while(sorted_dictionary[idxri].first == word){ // それより右のものを出力
			cout << dictionary[sorted_dictionary[idxri].second] << endl;
			idxri++;
		}

        int idxle = idx-1;
		while(sorted_dictionary[idxle].first == word){ // それより左のものを出力
			cout << dictionary[sorted_dictionary[idxle].second] << endl;
			idxle--;
		}
    }
	/* 見つからなかった場合 */
	else {
        cout << "anagram is not found." << endl;
    }
}


int main() {
    vector<string> dictionary;
	vector<pair<string,int> > sorted_dictionary;

	get_words("words.txt", dictionary);

	sort_dictionary(dictionary, sorted_dictionary);

	out_words("sorted.txt", sorted_dictionary);

	string word;
	cin >> word;

    anagram(word, dictionary, sorted_dictionary);
}