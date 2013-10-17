CPPFLAGS = -std=c++0x `pkg-config --cflags cairo`
OBJS = thestage.o stage_command.o stage_command_sync.o stage_command_null.o stage_command_move.o stage_command_enter.o onstage.o actor.o
GCC48 = /opt/bin/g++

onstage: $(OBJS)
	$(GCC48) -o onstage $(OBJS) `pkg-config --libs cairo`

onstage.o: onstage.cpp
	$(GCC48) onstage.cpp -c $(CPPFLAGS)

thestage.o: thestage.cpp
	$(GCC48) -c thestage.cpp $(CPPFLAGS) 

actor.o: actor.cpp
	$(GCC48) -c actor.cpp $(CPPFLAGS)

stage_command.o: stage_command.cpp
	$(GCC48) -c stage_command.cpp $(CPPFLAGS)
	$(GCC48) -c stage_command_sync.cpp $(CPPFLAGS)
	$(GCC48) -c stage_command_null.cpp $(CPPFLAGS)
	$(GCC48) -c stage_command_move.cpp $(CPPFLAGS)
	$(GCC48) -c stage_command_enter.cpp $(CPPFLAGS)

# `pkg-config --libs --cflags librsvg-2.0`

clean:
	rm -f onstage $(OBJS)