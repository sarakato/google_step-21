#! /usr/bin/python3

def read_number(line, index):
  number = 0
  while index < len(line) and line[index].isdigit():
    number = number * 10 + int(line[index])
    index += 1
  if index < len(line) and line[index] == '.':
    index += 1
    decimal = 0.1
    while index < len(line) and line[index].isdigit():
      number += int(line[index]) * decimal
      decimal /= 10
      index += 1
  token = {'type': 'NUMBER', 'number': number}
  return token, index


def read_plus(line, index):
  token = {'type': 'PLUS'}
  return token, index + 1


def read_minus(line, index):
  token = {'type': 'MINUS'}
  return token, index + 1

def read_multiply(line, index):
  token = {'type': 'MULTIPLY'}
  return token, index + 1

def read_divide(line, index):
  token = {'type': 'DIVIDE'}
  return token, index + 1


def tokenize(line):
  tokens = []
  index = 0
  while index < len(line):
    if line[index].isdigit():
      (token, index) = read_number(line, index)
    elif line[index] == '+':
      (token, index) = read_plus(line, index)
    elif line[index] == '-':
      (token, index) = read_minus(line, index)
    elif line[index] == '*':
      (token, index) = read_multiply(line, index)
    elif line[index] == '/':
      (token, index) = read_divide(line, index)
    else:
      print('Invalid character found: ' + line[index])
      exit(1)
    tokens.append(token)
  return tokens


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


def evaluate_plusminus(tokens):
  answer = 0
  tokens.insert(0, {'type': 'PLUS'}) # Insert a dummy '+' token
  index = 1


  while index < len(tokens):
    if tokens[index]['type'] == 'NUMBER':
      if tokens[index - 1]['type'] == 'PLUS':
        answer += tokens[index]['number']
      elif tokens[index - 1]['type'] == 'MINUS':
        answer -= tokens[index]['number']
      else:
        print('Invalid syntax')
        exit(1)
    index += 1
  return answer


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

run_test()

while True:
  print('> ', end="")
  line = input()
  tokens = tokenize(line)
  temp = evaluate_multidiv(tokens)
  answer = evaluate_plusminus(temp)
  print("answer = %f\n" % answer)