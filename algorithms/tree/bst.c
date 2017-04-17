/*************************************************************************
    > File Name: bst.c
    > Author: wangtian
    > Mail: 317302030@qq.com 
    > Created Time: Mon 17 Apr 2017 05:03:53 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

typedef struct bst_node_t{
	int key;
	struct bst_node_t *l_child, *r_child;
}bst,*p_bst;

int bst_insert(p_bst p_head, p_bst p_node, int data){
	p_bst p_tmp = p_head;
	while(p_tmp != NULL){
		if(data < p_tmp->key){
			p_tmp = p_tmp->l_child;
		}
		else {
			p_tmp = p_tmp->r_child;
		}
	}
	p_bst p_node = (p_bst)malloc(sizof(bst));
	p_node = p_tmp;
	p_node->key = data;
}

int inoder_bst(p_bst p_head){

}

bst bst_init(int *arr, int len){
	int i, j;
	p_bst p_tmp;
	p_bst p_head = (p_bst)malloc(sizof(bst));
	p_tmp = p_head;
	if(len > 0){
		p_head->key = arr[0];
	}
	for(i = 0; i < len; i++){

	}

}

int main(){

}
