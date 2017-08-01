#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/sched.h>
#include<linux/syscalls.h>
#include<linux/mm.h>
#include<asm/pgtable.h>
#include "translation.h"


asmlinkage long sys_translationVAtoPA(unsigned long va){
	pgd_t *pgd;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *ptep,pte;
	
	struct page *page = NULL;
	struct mm_struct *mm = current->mm;

	
	pgd = pgd_offset(mm, va);
	if (pgd_none(*pgd) || pgd_bad(*pgd))
		goto out;
	printk(KERN_NOTICE "Valid pgd");

	pud = pud_offset(pgd, va);
	if (pud_none(*pud) || pud_bad(*pud))
		goto out;
	printk(KERN_NOTICE "Valid pud");

	pmd = pmd_offset(pud, va);
	if (pmd_none(*pmd) || pmd_bad(*pmd))
		goto out;
	printk(KERN_NOTICE "Valid pmd");

	ptep = pte_offset_map(pmd, va);
	if (!ptep)
		goto out;
	pte = *ptep;

	page = pte_page(pte);
	if (page)
	printk("va 0x%lx -> pa 0x%lx\n",
	va, page_to_phys(page));
	pte_unmap(ptep);
out:
	return page;

}







