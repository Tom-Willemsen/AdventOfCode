#include "day18_impl.h"
#include <omp.h>

static const int64_t NODE_TYPE_CONST = 1;
static const int64_t NODE_TYPE_PAIR = 2;

typedef struct SFNumberNode {
    int64_t type;
    int64_t value;
    struct SFNumberNode* left;
    struct SFNumberNode* right;
} SFNumberNode;

static SFNumberNode* parse_from_str(char* s, int64_t offset, int64_t* parsed_size) {
    SFNumberNode* node = calloc(1, sizeof(SFNumberNode));
    if (s[offset] == '[') {
        int64_t size_l, size_r;
        node->type = NODE_TYPE_PAIR;
        node->left = parse_from_str(s, offset+1, &size_l);
        assert(s[offset+1+size_l] == ',');
        node->right = parse_from_str(s, offset+size_l+2, &size_r);
        assert(s[offset+2+size_l+size_r] == ']');
        *parsed_size = 3 + size_l + size_r;
    } else {
        node->type = NODE_TYPE_CONST;
        char* endptr;
        node->value = strtol(s + offset, &endptr, 10);
        *parsed_size = endptr - (s + offset);
    }
    return node;
}

static void free_node_tree(SFNumberNode* node) {
    if (node->type == NODE_TYPE_PAIR) {
        free_node_tree(node->left);
        free_node_tree(node->right);
    }
    free(node);
}

static int64_t add_to_leftmost(SFNumberNode* node, int64_t add) {
    if (node->type == NODE_TYPE_PAIR) {
        return add_to_leftmost(node->left, add);
    } else {
        node->value += add;
        return 1;
    }
}

static int64_t add_to_rightmost(SFNumberNode* node, int64_t add) {
    if (node->type == NODE_TYPE_PAIR) {
        return add_to_rightmost(node->right, add);
    } else {
        node->value += add;
        return 1;
    }
}

static int64_t explode(SFNumberNode* node, int64_t depth, int64_t* add_on_left, int64_t* add_on_right) {
    if (node->type == NODE_TYPE_PAIR) {
        if (depth >= 4) {
            assert(node->left->type == NODE_TYPE_CONST);
            assert(node->right->type == NODE_TYPE_CONST);
            
            *add_on_left = node->left->value;
            *add_on_right = node->right->value;
            
            free_node_tree(node->left);
            free_node_tree(node->right);
            node->type = NODE_TYPE_CONST;
            node->value = 0;
            return 1;
        } else {
            int64_t add_l, add_r;
            int64_t l_exploded=0, r_exploded=0;
            
            l_exploded = explode(node->left, depth+1, &add_l, &add_r);
            
            if (add_r != 0 && add_to_leftmost(node->right, add_r)) {
                add_r = 0;
            } 
            if (!l_exploded) {
                r_exploded = explode(node->right, depth+1, &add_l, &add_r);
                if (add_l != 0 && add_to_rightmost(node->left, add_l)) {
                    add_l = 0;
                }
            }
            *add_on_left = add_l;
            *add_on_right = add_r;
            return l_exploded || r_exploded;
        }
    } else {
        *add_on_right = 0;
        *add_on_left = 0;
        return 0;
    }
}

static int64_t split(SFNumberNode* node) {
    if (node->type == NODE_TYPE_PAIR) {
        return split(node->left) || split(node->right);
    } else {
        if (node->value >= 10) {
            node->type = NODE_TYPE_PAIR;
            node->left = calloc(1, sizeof(SFNumberNode));
            node->left->type = NODE_TYPE_CONST;
            node->right = calloc(1, sizeof(SFNumberNode));
            node->right->type = NODE_TYPE_CONST;
            
            node->left->value = node->value / 2;
            node->right->value = (node->value+1) / 2;
            return 1;
        } else {
            return 0;
        }
    }
}

static int64_t can_explode(SFNumberNode* node, int64_t depth) {
    if (node->type == NODE_TYPE_PAIR) {
        return depth >= 4 || can_explode(node->left, depth+1) || can_explode(node->right, depth+1);
    } else {
        return 0;
    }
}

static int64_t can_split(SFNumberNode* node) {
    if (node->type == NODE_TYPE_PAIR) {
        return can_split(node->left) || can_split(node->right);
    } else {
        return node->value >= 10;
    }
}

static int64_t magnitude(SFNumberNode* node) {
    if (node->type == NODE_TYPE_PAIR) {
        return 3*magnitude(node->left) + 2*magnitude(node->right);
    } else {
        return node->value;
    }
}

static void reduce_number(SFNumberNode* node) {
    int64_t can_reduce = 1, add_l, add_r;
    
    while (can_reduce) {
        if (can_explode(node, 0)) {
            explode(node, 0, &add_l, &add_r);
        } else if (can_split(node)) {
            split(node);
        } else {
            can_reduce = 0;
        }
    }
}

static SFNumberNode* add(SFNumberNode* left, SFNumberNode* right) {
    SFNumberNode* node = calloc(1, sizeof(SFNumberNode));
    node->type = NODE_TYPE_PAIR;
    node->left = left;
    node->right = right;
    reduce_number(node);
    return node;
}

static SFNumberNode* parse_and_reduce(char* data) {
    int64_t parsed_size;
    SFNumberNode* node = parse_from_str(data, 0, &parsed_size);
    reduce_number(node);
    return node;
}

void calculate(char** data, uint64_t data_size, int64_t* part1, int64_t* part2) {
    int64_t biggest_sum = 0;
    assert(data_size >= 2);
    
    SFNumberNode* sum = parse_and_reduce(data[0]);
    for (uint64_t i=1; i<data_size; ++i) {
        sum = add(sum, parse_and_reduce(data[i]));
    }
    *part1 = magnitude(sum);
    free_node_tree(sum);
    
    #pragma omp parallel for shared(data, data_size)
    for (uint64_t i=0; i<data_size; ++i) {
        for (uint64_t j=0; j<data_size; ++j) {
            SFNumberNode* sum = add(parse_and_reduce(data[i]), parse_and_reduce(data[j]));
            int64_t m = magnitude(sum);
            #pragma omp critical
            {
                biggest_sum = max(biggest_sum, m);
            }
            free_node_tree(sum);
        }
    }
    *part2 = biggest_sum;
}
