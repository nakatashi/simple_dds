# Simple DDS controller
RedPitaya上で実装したDDSのコントローラ。
## インストール
プロジェクトのルートで
```
make
```
を実行すると、
"rp_dds.h"が/usr/local/include/に、"librp_dds.a"が/usr/local/lib/に配置される。


## 使用
生成したライブラリを使用した、ソースコード(ここではmain.c)をコンパイルするには次を実行する。
```
gcc -o main.out main.c -lrp_dds
```

## サンプルプログラム
main.cは動作確認用のプログラムデ、
```
make test
```
によりコンパイルされる。

周波数25MHz、振幅係数0.4の出力を生成する。

