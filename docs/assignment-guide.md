# TCP/IP Model: C Demonstration

This repository contains a small, educational C program that demonstrates how data is encapsulated and decapsulated across the four layers of the TCP/IP model.

## Program

`src/tcp_ip_model.c` models each layer's header and stores the headers in an array inside a `Packet` structure. During encapsulation, headers are added from the Application layer down to the Network Access layer. During decapsulation, they are removed in reverse order.

The program is a conceptual simulation; it does not open sockets or send real network traffic.

## Build and run

```sh
gcc -std=c11 -Wall -Wextra -pedantic src/tcp_ip_model.c -o tcp_ip_model
./tcp_ip_model
```

## Data structures and logic

- `LayerHeader` stores the name of a TCP/IP layer and an example header description.
- `Packet` stores the application payload and a fixed-size array of layer headers.
- `encapsulate()` adds one header for each layer, demonstrating the downward flow of data.
- `decapsulate()` removes headers from the top of the array, demonstrating the receiving host's upward flow.

An array is suitable here because the model has a known, fixed number of layers and their processing order is sequential. A structure groups the related packet fields together.

## Example layer roles

1. **Application** — protocols such as HTTP, DNS, and SSH provide network services to applications.
2. **Transport** — TCP or UDP supports communication between processes using port numbers.
3. **Internet** — IP addresses and routes packets between networks; routers operate primarily at this layer.
4. **Network Access** — technologies such as Ethernet and Wi-Fi carry frames over a local link; switches and network interface cards are relevant examples.

The header values in the source are illustrative only.
