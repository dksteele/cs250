<<<<<<< HEAD
### CS250 Introduction to C Programming<br> Capitol Technology University
--
### Project 2 <br>

#### Chat Broadcast Client and Server in C

We are going to program a chat client program and the associated server program in this project. The user requirements are simple: a message entered into a client should be broadcast to all other clients. Conceptually, the client is a simple UDP client while the server is a broadcast echo program.

Specific technical requirements include:

(Client)
1. Accept hostname or IP address & port number as parameters
2. If given a hostname, convert into an IP Address (report errors).
3. Open a UDP socket (report errors).
4. Read a message input by the user.
5. Send the message (report errors). 
  a. To ensure that we can track messages, append a timestamp to the message before sending.
6. Receive messages from the server (report errors). 
  a. Do not display messages that you sent.
7. Continue operating until the user terminates the program.


(Server)
1. Accept hostname or IP address & port number as parameters
2. Open a UDP Socket (report errors).
3. Receive messages from clients (report errors).
4. Send the received message to all clients using a broadcast.
  a. There are two valid ways to send using a broadcast address. Either is fine for this project.
  b. Ensure that you set the correct socket structure options so that you have permissions to use a broadcast.
5. Continue operating until the user terminates the program.
=======
### CS250 Introduction to C Programming<br> Capitol Technology University
--
### Project 2 <br>

#### Chat Broadcast Client and Server in C

We are going to program a chat client program and the associated server program in this project. The user requirements are simple: a message entered into a client should be broadcast to all other clients. Conceptually, the client is a simple UDP client while the server is a broadcast echo program.

Specific technical requirements include:

(Client)
1. Accept hostname or IP address & port number as parameters
2. If given a hostname, convert into an IP Address (report errors).
3. Open a UDP socket (report errors).
4. Read a message input by the user.
5. Send the message (report errors). 
  a. To ensure that we can track messages, append a timestamp to the message before sending.
6. Receive messages from the server (report errors). 
  a. Do not display messages that you sent.
7. Continue operating until the user terminates the program.


(Server)
1. Accept hostname or IP address & port number as parameters
2. Open a UDP Socket (report errors).
3. Receive messages from clients (report errors).
4. Send the received message to all clients using a broadcast.
  a. There are two valid ways to send using a broadcast address. Either is fine for this project.
  b. Ensure that you set the correct socket structure options so that you have permissions to use a broadcast.
5. Continue operating until the user terminates the program.
>>>>>>> refs/remotes/jasonmpittman/master
