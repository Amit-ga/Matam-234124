CC = gcc
EM_OBJS = auxilaries.o date.o event.o event_manager.o list.o student.o
EM_EXEC = event_manager
PQ_OBJS=list.o priority_queue.o
PQ_EXEC = priority_queue
DEBUG_FLAG = # now empty, assign -g for debug
COMP_FLAG = -std=c99 -Wall -pedantic-errors -Werror 
PQ_IMPORT= -L. -lpriority_queue

$(EM_EXEC) : $(EM_OBJS)
	$(CC) $(COMP_FLAG) $(DEBUG_FLAG) $(EM_OBJS) tests/event_manager_tests.c $(PQ_IMPORT) -o $@
$(PQ_EXEC) : $(PQ_OBJS)
	$(CC) $(COMP_FLAG) $(DEBUG_FLAG) $(PQ_OBJS) tests/priority_queue_tests.c -o $@
event_manager.o: event_manager.c event_manager.h date.h priority_queue.h \
 list.h event.h auxiliaries.h student.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c 
priority_queue.o: priority_queue.c priority_queue.h list.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c
auxilaries.o: auxilaries.c auxiliaries.h event.h date.h priority_queue.h \
 student.h list.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c
date.o: date.c date.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c
event.o: event.c event.h date.h priority_queue.h auxiliaries.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c
list.o: list.c list.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c
student.o: student.c student.h date.h list.h auxiliaries.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c
clean:
	rm -f $(EM_OBJS) $(EM_EXEC)
	rm -f $(PQ_OBJS) $(PQ_EXEC)	