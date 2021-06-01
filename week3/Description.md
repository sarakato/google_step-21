## 宿題1

### 問題
> モジュール化されたプログラムを変更して、「*」「/」に対応しよう
> - 例: 3.0 + 4 * 2 − 1 / 5
> - 細かい仕様は好きに定義してください

### 解答

まずはメイン関数に乗算、除算のみ先に計算する`temp = evaluate_multidiv(tokens)`の1行を追加する。  
それに伴い上下の行の引数も変更も行なった。

###
~~~
while True:
	print('> ', end="")
	line = input()
	tokens = tokenize(line)
	temp = evaluate_multidiv(tokens) # 追加
	answer = evaluate_plusminus(temp)
	print("answer = %f\n" % answer)
~~~
###

次に各関数の中身について考えていく。  
まず字句に分割する関数`tokenize()`を「*」「/」に対応するようにアップデートする。  

具体的には、`read_multiply()`と`read_divide()`という2つの関数を新たに定義することで対応した。

###
~~~
def tokenize(line):
...
	elif line[index] == '*':
		(token, index) = read_multiply(line, index)
	elif line[index] == '/':
		(token, index) = read_divide(line, index)
...
~~~
###

~~~
def read_multiply(line, index):
	token = {'type': 'MULTIPLY'}
	return token, index + 1

def read_divide(line, index):
	token = {'type': 'DIVIDE'}
	return token, index + 1
~~~
###

最後に字句を引数にとり乗算、除算のみ計算して字句の形で返す関数、`evaluate_multidiv()`を定義する。  
以下のような流れで実装を行なった。

1. まず`evaluate_plusminus()`と同じように与えられた字句配列の先頭に {'type': 'PLUS'} を追加し、空の配列tempを用意しておく。  

1. 一つ目のwhile文で、与えられた字句を前から見ていき「+」「-」型、あるいは一つ前が「+」「-」である数字型ならtempに追加する。  
一つ前が「*」「/」である数字型なら二つ目のwhile文に突入する。  

1. 二つ目のwhile文では一つ前が「*」ならばtempの最後の要素の数字に対して現在見ている字句の数字をかけることで数字を更新する。  
「/」の場合も同様にして数字を更新する。  

1. この先この項で乗算、除算が続くか調べるためにindexを2増やし再び二つ目のwhile文に入る。  
乗算、除算が終了するか字句を最後まで見終わったら(flag)このwhile文から抜ける。

1. 最後に字句を最後まで見終わっていたら(flag)一つ目のwhile文からも抜け、見終わっていなかったらindexを1増やして再び一つ目のwhile文に入る。  
また二つ目のwhile文でどこまで乗算、除算が続くか調べるために増やしたindexは元に戻しておく(flag2)

###
~~~
def evaluate_multidiv(tokens):
	tokens.insert(0, {'type': 'PLUS'})
	temp = []
	index = 0

	flag = False # 最後の項が乗算、除算で終わったとき全体のwhile文から抜けるためのflag
	while index < len(tokens):
		flag2 = False # 2つ目のwhile文でどこまで乗算、除算が続くか調べるために大きくしたindexを戻すためのflag
		if tokens[index - 1]['type'] == 'PLUS' or tokens[index - 1]['type'] == 'MINUS':
				temp.append(tokens[index])
		elif tokens[index - 1]['type'] == 'MULTIPLY' or tokens[index - 1]['type'] == 'DIVIDE':
			while tokens[index - 1]['type'] == 'MULTIPLY' or tokens[index - 1]['type'] == 'DIVIDE':
				if tokens[index - 1]['type'] == 'MULTIPLY':
					temp[-1]['number'] = temp[-1]['number'] * tokens[index]['number']
					index += 2
					flag2 = True
				elif tokens[index - 1]['type'] == 'DIVIDE':
					temp[-1]['number'] = temp[-1]['number'] / tokens[index]['number']
					index += 2
					flag2 = True
				if index >= len(tokens):
					flag = True
					break
		elif tokens[index]['type'] == 'PLUS' or tokens[index]['type'] == 'MINUS':
			temp.append(tokens[index])
		if flag:
			break
		if flag2:
			index -= 2
		index += 1
	return temp
~~~

## 宿題2

### 問題
> 書いたプログラムが正しく動いていることを確認するためのテストケースを追加しよう

### 解答

`test()`、`run_test()`を以下のように追加、変更した。

~~~
def test(line):
	tokens = tokenize(line)
	temp = evaluate_multidiv(tokens)
	actual_answer = evaluate_plusminus(temp)
	expected_answer = eval(line)
	if abs(actual_answer - expected_answer) < 1e-8:
		print("PASS! (%s = %f)" % (line, expected_answer))
	else:
		print("FAIL! (%s should be %f but was %f)" % (line, expected_answer, actual_answer))


# Add more tests to this function :)
def run_test():
	print("==== Test started! ====")
	test("1")
	test("1+2")
	test("1.0+2.1-3")
	test("2*3")
	test("2.0*3.0")
	test("6/4")
	test("6.0/4.0")
	test("6*7/2.0")
	test("3.0+6*5.5/2-7/1.0/5*6")
	print("==== Test finished! ====\n")
~~~
###

実行結果はこのようになり、宿題1の実装の成功が確認できた。

###
~~~
% python3 modularized_calculator.py
==== Test started! ====
PASS! (1 = 1.000000)
PASS! (1+2 = 3.000000)
PASS! (1.0+2.1-3 = 0.100000)
PASS! (2*3 = 6.000000)
PASS! (2.0*3.0 = 6.000000)
PASS! (6/4 = 1.500000)
PASS! (6.0/4.0 = 1.500000)
PASS! (6*7/2.0 = 21.000000)
PASS! (3.0+6*5.5/2-7/1.0/5*6 = 11.100000)
==== Test finished! ====

> 
~~~

## 宿題3

### 問題
> 括弧に対応しよう 
> - 例: (3.0 + 4 * (2 − 1)) / 5
> - テストケースも追加してください 

### 解答

新たに modularized_calculator2.py を作成する。

方針として、式に()が存在するとき最も内側の()を見つけ出してその中身を宿題1と同様に処理し、  
それを()がなくなるまで続け、なくなったら全体を1と同様に処理するというように考えた。

まずはメイン関数を書き換える。  
`exist_brackets()`で()が存在するか調べ、`evaluate_brackets()`で最も内側の()の中身を処理することにした。

###
~~~
while True:
    print('> ', end="")
    line = input()
    tokens = tokenize(line)

    while exist_brackets(tokens) == True: # ()が存在する限り回す
        tokens = evaluate_brackets(tokens) # ()の中身を計算する

    temp = evaluate_multidiv(tokens)
    answer = evaluate_plusminus(temp)
    print("answer = %f\n" % answer)
~~~
###

次に読み込むときに「(」「)」に対応するように変更した。

###
~~~
def tokenize(line):
...
	elif line[index] == ‘(‘:
		(token, index) = read_Lbracket(line, index)
	elif line[index] == ‘)’:
		(token, index) = read_Rbracket(line, index)
...
~~~
###

~~~
def read_Lbracket(line, index):
    token = {'type': 'Lbracket'}
    return token, index + 1

def read_Rbracket(line, index):
    token = {'type': 'Rbracket'}
    return token, index + 1

~~~
###

最後に`exist_brackets()`と`evaluate_brackets()`を定義する。

まず`exist_brackets()`は、与えられた字句を前から見ていき「(」を見つけたらTrueを返す関数である。  
existというフラグを立てて実装した。

###
~~~
def exist_brackets(tokens):
    exist = False
    for i in range(len(tokens)):
        if tokens[i]['type'] == 'Lbracket':
            exist = True
            break
    return exist
~~~
###

そして`evaluate_brackets()`は次のような流れで()の中身を処理する関数である。

1. 最も内側の()を見つけ出し、左括弧と右括弧の場所(L_index, R_index)を保存する。
1. tokensを前から見ていき [L_index-1] までは要素を新しく用意した配列new_tokensに追加する。
1. [L_index]まで到達したら、()内の要素 (tokens[L_index + 1 : R_index]) を `evaluate_multidiv()`と`evaluate_plusminus()`を使って計算し、new_tokensに追加する。indexは()の次の要素まで進めておく。
1. 残りの要素をnew_tokensに追加する。


1は以下のように`inner_brackets()`という関数を別に定義した。  

最も内側の()とは、先頭から見て一番はじめに現れた右括弧と、それに対応する左括弧のペアのことである。  
つまり与えられた字句を先頭から見ていき右括弧が現れたら現在のindexをR_indexに保存、  
そこから今度は前に戻りながら見ていき左括弧が現れたら現在のindexをL_indexに保存することで位置を保存した。

###
~~~
def inner_brackets(tokens):
    index = 0
    fin = False
    while index < len(tokens):
        if tokens[index]['type'] == 'Rbracket':
            R_index = index
            while index >= 0:
                if tokens[index]['type'] == 'Lbracket':
                    L_index = index
                    fin = True
                    break
                index -= 1
        if fin: break
        index += 1
    return L_index, R_index
~~~
###

`evaluate_brackets()`では最初に`inner_brackets()`を呼び出し、while文で2〜4までを実装した。

###
~~~
def evaluate_brackets(tokens):
    new_tokens = []
    inner = []
    index = 0

    L_index, R_index = inner_brackets(tokens) # 最も内側の()の位置を保存

    while index < len(tokens):
        if index == L_index:
            inner = tokens[L_index + 1 : R_index]
            temp = evaluate_multidiv(inner)
            answer = evaluate_plusminus(temp)
            new_tokens.append({'type': 'NUMBER', 'number': answer})
            index += R_index - L_index + 1

        else:
            new_tokens.append(tokens[index])
            index += 1
    return new_tokens
~~~
###

最後にテストケースの追加、変更を行った。  
`test()`の中身はメイン関数と同様の変更をし、テストケースは以下のように追加を行なった。

###
~~~
def run_test():
    print("==== Test started! ====")
...
    test("(8)")
    test("(9+2.6)")
    test("6*(9+2)")
    test("(3.0+4*(2-1))/5")
    test("(8.3*6-9)*2-6/(7-4)")
    test("2-8*((4-2)*4-(8-4*6*(8+2)))")
    print("==== Test finished! ====\n")
~~~

結果は全てPASSとなり、今回の実装の成功を確認できた。
