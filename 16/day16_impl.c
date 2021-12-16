#include "day16_impl.h"

static list_i64* get_bits(char* data) {
    int64_t v;
    list_i64* bits = list_i64_init(strlen(data) * 4);
    for (uint64_t i=0; i<strlen(data); ++i) {
        if (data[i] == '\n') {
            continue;
        }
        v = (data[i] >= '0' && data[i] <= '9') ? data[i] - '0' : data[i] + 10 - 'A';
        assert(v >=0 && v <= 0xF);
        for (uint64_t j=0; j<4; ++j) {
            list_i64_push_back(bits, v & (1 << (3-j)) ? 1 : 0);
        }
    }
    return bits;
}

static int64_t bin_to_int(list_i64* l, int64_t start, int64_t stop) {
    int64_t v = 0;
    for (uint64_t i=start; i<stop; ++i) {
        v = v*2+list_i64_get(l, i);
    }
    return v;
}

static void parse_literal(list_i64* data, uint64_t offset, int64_t* n_bits, int64_t* value) {
    int64_t i = 0;
    int64_t v = 0;
    while (list_i64_get(data, offset+6+i) == 1) {
        v <<= 4;
        v += bin_to_int(data, offset+7+i, offset+7+i+4);
        i += 5;
    }
    v <<= 4;
    v += bin_to_int(data, offset+7+i, offset+7+i+4);
    *n_bits = 6+i+5;
    *value = v;
}

static void parse_op(list_i64* data, uint64_t offset, int64_t* n_bits, int64_t* value, int64_t* version_sum) {
    uint8_t mode;
    int64_t size, length_of_subpackets = 0, n_subpackets = 0, op_type, header_len;
    list_i64* read_values = list_i64_init(5);
    int64_t read_length, read_value;
    
    if (list_i64_get(data, offset+6) == 1) {
        mode = PACKETS_MODE;
        header_len = 7+11;
    } else {
        mode = BITS_MODE;
        header_len = 7+15;
    }
    
    op_type = bin_to_int(data, offset+3, offset+6);
    size = bin_to_int(data, offset+7, offset+header_len);
    
    while ((mode == BITS_MODE && length_of_subpackets < size) || 
           (mode == PACKETS_MODE && n_subpackets < size)) 
    {
        parse_packet(data, offset+header_len+length_of_subpackets, &read_length, &read_value, version_sum);
        list_i64_push_back(read_values, read_value);
        length_of_subpackets += read_length;
        n_subpackets += 1;
    }
    
    if (op_type == OP_SUM) {
        *value = 0;
        for (uint64_t j=0; j<list_i64_size(read_values); ++j) {
            (*value) += list_i64_get(read_values, j);
        }
    } else if (op_type == OP_PRODUCT) {
        *value = 1;
        for (uint64_t j=0; j<list_i64_size(read_values); ++j) {
            (*value) *= list_i64_get(read_values, j);
        }
    } else if (op_type == OP_MIN) {
        *value = list_i64_min(read_values);
    } else if (op_type == OP_MAX) {
        *value = list_i64_max(read_values);
    } else if (op_type == OP_GT) {
        *value = (list_i64_get(read_values, 0) > list_i64_get(read_values, 1)) ? 1 : 0;
    } else if (op_type == OP_LT) {
        *value = (list_i64_get(read_values, 0) < list_i64_get(read_values, 1)) ? 1 : 0;
    } else if (op_type == OP_EQ) {
        *value = (list_i64_get(read_values, 0) == list_i64_get(read_values, 1)) ? 1 : 0;
    }
    
    *n_bits = header_len + length_of_subpackets;
    list_i64_free(read_values);
}


static void parse_packet(list_i64* data, uint64_t offset, int64_t* n_bits, int64_t* value, int64_t* version_sum) {
    int64_t type = bin_to_int(data, offset+3, offset+6);
    (*version_sum) += bin_to_int(data, offset, offset+3);
    if (type == 4) {
        parse_literal(data, offset, n_bits, value);
    } else {
        parse_op(data, offset, n_bits, value, version_sum);
    }
}

void calculate(char* data, int64_t* part1, int64_t* part2) {
    int64_t n_bits;
    *part1 = 0;
    *part2 = 0;
    list_i64* bits = get_bits(data);
    parse_packet(bits, 0, &n_bits, part2, part1);
    list_i64_free(bits);
}
