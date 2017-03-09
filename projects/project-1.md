### CS250 Introduction to C Programming<br> Capitol Technology University
--
### Project 1<br>

#### Simple HTTP Client & Server in C

We are going to program a simple HTTP client and HTTP server for this project. While the HTTP protocol consists of a robust feature set, we only need to implement the most basic version of a HTTP GET request. That is, the client will send a 'request' for a specific resource such as webpage.html and the server will return the corresponding content. 


The Client:

1. Your client must include the following requirements:

2. Accept a hostname and port as command arguements (i.e., client hostname 80).

3. Convert the hostname into an IP address. Report "hostname error" if unsuccessful.

4. Open a socket connection with the server. Report "unable to connect" on failure.

5. Read a command from the user. You can assume the command is the file name that the user wants to retrieve (e.g. index.html).

6. Send data to the server (using your protocol). Report "server not responding" if the connection appears to be dead.

7. Wait for the server's response. Be sure to implement behavior that avoids blocking conditions!

8. Handle data sent by the server. The contents of the HTTP resource should be printed to stdout correctly. For example, if the target resource consists of two lines separated by a newline then the client must render correctly [Be sure to test at least a single line and a double line!].

9. Close the socket connection and exit the program. 



The Server:

1. Create a listening socket based on the command arguments (e.g. server 80)

2. Accept a connection from a client. 

3. Fork a child process to service the connection, whilst the parent process goes back to accept more connections.

4. Read a HTTP request from a connected client. Because we are building a very simple HTTP server, just handle the incoming file name. You can assume that the target file (e.g. index.html) is in the same directory as the server.

5. Send the file requested (e.g. index.html) if the file exists. Otherwise, return an appropriate error condition to the client (e.g., file not found).

6. Continue accepting connections until the user terminates the server process.
