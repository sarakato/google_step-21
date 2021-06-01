## 宿題1

> Wikipediaのリンク構造を使って面白いことを見つける  
> 必須：”Google”から”渋谷”を(最短で)たどる経路を探す

## 準備

[wikipedia_data.zip](https://drive.google.com/file/d/1zqtjSb-ZoR4rzVUWZrjNSES5GKJhYmmH/view?usp=sharing) をダウンロードして解凍し、以下のようなディレクトリ構成にしてください。

```
step_wikipedia-graph
├── data
│   ├── graph_small.png
│   ├── links_small.txt
│   ├── links.txt
│   ├── pages_small.txt
│   └── pages.txt
├── .gitignore
├── README.md
├── wikipedia_sample.cc
├── wikipedia_sample.py
└── WikipediaSample.java
```

## 実行

step_wikipedia-graph に移動し以下を入力することで実行できます。  

```
g++ -std=c++11 wikipedia.cc && ./a.out
```

データ読み込みに5〜10分ほどかかります。  
読み込み完了後は以下のように探索を始めたいページ、辿り着きたいページを入力してください。

```
Enter start page : Google
Enter goal page : 渋谷
```

探索が実行され、最短の経路が表示されます。  
（今回の検索では15〜20分ほどかかりました）

最短経路はこのようになります。

```
Shows the route from "Google" to "渋谷".
Google (pageID : 457783)
セグウェイ (pageID : 154009)
渋谷 (pageID : 22557)
```

## その他

前回の講義で学んだモジュール化を意識して書きました。

