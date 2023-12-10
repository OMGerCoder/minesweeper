RESOURCEFILES = $(wildcard resources/*.*)
all: installer portable
	
installer: Game.exe $(RESOURCEFILES) inst.nsi
	mkdir -p dist
	makensis ./inst.nsi
portable: Game.exe $(RESOURCEFILES)
	mkdir -p dist
	"C:\Program Files\7-Zip\7z.exe" a -r ./dist/Minesweeper_portable.zip ./Game.exe ./resources
clean:
	rm -rf dist
.PHONY: all installer portable clean
