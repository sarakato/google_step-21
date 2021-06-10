## 宿題
巡回セールスマン問題(TSP)を解き、できるだけ良い解を見つける

### プログラム
- **solver_greedy_2opt.py**  
greedyアルゴリズムに2-opt法を組み合わせたプログラムを書きました。  
input_{0-6}.csvから都市の座標を読み込み、output_{0-6}.csvに周る順番を出力します。

- **output_verifier.py**  
移動距離のスコアを計算して出力します。

### 実行
```
% python3 solver_greedy.py input_x.csv    
```
x = 0~6として入力すると、output_{0-6}.csvに周る順番が出力されます。


```
% python3 output_verifier.py    
```
実行結果は以下のようになります。outputが今回のプログラムのスコアです。
```
Challenge 0
output          :    3418.10
sample/random   :    3862.20
sample/greedy   :    3418.10
sample/sa       :    3291.62

Challenge 1
output          :    3832.29
sample/random   :    6101.57
sample/greedy   :    3832.29
sample/sa       :    3778.72

Challenge 2
output          :    4994.89
sample/random   :   13479.25
sample/greedy   :    5449.44
sample/sa       :    4494.42

Challenge 3
output          :    8970.05
sample/random   :   47521.08
sample/greedy   :   10519.16
sample/sa       :    8150.91

Challenge 4
output          :   11489.79
sample/random   :   92719.14
sample/greedy   :   12684.06
sample/sa       :   10675.29

Challenge 5
output          :   21363.60
sample/random   :  347392.97
sample/greedy   :   25331.84
sample/sa       :   21119.55

Challenge 6
output          :   42712.37
sample/random   : 1374393.14
sample/greedy   :   49892.05
sample/sa       :   44393.89

```




