<h1 align="center">
  minitalk
</h1>

---

## About the project

> _The purpose of this project is to code a small data exchange program using UNIX signals._


## Usage

### Requirements

The function is written in C language and thus needs the **`cc` compiler** and some standard **C libraries** to run.

### Instructions

**1. Compiling the library**

To compile, go to the library path and run:

```shell
make
```

## Testing

To test the program, simply start the "server" and "client" in separate shell tabs as follows:

```shell
./server
```

It displays your PID to work the client and waits to receive messages from the "client".

```shell
./client "PID" "Your messages"
```

Starting this, "Your messages" appears in the server window.
