CXX := g++
CC := gcc
CXXFLAGS := -Wall -Wextra -O2 -std=c++17
CFLAGS := -Wall -Wextra -O2 -std=c17
DEBUGFLAGS :=
NDEBUGFLAGS := -DNDEBUG

# Object files
STRQUEUE_DBG_O := strqueue_dbg.o
STRQUEUE_NODBG_O := strqueue_nodbg.o
TEST1_O := strqueue_test_1.o
TEST2_O := strqueue_test_2.o

# Executables
TEST1_DBG := strqueue_test_1_dbg
TEST1_NODBG := strqueue_test_1_nodbg
TEST2_DBG_A := strqueue_test_2_dbg_a
TEST2_DBG_B := strqueue_test_2_dbg_b
TEST2_NODBG := strqueue_test_2_nodbg

all: $(TEST1_DBG) $(TEST1_NODBG) $(TEST2_DBG_A) $(TEST2_DBG_B) $(TEST2_NODBG)

# Compile object files
$(STRQUEUE_DBG_O): strqueue.cpp strqueue.h
	$(CXX) $(CXXFLAGS) $(DEBUGFLAGS) -c strqueue.cpp -o $@

$(STRQUEUE_NODBG_O): strqueue.cpp strqueue.h
	$(CXX) $(CXXFLAGS) $(NDEBUGFLAGS) -c strqueue.cpp -o $@

$(TEST1_O): strqueue_test_1.c strqueue.h
	$(CC) $(CFLAGS) -c strqueue_test_1.c -o $@

$(TEST2_O): strqueue_test_2.cpp strqueue.h
	$(CXX) $(CXXFLAGS) -c strqueue_test_2.cpp -o $@

# Link executables
$(TEST1_DBG): $(TEST1_O) $(STRQUEUE_DBG_O)
	$(CXX) $^ -o $@

$(TEST1_NODBG): $(TEST1_O) $(STRQUEUE_NODBG_O)
	$(CXX) $^ -o $@

$(TEST2_DBG_A): $(TEST2_O) $(STRQUEUE_DBG_O)
	$(CXX) $^ -o $@

$(TEST2_DBG_B): $(STRQUEUE_DBG_O) $(TEST2_O)
	$(CXX) $^ -o $@

$(TEST2_NODBG): $(TEST2_O) $(STRQUEUE_NODBG_O)
	$(CXX) $^ -o $@

clean:
	rm -f *.o $(TEST1_DBG) $(TEST1_NODBG) $(TEST2_DBG_A) $(TEST2_DBG_B) $(TEST2_NODBG)
