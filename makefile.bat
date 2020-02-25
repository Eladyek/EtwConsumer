g++ -O2 -o EtwConsumer.o -c EtwConsumer.cpp
g++ -O2 -o cEtwConsumer.o -c cEtwConsumer.cpp
ar r libEtwConsumer.a EtwConsumer.o cEtwConsumer.o
go build .
