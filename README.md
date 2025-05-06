# get_next_line

ファイルディスクリプタから1行ずつ読み込む関数 `get_next_line` を実装します。メモリ管理とバッファ制御の習得が目的です。

## ✅ 構成

- 関数名：`get_next_line`
- プロトタイプ：`char *get_next_line(int fd);`
- ファイル構成：
  - `get_next_line.c`, `get_next_line_utils.c`, `get_next_line.h`
- 読み取りは `BUFFER_SIZE` を用いて制御（`-D BUFFER_SIZE=42` など）

## 🔧 使用可能関数

- `read`
- `malloc`
- `free`

## 💎 ボーナス（任意）

- 静的変数は1つのみ使用
- 複数ファイルディスクリプタ（fd）を同時に扱えるようにする
- ボーナスファイル構成：
  - `get_next_line_bonus.c`
  - `get_next_line_bonus.h`
  - `get_next_line_utils_bonus.c`
