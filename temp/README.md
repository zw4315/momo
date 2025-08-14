
# momoDDD final (.h headers, optional SQLite)

## Build
```bash
cmake -S . -B build
cmake --build build -j
./build/momo_cli
```
- Default adapter: file (CSV) at `tags.csv`.
- To use SQLite (if dev package installed):  
  `MOMO_REPO=sqlite MOMO_SQLITE_PATH=tags.db ./build/momo_cli`

## Commands
- `add <name>`
- `addtag <YYYY-MM-DD> [tag]` (default `default`)
- `view <YYYY-MM-DD> <YYYY-MM-DD>` → prints day difference
- `get <name>`
- `list`
- `help`, `quit`
