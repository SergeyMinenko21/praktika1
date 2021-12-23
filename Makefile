all:
	g++ -c -Wall practice.cpp
	g++ -o app practice.o
exec:
	luit -encoding ru_RU.CP1251 ./app