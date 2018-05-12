CC = gcc
TARGET = enter_recovery
all: $(TARGET)

$(TARGET) : enter_recovery.c
	$(CC) $< -o $@ -limobiledevice

clean :
	rm -rf $(TARGET)
