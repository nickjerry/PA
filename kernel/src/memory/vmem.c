#include "common.h"
#include "memory.h"
#include <string.h>

#define VMEM_ADDR 0xa0000
#define SCR_SIZE (320 * 200)

/* Use the function to get the start address of user page directory. */
inline PDE* get_updir();

void create_video_mapping() {
	/* TODO: create an identical mapping from virtual memory area 
	 * [0xa0000, 0xa0000 + SCR_SIZE) to physical memory area 
	 * [0xa0000, 0xa0000 + SCR_SIZE) for user program. You may define
	 * some page tables to create this mapping.
	 */
/*	panic("please implement me");*/
	PDE *pdir = get_updir();

	Log("pdir:0x%x\n", (uint32_t)pdir);
	PTE *ptable;

	/* get ptable */
	ptable = (PTE *)(pdir[0].page_frame << 12);

	Log("get here!\n");
	/* fill PTEs */
	uint32_t pframe_addr = VMEM_ADDR;

	for (; pframe_addr < VMEM_ADDR + SCR_SIZE; pframe_addr += PAGE_SIZE) {
		ptable->val = make_pte(pframe_addr);
		ptable ++;
	}
}

void video_mapping_write_test() {
	int i;
	uint32_t *buf = (void *)VMEM_ADDR;
	for(i = 0; i < SCR_SIZE / 4; i ++) {
		buf[i] = i;
	}
}

void video_mapping_read_test() {
	int i;
	uint32_t *buf = (void *)VMEM_ADDR;
	for(i = 0; i < SCR_SIZE / 4; i ++) {
		assert(buf[i] == i);
	}
}

void video_mapping_clear() {
	memset((void *)VMEM_ADDR, 0, SCR_SIZE);
}

