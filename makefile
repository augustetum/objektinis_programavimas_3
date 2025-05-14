CXX = g++ #kompiliatorius
CXXFLAGS = -std=c++17 -I$(CATCH_PATH) #kompiliatoriaus veliaveles
CATCH_PATH = /opt/homebrew/Cellar/catch2/3.8.1/include

EXEC0 = konteineriuTyrimas
EXEC1 = 1strategija
EXEC2 = 2strategija
EXEC3 = 3strategija
EXEC4 = programa
TEST_EXEC = testavimas

all: $(EXEC0) $(EXEC1) $(EXEC2) $(EXEC3) $(EXEC4) $(TEST_EXEC)

$(EXEC0): programaFunkcijos.o konteineriuTyrimas.o
	$(CXX) $(CXXFLAGS) -o $(EXEC0) programaFunkcijos.o konteineriuTyrimas.o

$(EXEC1): programaFunkcijos.o strategija1.o
	$(CXX) $(CXXFLAGS) -o $(EXEC1) programaFunkcijos.o strategija1.o

$(EXEC2): programaFunkcijos.o strategija2.o
	$(CXX) $(CXXFLAGS) -o $(EXEC2) programaFunkcijos.o strategija2.o

$(EXEC3): programaFunkcijos.o strategija3.o
	$(CXX) $(CXXFLAGS) -o $(EXEC3) programaFunkcijos.o strategija3.o

$(EXEC4): programaFunkcijos.o programa.o
	$(CXX) $(CXXFLAGS) -o $(EXEC4) programaFunkcijos.o programa.o

$(TEST_EXEC): catchTests.o programaFunkcijos.o 
	$(CXX) $(CXXFLAGS) -o $(TEST_EXEC) catchTests.o programaFunkcijos.o -L/opt/homebrew/Cellar/catch2/3.8.1/lib -lCatch2Main -lCatch2

konteineriuTyrimas.o: 1_strategija/konteineriuTyrimas.cpp
	$(CXX) $(CXXFLAGS) -c 1_strategija/konteineriuTyrimas.cpp -o konteineriuTyrimas.o

strategija1.o: 1_strategija/strategija1.cpp
	$(CXX) $(CXXFLAGS) -c 1_strategija/strategija1.cpp -o strategija1.o

strategija2.o: 1_strategija/strategija2.cpp
	$(CXX) $(CXXFLAGS) -c 1_strategija/strategija2.cpp -o strategija2.o

strategija3.o: 1_strategija/strategija3.cpp
	$(CXX) $(CXXFLAGS) -c 1_strategija/strategija3.cpp -o strategija3.o

programa.o: programa.cpp
	$(CXX) $(CXXFLAGS) -c programa.cpp -o programa.o

catchTests.o: catchTests.cpp studentClass.h
	$(CXX) $(CXXFLAGS) -I$(CATCH_PATH) -c catchTests.cpp -o catchTests.o

clean:
	rm -f *.o $(EXEC0) $(EXEC1) $(EXEC2) $(EXEC3) $(EXEC4) $(TEST_EXEC)

runT: $(EXEC0)
	./$(EXEC0)

run1: $(EXEC1)
	./$(EXEC1)

run2: $(EXEC2)
	./$(EXEC2)

run3: $(EXEC3)
	./$(EXEC3)

runP: $(EXEC4)
	./$(EXEC4)

test: $(TEST_EXEC)
	./$(TEST_EXEC)