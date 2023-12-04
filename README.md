# dsa

[![CI](https://github.com/momeemt/dsa/actions/workflows/ci.yml/badge.svg)](https://github.com/momeemt/dsa/actions/workflows/ci.yml)
[![Generate Documents](https://github.com/momeemt/dsa/actions/workflows/generate-documents.yml/badge.svg)](https://github.com/momeemt/dsa/actions/workflows/generate-documents.yml)

興味があるデータ構造やアルゴリズムを実装したり挙動を確かめるサンドボックスとして使っています。
このリポジトリに記述されたプログラムが正確に動作することは保証しません。

## Docs

Doxygen で生成しています。

- https://momeemt.github.io/dsa/

## Develop

開発には以下のソフトウェアが必要です。

- gcc
- gnumake
- [CUnit](https://cunit.sourceforge.net/)

Nix コマンドが利用可能である場合は、以下のコマンドで開発環境に入れます。

```sh
$ nix-shell
```

## Build

Makefile を用いてビルドする場合には[CUnit](https://cunit.sourceforge.net/)をインストールして、以下のコマンドを実行してください。

```sh
$ make
```

Nix コマンドが利用可能である場合は、以下のコマンドを実行すると`result/bin/`以下にバイナリが生成されます。

```sh
$ nix-build
```

## Get Started

このリポジトリで実装されたプログラムをライブラリとして使う手順を説明します。

## LICENSE

- MIT OR Apache-2.0

## Author

- [Mutsuha Asada](https://github.com/momeemt)
