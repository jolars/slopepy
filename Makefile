all: install

install:
	pip install -e .

clean:
	rm -rf *.so src/*.o src/*.so __pycache__

test:
	python -m unittest discover

document:
	sphinx-apidoc -o docs/source pyslope ;\
	cd docs ;\
	make html latexpdf
