#ifndef MAIN_CORE_MODEL_H
#define MAIN_CORE_MODEL_H
// This class represents the actual performance model for a given core

#include <queue>
#include <iostream>
#include <string>

// Forward Decls
class Tile;
class BranchPredictor;

#include "instruction.h"
#include "basic_block.h"
#include "fixed_types.h"
#include "lock.h"
#include "dynamic_instruction_info.h"
#include "performance_model.h"

class MainCoreModel : protected CoreModel
{
public:
   //CoreModel(Tile* tile, float frequency);
   //virtual ~CoreModel();

   //void queueDynamicInstruction(Instruction *i);
   //void queueBasicBlock(BasicBlock *basic_block);
   //void iterate();

   //volatile float getFrequency() { return m_frequency; }
   //void updateInternalVariablesOnFrequencyChange(volatile float frequency);
   //void recomputeAverageFrequency(); 

   //UInt64 getCycleCount() { return m_cycle_count; }
   //void setCycleCount(UInt64 cycle_count);

   //void pushDynamicInstructionInfo(DynamicInstructionInfo &i);
   //void popDynamicInstructionInfo();
   //DynamicInstructionInfo& getDynamicInstructionInfo();

   //static CoreModel *create(Tile* tile);

   //BranchPredictor *getBranchPredictor() { return m_bp; }

   //void disable();
   //void enable();
   //bool isEnabled() { return m_enabled; }

   //virtual void outputSummary(std::ostream &os) = 0;

   //class AbortInstructionException { };

protected:
   friend class SpawnInstruction;

   typedef std::queue<DynamicInstructionInfo> DynamicInstructionInfoQueue;
   typedef std::queue<BasicBlock *> BasicBlockQueue;

   Tile* getCore() { return m_tile; }
   void frequencySummary(std::ostream &os);

   UInt64 m_cycle_count;

private:

   class DynamicInstructionInfoNotAvailableException { };

   virtual void handleInstruction(Instruction *instruction) = 0;

   Tile* m_tile;

   volatile float m_frequency;

   volatile float m_average_frequency;
   UInt64 m_total_time;
   UInt64 m_checkpointed_cycle_count;

   bool m_enabled;

   BasicBlockQueue m_basic_block_queue;
   Lock m_basic_block_queue_lock;

   DynamicInstructionInfoQueue m_dynamic_info_queue;
   Lock m_dynamic_info_queue_lock;

   UInt32 m_current_ins_index;

   BranchPredictor *m_bp;
};

#endif
