all: install

install:
	pip install -v .

clean:
	rm -rf *.so src/*.o src/*.so __pycache__ build dist

test:
	python -m unittest discover

document:
	sphinx-apidoc -o docs/source slopepy ;\
	cd docs ;\
	make html latexpdf
