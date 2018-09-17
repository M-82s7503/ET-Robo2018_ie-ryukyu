CC            = gcc
CFLAGS        = 
LIBS          = -lc++
OBJS          = test_main.o PatternMatcher.o answer_arrays.o
PROGRAM       = ptMatch

$(PROGRAM):     $(OBJS)
	$(CC) $(OBJS) $(LIBS) -o $(PROGRAM)

clean:;         rm -f *.o *~ $(PROGRAM)
