/* cache.c -- implementation of direct-mapped instruction cache */

/* You can add your implementation of a set-associative cache here */

#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "armemu.h"

/* Globals for cache */

/* Cache type: 0 - directed mapped, 1 - 4-way set associative */
int cache_type = 0;
/* (number of slots, where each slot holds a word) */
int cache_size = 0;

void cache_dm_init(struct cache_st *c, int cache_size) {
    c->num_slots = cache_size;

    /*
     * The number of bits for the slot index is variable in this cache
     * e.g. if we cache 8 words, we have 3 bits for the slot index
     * The mask is the number of ones to AND with to extract the index
     * e.g. if we're caching 8 words, the mask is 8-1 = 7, or 0b111
     */
    c->index_mask = cache_size - 1;
    verbose("  cache index mask: %d\n", c->index_mask);
    c->num_index_bits = 0;
    while (c->index_mask & (1 << c->num_index_bits))
        c->num_index_bits++;
    verbose("  cache num_index_bits: %d\n", c->num_index_bits);

    for (int s = 0; s < c->num_slots; s++)
        c->slots[s].valid = false;

    c->num_reqs = 0;
    c->num_hits = c->num_misses = 0;
    c->num_hot_misses = c->num_cold_misses = 0;
}

uint32_t cache_dm_fetch(struct cache_st *c, uint32_t *addr) {

    /* Didn't allocate any cache. I guess that's a miss?
     * This should not happen in our code as we don't simulate unless
     * cache_size > 0
     */
    if (0 == c->num_slots) {
        c->num_misses++;
        return *addr;
    }

    c->num_reqs += 1;    

    /* Skip over byte offset bits */
    uint32_t word_addr = (uint32_t) addr >> 2;
    /* Skip over index bits */
    uint32_t tag = word_addr >> c->num_index_bits;
    /* Get slot index */
    int s = word_addr & c->index_mask;
    struct cache_slot_st *slot = &c->slots[s];
    
    if (slot->valid) {
        if (tag == slot->tag) {
            verbose("  cache tag hit for slot %d tag %X addr %lX\n", s, tag, addr);
                if (slot->data != *addr) {
                    /* Sanity check */
                    printf("*** cache slot data doesn't match: %X != %X\n", slot->data, *addr);
                }
            c->num_hits++;
        }
        else {
            verbose("  cache tag (%X) miss for slot %d tag %X addr %X\n", slot->tag, s, tag, addr);
            c->num_misses++;
            /* Miss due to tage collision is a "hot" miss */
            c->num_hot_misses++;
            slot->data = *addr;
            slot->tag = tag;
        }
    }
    else {
        verbose("  cache slot %d not valid for tag %X addr %X\n", s, tag, addr);
        c->num_misses++;
        /* Miss due to invalid slot is a "cold" miss */
        c->num_cold_misses++;
        slot->data = *addr;
        slot->tag = tag;
        slot->valid = true;
    }
        
    return slot->data;
}

/* PUT YOUR SET ASSOCIATIVE IMPLEMENTATION HERE */

void cache_sa_init(struct cache_st *c, int cache_size) {
    return;
}

uint32_t cache_sa_fetch(struct cache_st *c, uint32_t *addr) {
    return *addr;
}

void cache_init(struct arm_state *asp, int cache_size) {
    if (cache_type == 0) {
        cache_dm_init(&(asp->cache), cache_size);
    } else if (cache_type == 1) {
        cache_sa_init(&(asp->cache), cache_size);
    }
}

uint32_t cache_fetch(struct arm_state *asp, uint32_t *addr) {
    uint32_t word;
    
    if (cache_type == 0) {
        word = cache_dm_fetch(&(asp->cache), addr);    
    } else if (cache_type == 1) {
        word = cache_sa_fetch(&(asp->cache), addr);
    }

    return word;
}

void cache_print(struct arm_state *asp) {
    struct cache_st *c = &(asp->cache);

    /* Nanoseconds, ballpark */
    const int hit_time = 3;
    const int miss_time = 100;
    
    int num_slots_used = 0;
    int i;

    for (i = 0; i < c->num_slots; i++) {
        if (c->slots[i].valid == 1) {
            num_slots_used += 1;
        }
    }

    printf("\n");
    printf("===Cache Analysis===\n");
    printf("Number of requests       = %d\n", c->num_reqs);
    printf("Number of hits           = %d\n", c->num_hits);
    printf("Number of misses         = %d\n", c->num_misses);
    printf("Number of misses (cold)  = %d\n", c->num_cold_misses);
    printf("Number of misses (hot)   = %d\n", c->num_hot_misses);
    printf("Hit Ratio                = %.2f%%\n", ((float) c->num_hits / (float) c->num_reqs) * 100.0);
    printf("Miss Ratio               = %.2f%%\n", ((float) c->num_misses / (float) c->num_reqs) * 100.0);
    printf("Percent of cache used    = %.2f%%\n", ((float) num_slots_used / (float) c->num_slots) * 100.0);
    printf("Approximat time (ns)     = %d\n", (hit_time * c->num_hits) + (miss_time * c->num_misses));
    

}
