all:	clean compile checkstyle test


clean:
	rm -f GcdMain
	rm -f GcdTest

compile:
	clang++ -o GcdMain GcdMain.cpp
	clang++ -o GcdTest GcdTest.cpp -lgtest

test:
	./GcdTest

checkstyle:
	clang-format-14 --dry-run -Werror *.cpp