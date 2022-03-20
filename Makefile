build: *.Rmd
	Rscript -e "bookdown::render_book('index.Rmd', 'bookdown::gitbook')"
	Rscript -e "bookdown::render_book('index.Rmd', 'bookdown::pdf_book')"
	Rscript -e "bookdown::render_book('index.Rmd', 'bookdown::epub_book')"

clean:
	rm -rf docs _book

publish: clean build
	cp -r _book docs

.PHONY: clean publish
