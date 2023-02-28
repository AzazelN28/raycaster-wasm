all:
	clang-15 -target wasm32 -nostdlib -Wl,--no-entry -Wl,--export-all -Wl,--allow-undefined -o raycaster.wasm vec2f.c vec2i.c view.c ray.c raycaster.c backdrop.c screen.c
