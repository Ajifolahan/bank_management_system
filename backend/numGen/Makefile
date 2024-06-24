CC = gcc
CFLAGS = -I/opt/homebrew/opt/openssl@3/include -I/opt/homebrew/opt/libmicrohttpd/include
LDFLAGS = -L/opt/homebrew/opt/openssl@3/lib -L/opt/homebrew/opt/libmicrohttpd/lib
LDLIBS = -lssl -lcrypto -lmicrohttpd

TARGET = run
SOURCES = generate_acct_num.c

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES) $(LDFLAGS) $(LDLIBS)

clean:
	rm -f $(TARGET)
