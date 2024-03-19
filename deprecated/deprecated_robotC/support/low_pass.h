#ifndef LOW_PASS_H
#define LOW_PASS_H

typedef struct {
  float alpha;
  float prev_output;
} LowPassFilter;

void low_pass_init(LowPassFilter *lp, float alpha, float init);
float low_pass_update(LowPassFilter *lp, float input);

#endif /*LOW_PASS_H*/