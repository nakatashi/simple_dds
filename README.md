# Simple DDS controller
RedPitaya上で実装したDDSのコントローラ。
プロジェクトのルートで
```
make
```
を実行すると、
"rp_dds.h"が/usr/local/include/に、"librp_dds.a"が/usr/local/lib/に配置される。

生成したライブラリを使用したmain.cをコンパイルするには次を実行する。
```
gcc -o main.out main.c -lrp_dds
```


```
make test
```
では、周波数25MHz、振幅係数0.4の出力を生成する実行ファイルを生成する。

