#include <stdio.h>
#include <stddef.h>
#include <string.h>

#define TCP_IP_LAYER_COUNT 4
#define PAYLOAD_SIZE 128
#define LAYER_NAME_SIZE 32
#define HEADER_DESCRIPTION_SIZE 96

typedef struct {
    char layer_name[LAYER_NAME_SIZE];
    char description[HEADER_DESCRIPTION_SIZE];
} LayerHeader;

typedef struct {
    char payload[PAYLOAD_SIZE];
    LayerHeader headers[TCP_IP_LAYER_COUNT];
    size_t header_count;
} Packet;

/* The order here is the sending host's encapsulation order. */
static const LayerHeader example_headers[TCP_IP_LAYER_COUNT] = {
    {"Application", "HTTP message: GET /index.html"},
    {"Transport", "TCP segment: source port 51514, destination port 80"},
    {"Internet", "IPv4 packet: source 192.0.2.10, destination 198.51.100.20"},
    {"Network Access", "Ethernet frame: source and destination MAC addresses"}
};

static int encapsulate(Packet *packet)
{
    size_t i;

    if (packet == NULL || packet->header_count != 0) {
        return 0;
    }

    for (i = 0; i < TCP_IP_LAYER_COUNT; ++i) {
        packet->headers[packet->header_count] = example_headers[i];
        ++packet->header_count;
        printf("%-16s adds its information: %s\n",
               example_headers[i].layer_name,
               example_headers[i].description);
    }

    return 1;
}

static int decapsulate(Packet *packet)
{
    if (packet == NULL || packet->header_count != TCP_IP_LAYER_COUNT) {
        return 0;
    }

    puts("\nReceiver removes headers in reverse order:");
    while (packet->header_count > 0) {
        const LayerHeader *header = &packet->headers[packet->header_count - 1];
        printf("%-16s processes and removes its information\n", header->layer_name);
        --packet->header_count;
    }

    return 1;
}

int main(void)
{
    Packet packet = {0};

    (void)snprintf(packet.payload, sizeof(packet.payload), "%s", "Hello from the application!");

    printf("Original application data: %s\n\n", packet.payload);
    puts("Sender encapsulates data:");
    if (!encapsulate(&packet)) {
        fputs("Could not encapsulate the packet.\n", stderr);
        return 1;
    }

    printf("\nData is ready for transmission with %zu layer headers.\n", packet.header_count);
    if (!decapsulate(&packet)) {
        fputs("Could not decapsulate the packet.\n", stderr);
        return 1;
    }

    printf("\nApplication receives the original data: %s\n", packet.payload);
    return 0;
}
