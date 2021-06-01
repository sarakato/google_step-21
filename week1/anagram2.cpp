#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

/* ファイル読み込み */
void get_words(string filename, vector<string>& dictionary){ 
	ifstream ifs1(filename);

	if (!ifs1) {
		cout << "error : failed to open the text file." << endl;
	}

	string tmp;
	while (getline(ifs1, tmp))
		dictionary.push_back(tmp);
}

/* 辞書をソートし新しい辞書を作成 */
void sort_dictionary(vector<string> dictionary, vector<pair<string,int> >& sorted_dictionary){ 
	for (int i = 0; i < dictionary.size(); i++) {
		sort(dictionary[i].begin(), dictionary[i].end()); 
		sorted_dictionary.push_back(make_pair(dictionary[i],i)); // ソート済みの単語と元の場所(idxex)のペアを追加
	}
	sort(sorted_dictionary.begin(), sorted_dictionary.end());
}

/* wordに何が何文字含まれているかカウントしセット */
void count_set(string word, vector<pair<char,int> >& v){
    for (int i = 0; i < word.size(); i++) {
        if(i == 0 || v.back().first != word[i]){
            v.push_back(make_pair(word[i],1));
        }
        else v.back().second++;
    }
}

/* 単語の点数を計算 */
int calculate_score(string word) {
    vector<int> SCORES = { 1, 3, 2, 2, 1, 3, 3, 1, 1, 4, 4, 2, 2, 1, 1, 3, 4, 1, 1, 1, 2, 3, 3, 4, 3, 4 };

    int score = 0;
    for (int i = 0; i < word.size(); i++){
        score += SCORES[word[i] - 'a'];
    }

    return score;
}

/* 最適なアナグラムを見つけ出す */
string search_anagram(string word, vector<pair<char,int> >& v, vector<string> original_dictionary,
    vector<pair<string,int> > sorted_dictionary, vector<vector<pair<char,int> > > count_dictionary){
    v.clear();
    sort(word.begin(), word.end());
    count_set(word, v);
    
    pair<string,int> maxscore = {"",0};
    for (int i = 0; i < count_dictionary.size(); i++) {
        int k = 0, j = 0;
        while(k < count_dictionary[i].size() && j < v.size()){
            if(count_dictionary[i][k].first == v[j].first){
                if(count_dictionary[i][k].second <= v[j].second){
                    k++; j++;
                    if(k >= count_dictionary[i].size()){
                        int index = sorted_dictionary[i].second;
                        if(maxscore.second <= calculate_score(original_dictionary[index])){
                            maxscore.first = original_dictionary[index];
                            maxscore.second = calculate_score(original_dictionary[index]);
                        }
                    }
                }
                else break;
            }
            else j++;
        }
    }
    return maxscore.first;
}


int main() {
    /* 辞書を準備 */
    vector<string> original_dictionary;
    vector<pair<string,int> > sorted_dictionary;

    get_words("words.txt", original_dictionary);
    sort_dictionary(original_dictionary, sorted_dictionary);

    vector<vector<pair<char,int> > > count_dictionary(sorted_dictionary.size(),vector<pair<char,int> >(0));
    for (int i = 0; i < sorted_dictionary.size(); i++) {
        string w = sorted_dictionary[i].first;
        count_set(w, count_dictionary[i]);
    }

    /* 単語を準備 */
    vector<pair<char,int> > v;
    vector<string> wordlist;
    get_words("small.txt", wordlist);

    /* 書き出しの準備 */
    ofstream ifs("small_answer.txt");
	if (!ifs) {
		cout << "error : failed to open the text file." << endl;
	}

    /* 書き出し */
	for (int i = 0; i < wordlist.size(); i++) {
		ifs << search_anagram(wordlist[i], v, original_dictionary, sorted_dictionary, count_dictionary) << endl;
	}
    ifs.close();
}
