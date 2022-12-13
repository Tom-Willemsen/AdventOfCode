#include "day13_impl.h"

#define MAX_SUBPACKETS 8

static const uint64_t TYPE_INTEGER = 0;
static const uint64_t TYPE_SUBPACKET = 1;

typedef struct packet{
    uint64_t type;
    int64_t integer;
    size_t size;
    struct packet** subpackets;
} packet;


static void free_packet(packet* packet) {
    if (packet->type == TYPE_SUBPACKET) {
        for (size_t i=0; i<packet->size; ++i) {
            free_packet(packet->subpackets[i]);
        }
        free(packet->subpackets);
    }
    free(packet);
}

static packet* make_packet_from_single_int(int64_t integer) {
    packet* int_packet = calloc(1, sizeof(packet));
    int_packet->type = TYPE_INTEGER;
    int_packet->integer = integer;
    
    packet* ret = calloc(1, sizeof(packet));
    ret->type = TYPE_SUBPACKET;
    ret->size = 1;
    ret->subpackets = calloc(1, sizeof(packet*));
    ret->subpackets[0] = int_packet;
    return ret;
}

static int comparator(const packet* p1, const packet* p2) {
    if (p1->type == TYPE_INTEGER && p2->type == TYPE_INTEGER) {
        return i64sign(p2->integer - p1->integer);
    } else if (p1->type == TYPE_SUBPACKET && p2->type == TYPE_SUBPACKET) {
        for (size_t i=0; i < p1->size && i < p2->size; ++i) {
            int comp = comparator(p1->subpackets[i], p2->subpackets[i]);
            if (comp != 0) {
                return comp;
            }
        }
        return i64sign(p2->size - p1->size);
    } else if (p1->type == TYPE_INTEGER && p2->type == TYPE_SUBPACKET) {
        packet* temp = make_packet_from_single_int(p1->integer);
        int result = comparator(temp, p2);
        free_packet(temp);
        return result;
    } else {
        packet* temp = make_packet_from_single_int(p2->integer);
        int result = comparator(p1, temp);
        free_packet(temp);
        return result;
    }
    return 0;
}

static packet* parse_packet(char* data, size_t offset, size_t* parsed_size) {
    size_t parsed = 0;
    char* endptr;
    
    packet* p = calloc(1, sizeof(packet));
    
    if(data[offset] >= '0' && data[offset] <= '9') {
        p->type = TYPE_INTEGER;
        p->integer = strtol(data + offset + parsed, &endptr, 10);
        p->size = 0;
        p->subpackets = NULL;
        parsed += endptr - (data + offset + parsed);
    } else if (data[offset] == '[') {
        p->type = TYPE_SUBPACKET;
        p->integer = INT64_MIN;
        p->subpackets = calloc(MAX_SUBPACKETS, sizeof(packet*));
        p->size = 0;
        assert(data[offset] == '[');
        parsed = 1;
        
        if (data[offset+parsed] != ']') {
            do {
                size_t ps = 0;
                if (data[offset + parsed] == ',') {
                    parsed += 1;
                }
                assert(p->size <= MAX_SUBPACKETS);
                p->subpackets[p->size] = parse_packet(data, offset + parsed, &ps);
                parsed += ps;
                p->size++;
            } while (data[offset + parsed] == ',');
        }
        assert(data[offset+parsed] == ']');
        parsed += 1;  // Trailing ']'
    } else {
        printf("unknown packet start in %s at offset %ld\n", data, offset + parsed);
        abort();
    }
    (*parsed_size) += parsed;

    return p;
}

void calculate(char** data, uint64_t data_size, int64_t* part1, int64_t* part2) {
    uint64_t num_packets = 0, p = 0;
    
    for (size_t i=0; i<data_size; ++i) {
        if (data[i][0] == '[') {
            num_packets++;
        }
    }
    
    assert(num_packets % 2 == 0 && num_packets > 0);
    
    packet** packets = calloc(num_packets, sizeof(packet*));
    
    for (size_t i=0; i<data_size; ++i) {
        if (data[i][0] == '[') {
            uint64_t parsed_size = 0;
            packets[p] = parse_packet(data[i], 0, &parsed_size);
            assert(parsed_size == strlen(data[i]) - 1);
            p++;
        }
    }
    
    for (size_t i=0; i<num_packets-1; i+=2) {
        if (comparator(packets[i], packets[i+1]) == 1) {
            *part1 += (i/2)+1;
        }
    }
    
    size_t parsed_size = 0;
    packet* marker1 = parse_packet("[[2]]", 0, &parsed_size);
    assert(parsed_size == 5);
    parsed_size = 0;
    packet* marker2 = parse_packet("[[6]]", 0, &parsed_size);
    assert(parsed_size == 5);
    
    int64_t p2_1=0, p2_2=0;
    for (size_t i=0; i<num_packets; ++i) {
        if (comparator(packets[i], marker1) == 1) {
            p2_1++;
        }
        if (comparator(packets[i], marker2) == 1) {
            p2_2++;
        }
    }
    
    if (comparator(marker1, marker2) == -1) {
        p2_1++;
    } else {
        p2_2++;
    }
    
    *part2 = (p2_1 + 1) * (p2_2 + 1);
    
    free_packet(marker1);
    free_packet(marker2);
    for (size_t i=0; i<num_packets; ++i) {
        free_packet(packets[i]);
    }
    free(packets);
}
