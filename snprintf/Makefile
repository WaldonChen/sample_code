CC = cc
CFLAGS := -D

SOURCE = snprintf.c
TARTGET_SAFE = safe-print
TARTGET_UNSAFE = unsafe-print

.PHONY: all
all:	$(TARTGET_SAFE) $(TARTGET_UNSAFE) 
	@echo "Generate the safe and unsafe version."
	
$(TARTGET_SAFE):	$(SOURCE)
	$(CC) $(CFLAGS) SAFE_VERSION $(SOURCE) -o $(TARTGET_SAFE)
	
$(TARTGET_UNSAFE):	$(SOURCE)
	$(CC) $(CFLAGS) UNSAFE_VERSION $(SOURCE) -o $(TARTGET_UNSAFE)

clean:
	-rm $(TARTGET_SAFE) $(TARTGET_UNSAFE)
