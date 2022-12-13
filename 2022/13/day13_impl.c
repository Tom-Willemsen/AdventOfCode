#include "day13_impl.h"

#define MAX_SUBPACKETS 16

static const uint64_t TYPE_INTEGER = 0;
static const uint64_t TYPE_SUBPACKET = 1;

typedef struct packet{
    int64_t marker;
    uint64_t type;
    int64_t integer;
    size_t size;
    struct packet** subpackets;
} packet;


static void free_packet(packet* packet) {
    if (packet->type == TYPE_SUBPACKET) {
        for (size_t i=0; i<MAX_SUBPACKETS; ++i) {
            if (packet->subpackets[i] != NULL) {
                free_packet(packet->subpackets[i]);
            }
        }
        free(packet->subpackets);
    }
    free(packet);
}

static packet* make_packet_from_single_int(int64_t integer) {
    packet* ret = calloc(1, sizeof(packet));
    ret->type = TYPE_SUBPACKET;
    ret->size = 1;
    ret->subpackets = calloc(MAX_SUBPACKETS, sizeof(packet*));
    ret->subpackets[0] = calloc(1, sizeof(packet));
    ret->subpackets[0]->type = TYPE_INTEGER;
    ret->subpackets[0]->integer = integer;
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
        if (p1->size < p2->size) {
            return 1;
        } else if (p1->size > p2->size) {
            return -1;
        }
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

static int qsort_comparator(const void* p1, const void* p2) {
    return comparator((packet*) p1, (packet*) p2);
}

static packet* parse_packet(char* data, size_t offset, size_t* parsed_size, int64_t marker) {
    size_t parsed = 0;
    char* endptr;
    
    packet* p = calloc(1, sizeof(packet));
    p->marker = marker;
    
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
        for (size_t i=0; i<MAX_SUBPACKETS; ++i) {
            p->subpackets[i] = NULL;
        }
        p->size = 0;
        assert(data[offset] == '[');
        parsed = 1;
        uint64_t n = 0;
        
        if (data[offset+parsed] != ']') {
            do {
                size_t ps = 0;
                if (data[offset + parsed] == ',') {
                    parsed += 1;
                }
                assert(n < MAX_SUBPACKETS);
                p->subpackets[n] = parse_packet(data, offset + parsed, &ps, marker);
                parsed += ps;
                n++;
            } while (data[offset + parsed] == ',');
        }
        p->size = n;
        assert(data[offset+parsed] == ']');
        parsed += 1;  // Trailing ']'
    } else {
        printf("unknown packet start in %s at offset %ld\n", data, offset + parsed);
    }
    (*parsed_size) += parsed;

    return p;
}

void calculate(char** data, uint64_t data_size, int64_t* part1, int64_t* part2) {
    packet** packets = calloc(data_size + 2, sizeof(packet*));
    
    uint64_t marker1_idx = 0;
    uint64_t marker2_idx = 0;
    
    int64_t pn = 0;
    for (size_t i=0; i<data_size; ++i) {
        if (strlen(data[i]) > 1) {
            uint64_t parsed_size = 0;
            packets[pn] = parse_packet(data[i], 0, &parsed_size, 0);
            assert(parsed_size == strlen(data[i]) - 1);
            pn++;
        }
    }
    
    for (uint64_t i=0; i<pn-1; i+=2) {
        if (comparator(packets[i], packets[i+1]) == 1) {
            *part1 += (i/2)+1;
        }
    }
    
    size_t parsed_size;
    packets[pn] = parse_packet("[[2]]", 0, &parsed_size, 1);
    packets[pn+1] = parse_packet("[[6]]", 0, &parsed_size, 2);
    
    printf("%ld %ld\n", pn+1, pn+2);
    
    // qsort(packets, pn, sizeof(packet*), qsort_comparator);
    
    for (uint64_t i=0; i<pn+2; ++i) {
        if (packets[i]->marker == 1) {
            marker1_idx = pn;
        } else if (packets[i]->marker == 2) {
            marker2_idx = pn;
        }
    }
    
    printf("%ld %ld\n", marker1_idx, marker2_idx);
    
    *part2 = (marker1_idx + 1) * (marker2_idx + 1);
    
    for (uint64_t i=0; i<data_size; ++i) {
        free(packets[i]);
    }
    free(packets);
}
