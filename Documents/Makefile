.PHONY: all clean

TEX_FILES := $(wildcard *.tex)
PDF_FILES := $(TEX_FILES:.tex=.pdf)
BUILD_DIR := build

all: $(PDF_FILES)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

%.pdf: %.tex | $(BUILD_DIR)
	latexmk -pdf -pdflatex="pdflatex -interaction=nonstopmode" -outdir=$(BUILD_DIR) -use-make $<
	mv $(BUILD_DIR)/$@ .
	pkill -HUP mupdf || true

clean:
	latexmk -C
	rm -rf $(BUILD_DIR)
