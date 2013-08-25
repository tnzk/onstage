CPPFLAGS = -std=c++0x
OBJS = thestage.o stage_command.o onstage.o actor.o

onstage: $(OBJS)
	g++ onstage.cpp -c $(CPPFLAGS)
	g++ -o onstage $(OBJS)

thestage: thestage.cpp
	g++ thestage.cpp -c $(CPPFLAGS)

actor: actor.cpp
	g++ actor.cpp -c $(CPPFLAGS)

stage_command: stage_command.cpp
	g++ stage_command.cpp -c $(CPPFLAGS)

# `pkg-config --libs --cflags librsvg-2.0`

clean:
	rm -f onstage $(OBJS)