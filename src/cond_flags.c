#include "cond_flags.h"

typedef struct {
	bit unused : 28;
	bit v : 1;
	bit c : 1;
	bit z : 1;
	bit n : 1;
} flags_t;

typedef boolean (*emulator_condition)(flags_t flags);

void set_negative(uint32_t *reg) {
	((flags_t *) reg)->n = 1;
}

void clear_negative(uint32_t *reg) {
	((flags_t *) reg)->n = 0;
}

void set_zero(uint32_t *reg) {
	((flags_t *) reg)->z = 1;
}

void clear_zero(uint32_t *reg) {
	((flags_t *) reg)->z = 0;
}

boolean equal(flags_t flags) {
	return flags.z;
}

boolean not_equal(flags_t flags) {
	return !equal(flags);
}

boolean greater_equal(flags_t flags) {
	return flags.n == flags.v;
}

boolean less(flags_t flags) {
	return flags.n != flags.v;
}

boolean greater(flags_t flags) {
	return not_equal(flags) && greater_equal(flags);
}

boolean less_equal(flags_t flags) {
	return equal(flags) || less(flags);
}

boolean always(flags_t flags) {
	return 1;
}

boolean undefined(flags_t flags) {
	return 0;
}

emulator_condition condition_table[16] = {
	equal, not_equal, undefined, undefined, 	// 0000 to 0011
	undefined, undefined, undefined, undefined, // 0100 to 0111
	undefined, undefined, greater_equal, less,  // 1000 to 1011
	greater, less_equal, always, undefined 	    // 1100 to 1111
};


boolean cond_check(uint32_t cond, uint32_t reg) {
	
	flags_t flags = *(flags_t *) &reg;
	return condition_table[cond & 15](flags);
}
