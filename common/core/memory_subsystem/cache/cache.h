#ifndef CACHE_H
#define CACHE_H

#include <string>
#include <cassert>

#include "cache_base.h"
#include "cache_set.h"
#include "cache_block_info.h"
#include "utils.h"
#include "hash_map_set.h"
#include "cache_perf_model.h"
#include "shmem_perf_model.h"
#include "log.h"

class Cache : public CacheBase
{
   private:
      bool m_enabled;

      // Cache counters
      UInt64 m_num_accesses;
      UInt64 m_num_hits;
      UInt64 m_num_evicts;

      //elau PEP Cache counters
      UInt64 m_num_pep_accesses;
      UInt64 m_num_pep_hits;
      UInt64 m_num_pep_evicts;

      UInt64 m_num_both_evicts;
      UInt64 m_num_total_evicts;

      UInt64 m_num_pep_insertions;
      UInt64 m_num_main_insertions;

      UInt64 m_num_pep_fills;
      UInt64 m_num_main_fills;
      // Generic Cache Info
      //
      cache_t m_cache_type;
      CacheSet** m_sets;
      
   public:

      // constructors/destructors
      Cache(string name, 
            UInt32 cache_size, 
            UInt32 associativity, UInt32 cache_block_size,
            std::string replacement_policy,
            cache_t cache_type);
      ~Cache();

      bool invalidateSingleLine(IntPtr addr);
      CacheBlockInfo* accessSingleLine(IntPtr addr, 
            access_t access_type, Byte* buff = NULL, UInt32 bytes = 0);
      void insertSingleLine(IntPtr addr, Byte* fill_buff,
            bool* eviction, IntPtr* evict_addr, 
            CacheBlockInfo* evict_block_info, Byte* evict_buff);
      CacheBlockInfo* peekSingleLine(IntPtr addr);

      // Update Cache Counters
      void updateCounters(bool cache_hit);
      //elau
      void updatePepCounters(bool cache_hit);
      void incrMainEvict() {m_num_evicts++;}
      void incrPepEvict() {m_num_pep_evicts++;}
      void incrBothEvict() {m_num_both_evicts++;}
      void incrTotalEvicts() {m_num_total_evicts++;}
      void incrPepInsertion() {m_num_pep_insertions++;}
      void incrMainInsertion() {m_num_main_insertions++;}
      void incrPepFill() {m_num_pep_fills++;}
      void incrMainFill() {m_num_main_fills++;}

      void enable() { m_enabled = true; }
      void disable() { m_enabled = false; } 

      virtual void outputSummary(ostream& out);
};

template <class T>
UInt32 moduloHashFn(T key, UInt32 hash_fn_param, UInt32 num_buckets)
{
   return (key >> hash_fn_param) % num_buckets;
}

#endif /* CACHE_H */
