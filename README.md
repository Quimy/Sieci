Http 1.0 Server 
RFC: https://tools.ietf.org/html/rfc1945

Server compilation:
1. Compile using cmake 'cmake ..'.
2. Then 'make'.
3. Start serwer with './httpServer'

Root folder for server is /serverRoot.

Server works on port 7070.

Running tests:
1. In /tests run: cat 'filename_with_request' | nc localhost 7070.