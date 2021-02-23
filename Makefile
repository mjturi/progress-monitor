
# Matthew Turi
# ID: 822202323

CXX = g++ 
CXXFLAGS += -std=c++11 

myls : wordcount.o 
	$(CXX) wordcount.o -o wordcount -pthread

myls.o : myls.cpp
	$(CXX) $(CXXFLAGS) -c wordcount.cpp -pthread

clean :
	rm *.o

