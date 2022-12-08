#include "day08_impl.h"

void calculate(uint8_t** data, uint64_t x_size, uint64_t y_size, int64_t* part1, int64_t* part2) {
    *part1 = 2 * x_size + 2 * (y_size - 2);
    
    for (uint64_t row=1; row<y_size-1; ++row) {
        for (uint64_t col=1; col<x_size-1; ++col) {
            uint8_t ch = data[row][col];
            int64_t d1=1, d2=1, d3=1, d4=1;
            uint8_t v1 = (data[row][0] < ch);
            uint8_t v2 = (data[row][x_size-1] < ch);
            uint8_t v3 = (data[0][col] < ch);
            uint8_t v4 = (data[y_size-1][col] < ch);
            
            for (int64_t c=col-1; c>0; --c) {
                if (data[row][c] < ch) {
                    d1++;
                } else {
                    v1 = 0;
                    break;
                }
            }
            
            for (int64_t c=col+1; c<x_size-1; ++c) {
                if (data[row][c] < ch) {
                    d2++;
                } else {
                    v2 = 0;
                    break;
                }
            }
            
            for (int64_t r=row-1; r>0; --r) {
                if (data[r][col] < ch) {
                    d3++;
                } else {
                    v3 = 0;
                    break;
                }
            }
            
            for (int64_t r=row+1; r<y_size-1; ++r) {
                if (data[r][col] < ch) {
                    d4++;
                } else {
                    v4 = 0;
                    break;
                }
            }
            
            *part1 += v1||v2||v3||v4;
            *part2 = max(*part2, d1*d2*d3*d4);
        }
    }
}
