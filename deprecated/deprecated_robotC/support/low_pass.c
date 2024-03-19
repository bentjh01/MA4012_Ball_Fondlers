#include "low_pass.h"
// Low pass filter function
void low_pass_filter_init(LowPassFilter* filter, float alpha, float initial_output) {
    filter->alpha = alpha;
    filter->prev_output = initial_output;
}

float lowPassFilter(LowPassFilter* filter, float input) {
    filter->prev_output = (filter->alpha * input) + ((1 - filter->alpha) * filter->prev_output);
    return filter->prev_output;
}
