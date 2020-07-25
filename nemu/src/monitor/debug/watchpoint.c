#include "monitor/watchpoint.h"
#include "monitor/expr.h"

#define NR_WP 32

static WP wp_pool[NR_WP] = {};
static WP *head = NULL, *free_ = NULL;

void init_wp_pool() {
  int i;
  for (i = 0; i < NR_WP; i ++) {
    wp_pool[i].NO = i;
    wp_pool[i].next = &wp_pool[i + 1];
  }
  wp_pool[NR_WP - 1].next = NULL;

  head = NULL;
  free_ = wp_pool;
}

/* TODO: Implement the functionality of watchpoint */

/* PA1.6 
 * Date: 2020/7/25
 */

/* Head insert */
WP* new_wp(){
	if(free_ == NULL) {
		// or assert(0) ?
		printf("There is no more memory to set watchpoint. You candelete some watchpoints to free memory.\n");
		return NULL;
	}
	WP* p = free_;
	free_ = free_ -> next;
	p -> next = head;
	head = p;
	return head;
}

/* Head insert */
void free_wp(WP *wp){
	if(head == NULL){
		printf("There is no watchpoint to free.\n");
		return ;
	}
	if(wp == head){
		head = head -> next;
		wp -> next = free_;
		free_ = wp;	
		return ;
	}

	WP *p = head;
	while(p -> next != wp) p = p -> next;
	p -> next = wp -> next;
	wp -> next = free_;
	free_ = wp;
}

