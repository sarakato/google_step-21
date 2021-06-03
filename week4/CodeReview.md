## CodeReview (To Hikari Fujimoto)

### はじめに
普段あまりPythonを触らないので何か見当違いなレビューをしていたらすみません。  
Pythonの文法に詳しくない自分でも見やすいコードでした！:)

### 良いと感じた点
- 変数名、関数名の付け方  
どれも汎用性がありわかりやすかったです！  
何を指しているか、何をする関数なのか一目で理解できました。

- モジュール化  
これ以上分けられないくらいまで分割できていて全体的に読みやすかったです。

- 目的のものが見つからなかった時の処理  
```raise Exception ("Item not found")```や```raise Exception("Path not found")``` で例外を発生させる処理の仕方にあまり馴染みがなかったので、面白いなと思いました。  
自分ではエラーメッセージを出力する処理しか思いつかなかったので勉強になりました！

### 改善できそうな点
- 現在のコードだと"Google"から"渋谷"への検索に固定されているので、入力を自由に受け付けるようにすると汎用性が高くなるのではないかなと思いました！  
既にfind_id()という関数を作っているので少しの変更でできると思います。

### その他
- 私のコード(C++)では"Google"から"渋谷"までのルート検索だと"Google"→"セグウェイ"→"渋谷"のルートしか出てこないので、複数のルートが出てくるのは何による違いなのか気になりました。(言語によるもの？)  
  
___

I'm not very good at English, so I apologize if my grammar is wrong.

### Introduction
I don't usually work with Python, so I'm sorry if I'm giving a misguided review of something.   
The code was easy to read, even for someone like me who doesn't know much about Python syntax!:)

### Good points
- Variable names, function names  
They were all versatile and easy to understand!  
I was able to understand at a glance what they pointed to and what the function was supposed to do.

- Modularization  
The program could be divided up to the point where it couldn't be divided any further.

- What to do when the desired item is not found  
I was not familiar with the ```raise Exception ("Item not found")``` or ```raise Exception("Path not found")```, so I thought it was interesting.  
I could only think of processing that would output an error message, so I learned a lot!

### Points that could be improved
- In the current code, the search is fixed to "Google" to "渋谷", so I thought it would be more versatile if it accepts any input.  
You have already created the find_id() function, so I think you can do it with a few changes.

### Other
- In my code (C++), when searching for a route from "Google" to "渋谷", I only get the route "Google" -> "セグウェイ" -> "渋谷".  
I was wondering what the difference was.  
