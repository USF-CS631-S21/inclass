#define ARMEMU_DEBUG 0
#define MAX_INSTRUCTION_COUNT 1000000

#define NREGS 16
#define STACK_SIZE 4096
#define SP 13
#define LR 14
#define PC 15

/* Simple logging */
void verbose_init(bool);
void verbose(char *fmt, ...);

/* Cache simulation  */

#define CACHE_MAX_SLOTS 2048

struct cache_slot_st {
    bool valid;
    uint32_t tag;
    uint32_t data;
    uint32_t timestamp;
};

/* Add to this struct if needed to support 4-way set associative */
struct cache_st {
    struct cache_slot_st slots[CACHE_MAX_SLOTS];
    int num_slots;
    uint32_t index_mask;
    uint32_t num_index_bits;
    int num_reqs;
    int num_hits;
    int num_misses;
    int num_hot_misses;
    int num_cold_misses;
};

/* The complete machine state */
struct arm_state {
    uint32_t regs[NREGS];
    uint32_t cpsr;
    uint8_t stack[STACK_SIZE];
    bool cache_on;
    int cache_type;
    struct cache_st cache;
};

/* Initialize an arm_state struct with a function pointer and arguments */
void armemu_init(struct arm_state *asp, uint32_t *fp,
                    uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3);
int armemu(struct arm_state *asp);
void armemu_print(struct arm_state *asp);

void cache_init(struct arm_state *asp, int cache_size);
uint32_t cache_fetch(struct arm_state *asp, uint32_t *addr);
void cache_print(struct arm_state *asp);
