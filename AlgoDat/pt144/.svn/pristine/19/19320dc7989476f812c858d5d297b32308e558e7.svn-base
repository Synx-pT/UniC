.PHONY: all checkstyle compile test clean

# Default target executed when no arguments are given to make.
all: checkstyle compile test

# Target for checking style with flake8.
checkstyle:
	@echo "Checking Python style with flake8..."
	flake8 MergeSort.py

# Target for syntax check or pre-compilation step
compile:
	@echo "Performing Python syntax check..."
	python3.12 -m py_compile MergeSort.py

# Target for running unit tests with pytest and doctest.
test:
	@echo "Running doctests..."
	python3.12 -m doctest MergeSort.py

# Target to clean up the project.
clean:
	@echo "Cleaning up..."
	rm -f *.pyc
	rm -rf __pycache__
