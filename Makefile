CPPFLAGS = -std=c++0x
OBJS = thestage.o stage_command.o onstage.o actor.o
GCC48 = /opt/bin/g++

onstage: $(OBJS)
	$(GCC48) -o onstage $(OBJS)

onstage.o: onstage.cpp
	$(GCC48) onstage.cpp -c $(CPPFLAGS)

thestage.o: thestage.cpp
	$(GCC48) -c thestage.cpp $(CPPFLAGS)

actor.o: actor.cpp
	$(GCC48) -c actor.cpp $(CPPFLAGS)

stage_command.o: stage_command.cpp
	$(GCC48) -c stage_command.cpp $(CPPFLAGS)

# `pkg-config --libs --cflags librsvg-2.0`

clean:
	rm -f onstage $(OBJS)