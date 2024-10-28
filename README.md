# プログレスメーカー

プログレスバーで遊ぼう

## 概要

このプロジェクトは、 Qt についての理解を深めるために作成されたものです。  
以前、Hot Soup Processor で似たようなものを開発したことがあり(残念ながらそのプログラムは失われてしまいましたが)、それを Qt で再度開発しました。

## ビルド

まず、必要なものが揃っているかどうかを確認してください。おそらく必須となるのは次のとおりです:
- CMake
- お好みのビルドツール
	- ninja
	- makefile
	- etc...
- ご家庭でお持ちのC++コンパイラ
	- clang++
	- g++
	- etc...
- Qt (5,もしくは6)
	- Core
	- Widgets
	- LinguistTools

必要な道具が揃っていたら、このリポジトリをpullしてください。
```sh
git pull https://github.com/zawa-ch/stress-progress
```

食材の準備ができたみたいです。
pullしたディレクトリに入り、`cmake`で料理しましょう。
```sh
cd stress-progress
cmake -S ./ -B build
cmake --build build --target all
```

上手に料理ができたら、`build`ディレクトリ内に完成品があるはずです。
このまま美味しく召し上がれます。
```sh
build/stress-progress
```
