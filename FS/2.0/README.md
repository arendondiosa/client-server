# File System

## Compile and run

```bash
make
```
### Run Server

```bash
./server.out
```

### Run Client(s)
```bash
./client.out
```

## Basic commands

### Add
Add a file. If a file exit in server, it will replace.
_Files will saved in `files/username/` (Server path)_
```bash
>>$ add file
```

### get
Get a file from the server.
_Files will saved in `downloads/` (Client path)_
```bash
>>$ get file
```

### rm
Remove a file from the server.
```bash
>>$ rm file
```

### ls
Get a list _(In this version with format JSON)_ from server with the user files.
```bash
>>$ ls
```

### exit

Close the user session and the connection with the server.

```bash
>>$ exit
```

## Dependencies

### [ZMQ](https://github.com/zeromq/zmqpp)

### [JSON](https://github.com/nlohmann/json)

_Notes:_

_* This version only sends files from the folder where the client.out is located._

_* Please report bugs in [![Github Issues](https://img.shields.io/github/issues/aerendon/client-server.svg)](http://github.com/aerendon/client-server/issues)_ 
