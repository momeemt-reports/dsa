# dsa 
[![CI](https://github.com/momeemt/dsa/actions/workflows/ci.yml/badge.svg)](https://github.com/momeemt/dsa/actions/workflows/ci.yml)
[![Generate Documents](https://github.com/momeemt/dsa/actions/workflows/generate-documents.yml/badge.svg)](https://github.com/momeemt/dsa/actions/workflows/generate-documents.yml)

データ構造とアルゴリズム

## Docs
https://momeemt.github.io/dsa/

## Develop
開発には以下のソフトウェアが必要です。

- gcc
- gnumake
- [CUnit](https://cunit.sourceforge.net/)

Nixコマンドが利用可能である場合は、以下のコマンドで開発環境に入れます。

```sh
$ nix-shell
```

## Build
Makefileを用いてビルドする場合には[CUnit](https://cunit.sourceforge.net/)をインストールして、以下のコマンドを実行してください。

```sh
$ make
```

Nixコマンドが利用可能である場合は、以下のコマンドを実行すると`result/bin/`以下にバイナリが生成されます。

```sh
$ nix-build
```

## LICENSE
- MIT OR Apache-2.0

## Author
- [Mutsuha Asada](https://github.com/momeemt)
