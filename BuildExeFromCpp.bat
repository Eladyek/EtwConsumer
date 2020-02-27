mkdir Debug
cd Debug
g++ -c ../EtwConsumer.cpp ../TraceSession.cpp ../TraceConsumer.cpp ../Common.cpp
g++ -o cppEtwConsumer.exe EtwConsumer.o TraceSession.o TraceConsumer.o Common.o