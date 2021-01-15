#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "tlb.h"
#include "cpu.h"
#include "mmu.h"

typedef struct{
  unsigned int vbit_and_vpage;  
  unsigned int mr_pframe;       
} TLB_ENTRY;

TLB_ENTRY *tlb;  

unsigned int num_tlb_entries;
unsigned int mod_tlb_entries_mask;
BOOL tlb_miss; 

#define VBIT_MASK   0x80000000  
#define VPAGE_MASK  0x000FFFFF            
#define RBIT_MASK   0x80000000  
#define MBIT_MASK   0x40000000  
#define PFRAME_MASK 0x000FFFFF            

void tlb_initialize(){
  tlb = (TLB_ENTRY *) malloc(num_tlb_entries * sizeof(TLB_ENTRY));
  mod_tlb_entries_mask = num_tlb_entries - 1;  
  tlb_miss = 0;
  int i;
  for(i = 0; i < num_tlb_entries; i++){
    tlb[i].vbit_and_vpage = 0x0;
    tlb[i].mr_pframe = 0x0;
  }
}

void tlb_clear_all() 
{
  int i;
  for(i = 0; i < num_tlb_entries; i++){
    tlb[i].vbit_and_vpage = (tlb[i].vbit_and_vpage & ~VBIT_MASK);
  }

  tlb_miss = 0;
}


void tlb_clear_all_R_bits() 
{
  int i;
  for(i = 0; i < num_tlb_entries; i++){
    tlb[i].mr_pframe = (tlb[i].mr_pframe & ~RBIT_MASK);
  }
}
void tlb_clear_entry(VPAGE_NUMBER vpage) {
  int i;
  for(i = 0; i < num_tlb_entries; i++){
    if((tlb[i].vbit_and_vpage & VPAGE_MASK) == vpage)
      tlb[i].vbit_and_vpage = (tlb[i].vbit_and_vpage & ~VBIT_MASK);
  }
}
PAGEFRAME_NUMBER tlb_lookup(VPAGE_NUMBER vpage, OPERATION op)
{
  int i;
  for(i = 0; i < num_tlb_entries; i++){
    if((tlb[i].vbit_and_vpage & VPAGE_MASK) == vpage){
      tlb[i].mr_pframe = (tlb[i].mr_pframe | RBIT_MASK);
      if(op == STORE)
	tlb[i].mr_pframe = (tlb[i].mr_pframe | MBIT_MASK);
      return (PAGEFRAME_NUMBER)(tlb[i].mr_pframe & PFRAME_MASK);
    }
  }
  tlb_miss = 1;
  return;
}

int clock_hand = 0;
void tlb_insert(VPAGE_NUMBER new_vpage, PAGEFRAME_NUMBER new_pframe,
		BOOL new_mbit, BOOL new_rbit)
{
  int i;
  for(i = 0; i <= num_tlb_entries; i++){
    if((((tlb[clock_hand].mr_pframe & RBIT_MASK) >> 31) == 0) &&
       (((tlb[clock_hand].mr_pframe & MBIT_MASK) >> 30) == 0)){
      tlb[clock_hand].vbit_and_vpage = (tlb[clock_hand].vbit_and_vpage & ~VBIT_MASK);
      break;
    }
    else{
      clock_hand++;
      clock_hand = (clock_hand & mod_tlb_entries_mask);
    }
  }
  if(tlb[clock_hand].vbit_and_vpage & VBIT_MASK){
    mmu_modify_rbit_bitmap(tlb[clock_hand].mr_pframe & PFRAME_MASK, (tlb[clock_hand].mr_pframe & RBIT_MASK) >> 31);
    mmu_modify_mbit_bitmap(tlb[clock_hand].mr_pframe & PFRAME_MASK, (tlb[clock_hand].mr_pframe & MBIT_MASK) >> 30);
  }
  tlb[clock_hand].vbit_and_vpage = (tlb[clock_hand].vbit_and_vpage | new_vpage);
  tlb[clock_hand].mr_pframe = (tlb[clock_hand].mr_pframe | new_pframe);
  if(new_mbit)
    tlb[clock_hand].mr_pframe = (tlb[clock_hand].mr_pframe | (1 << 30));
  if(new_rbit)
    tlb[clock_hand].mr_pframe = (tlb[clock_hand].mr_pframe | (1 << 31));

  clock_hand++;
  clock_hand = (clock_hand & mod_tlb_entries_mask);
}
void tlb_write_back()
{
  int i;
  for(i = 0; i < num_tlb_entries; i++){
    if(tlb[i].vbit_and_vpage & VBIT_MASK){
      mmu_modify_rbit_bitmap((tlb[i].mr_pframe & PFRAME_MASK), ((tlb[i].mr_pframe & RBIT_MASK) >> 31));
      mmu_modify_mbit_bitmap((tlb[i].mr_pframe & PFRAME_MASK), ((tlb[i].mr_pframe & MBIT_MASK) >> 30));
    }
  }
}
