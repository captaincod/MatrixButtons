#include "mbed.h"
#include <chrono>

using namespace std::chrono_literals;

BusInOut rows(PA_0, PA_1, PA_2, PA_3);
BusInOut cols(PA_5, PA_6, PA_7);
BusOut leds(PB_5, PB_4, PB_3, PA_15);

int main() {
    rows.mode(PullUp);
    cols.mode(PullDown);

    while (true) {
        rows.input();
        cols.output();

        int row_number = rows & rows.mask();
        if (row_number == 0xE) row_number = 1;
        else if (row_number == 0xD) row_number = 2;
        else if (row_number == 0xB) row_number = 3;
        else if (row_number == 0x7) row_number = 4;
        else row_number = -1;

        cols.input();
        rows.output();

        int col_number = cols & cols.mask();
        if (col_number == 0x1) col_number = 1;
        else if (col_number == 0x2) col_number = 2;
        else if (col_number == 0x4) col_number = 3;
        else col_number = -1;

        int mask = row_number + 2 * col_number;
        if (mask > -1) {
            leds = mask;
        }
        else mask = 0;
        ThisThread::sleep_for(100ms);
    }
}