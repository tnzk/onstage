CPPFLAGS = -std=c++0x `pkg-config --cflags cairo librsvg-2.0` -I./headers
OBJS = thestage.o stage_command.o stage_command_sync.o stage_command_null.o stage_command_move.o stage_command_enter.o stage_command_item.o onstage.o actor.o item.o
GCC48 = /opt/bin/g++

onstage: $(OBJS)
	$(GCC48) -o onstage $(OBJS) `pkg-config --libs cairo librsvg-2.0`

onstage.o: onstage.cpp
	$(GCC48) onstage.cpp -c $(CPPFLAGS)

thestage.o: thestage.cpp
	$(GCC48) -c thestage.cpp $(CPPFLAGS) 

actor.o: actor.cpp
	$(GCC48) -c actor.cpp $(CPPFLAGS)

item.o: item.cpp
	$(GCC48) -c item.cpp $(CPPFLAGS)

stage_command.o: stage_command.cpp
	$(GCC48) -c stage_command.cpp $(CPPFLAGS)
	$(GCC48) -c commands/stage_command_sync.cpp $(CPPFLAGS)
	$(GCC48) -c commands/stage_command_null.cpp $(CPPFLAGS)
	$(GCC48) -c commands/stage_command_move.cpp $(CPPFLAGS)
	$(GCC48) -c commands/stage_command_enter.cpp $(CPPFLAGS)
	$(GCC48) -c commands/stage_command_item.cpp $(CPPFLAGS)

clean:
	rm -f onstage $(OBJS)
