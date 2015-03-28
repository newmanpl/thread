ifeq (,$(tg))
  tg=test1
endif

CC = gcc
CXX = g++
CFLAGS = `pkg-config --cflags --libs gtk+-2.0`

ifeq ($(tg),test1)
thread: thread.cc
	$(CXX) -o $@ $^ $(CFLAGS)
	@echo "build thread"
endif
.PHONY: clean
clean:
#	-rm *.o test
	-rm thread
