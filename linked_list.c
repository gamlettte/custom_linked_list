#ifndef ATTEMPT_LINKED_LIST_C
#define ATTEMPT_LINKED_LIST_C

#include <stdlib.h>
#include <stdbool.h>
#include "linked_list.h"

bool fn_Instantiate_linked_list (struct s_Linked_list_* asp_to_return)
/*
 * param:  struct s_Linked_list_* asp_to_return  - list to fill fields
 * return: bool - if instance set properly
 * */
{
    asp_to_return = (struct s_Linked_list_ *)calloc(1, sizeof(struct s_Linked_list_));
    if(asp_to_return == NULL){
        return false;
    }
    asp_to_return->sp_first_ = NULL;
    asp_to_return->sp_last_ = NULL;
    asp_to_return->ui_nodes_count = 0;
    return true;
        
}

bool fn_Push_first_element (struct s_Linked_list_* asp_list, void* avp_data)
/*
 * param:  struct s_Linked_list_* asp_list - empty linked list 
 * param:  void* avp_data - pointer to inserted data
 * return: bool - if an element added properly
 *
 * hidden function to add first element into list*/
{
    struct s_Linked_list_node_*  sp_to_add = (struct s_Linked_list_node_*)calloc(1, sizeof(struct s_Linked_list_node_));
    if(sp_to_add == NULL){
        return false;
    }
    sp_to_add->vp_data = avp_data;
    sp_to_add->sp_next_ = NULL;
    sp_to_add->sp_prev_ = NULL;
    asp_list->sp_first_ = sp_to_add;
    asp_list->sp_last_ = sp_to_add;
    asp_list->ui_nodes_count = 1;
    return true;
}

bool fn_Push_back_to_linked_list (struct s_Linked_list_* asp_list, void* avp_data)
/*
 * param:  struct s_Linked_list_* asp_list - linked list to push a new element
 * param:  void* avp_data - pointer to inserted data 
 * return: bool - if an element added properly 
 * */
{
    struct s_Linked_list_node_*  sp_to_add = (struct s_Linked_list_node_*)calloc(1, sizeof(struct s_Linked_list_node_));
    if(sp_to_add == NULL){
        return false;
    }
    if(asp_list->sp_first_ == NULL && asp_list->sp_last_ == NULL){
        return fn_Push_first_element(asp_list, avp_data);
    }

    sp_to_add->vp_data = avp_data;
    sp_to_add->sp_next_ = NULL;
    sp_to_add->sp_prev_ = asp_list->sp_last_;
    asp_list->sp_last_->sp_next_ = sp_to_add;
    asp_list->sp_last_ = sp_to_add;
    ++asp_list->ui_nodes_count;
    return true;
}

bool fn_Push_front_to_linked_list(struct s_Linked_list_* asp_list, void* avp_data)
/*
 * param:  struct s_Linked_list_* asp_list - linked list to push a new element
 * param:  void* avp_data - pointer to inserted data 
 * return: bool - if an element added properly 
 * */
{
    struct s_Linked_list_node_*  sp_to_add = (struct s_Linked_list_node_*)calloc(1, sizeof(struct s_Linked_list_node_));
    if(sp_to_add == NULL){
        return false;
    }
    if(asp_list->sp_first_ == NULL && asp_list->sp_last_ == NULL){
        return fn_Push_first_element(asp_list, avp_data);
    }
    sp_to_add->vp_data = avp_data;
    sp_to_add->sp_prev_ = NULL;
    sp_to_add->sp_next_= asp_list->sp_first_;
    asp_list->sp_first_->sp_prev_ = sp_to_add;
    asp_list->sp_first_ = sp_to_add;
    ++asp_list->ui_nodes_count;
    return true;
}

void* fn_Pop_last_element(struct s_Linked_list_* asp_list)
/*
 * param:  struct s_Linked_list_* asp_list - linked list to pop the last element
 * return: void* - pointer to released data
 * 
 * hidden function to pop last element from list
 * */
{
    void* vp_temp = asp_list->sp_first_->vp_data;
    free(asp_list->sp_first_);
    asp_list->sp_first_ = NULL;
    asp_list->sp_last_ = NULL;
    asp_list->ui_nodes_count = 0;
    return vp_temp;
}

void* fn_Pop_back_from_linked_list(struct s_Linked_list_* asp_list)
/*
 * param:  struct s_Linked_list_* asp_list - linked list to pop an element
 * return: void* - pointer to released data
 * */
{
    if(asp_list->sp_last_ == NULL){
        return NULL;
    }else{
        void* vp_temp = asp_list->sp_last_->vp_data;
        if(asp_list->sp_first_ == asp_list->sp_last_){
            return fn_Pop_last_element(asp_list);
        }
        asp_list->sp_last_ = asp_list->sp_last_->sp_prev_;
        free(asp_list->sp_last_->sp_next_);
        asp_list->sp_last_->sp_next_= NULL;
        --asp_list->ui_nodes_count;
        return vp_temp;
    }
}

void* fn_Pop_front_from_linked_list( struct s_Linked_list_* asp_list )
/*
 * param:  struct s_Linked_list_* asp_list - linked list to pop an element
 * return: void* - pointer to released data
 * */
{
    if(asp_list->sp_last_ == NULL){
        return NULL;
    }else{
        void* vp_temp = asp_list->sp_first_->vp_data;
        if(asp_list->sp_first_ == asp_list->sp_last_){
            return fn_Pop_last_element(asp_list);
        }
        asp_list->sp_first_ = asp_list->sp_first_->sp_next_;
        free(asp_list->sp_first_->sp_prev_);
        asp_list->sp_first_->sp_prev_ = NULL;
        --asp_list->ui_nodes_count;
        return vp_temp;
    }
}

bool fn_Insert_into_linked_list(struct s_Linked_list_* asp_list , unsigned int aui_index , void* avp_data)
/*
 * param:  struct s_Linked_list_* asp_list - linked list to insert a new element
 * param:  unsigned int aui_index - expected index of a new element
 * param:  void* avp_data - pointer to inserted data 
 * return: bool - if an element added properly 
 * */
{
    if(asp_list == NULL || avp_data == NULL || aui_index > asp_list->ui_nodes_count){
        return false;
    }
    if(aui_index == 0){
        return fn_Push_front_to_linked_list(asp_list, avp_data);
    }
    if(aui_index == asp_list->ui_nodes_count){
        return fn_Push_back_to_linked_list(asp_list, avp_data);
    }
    struct s_Linked_list_node_* sp_to_add = (struct s_Linked_list_node_*)calloc(1, sizeof(struct s_Linked_list_node_));
    if(sp_to_add == NULL){
        return false;
    }else{
        sp_to_add->vp_data = avp_data;
        unsigned int ui_temp_index;
        struct s_Linked_list_node_* sp_temp_pointer;
        if(asp_list->ui_nodes_count / 2.0 <= aui_index){
            ui_temp_index = 0;
            sp_temp_pointer = asp_list->sp_first_;
            while(ui_temp_index != aui_index){
                sp_temp_pointer = sp_temp_pointer->sp_next_;
                ++ui_temp_index;
            }
        }else{
            ui_temp_index = asp_list->ui_nodes_count - 1;
            sp_temp_pointer = asp_list->sp_last_;
            while(ui_temp_index != aui_index){
                sp_temp_pointer = sp_temp_pointer->sp_prev_;
            }
        }
        sp_to_add->sp_prev_ = sp_temp_pointer->sp_prev_;
        sp_to_add->sp_next_ = sp_temp_pointer;
        sp_to_add->sp_prev_->sp_next_ = sp_to_add;
        sp_to_add->sp_next_->sp_prev_ = sp_to_add;
        ++asp_list->ui_nodes_count;
        return true;
    }
}

void fn_Clear_linked_list(struct s_Linked_list_* asp_list, void(*afnp_clear_element)(void*))
/*
 * param:  struct s_Linked_list_* asp_list - linked list to clear
 * param:  void(*afnp_clear_element)(void*)) - function pointer to element data clearer. Is not used if == NULL
 * return: void*/
{
    if(afnp_clear_element != NULL){
        while(asp_list->sp_first_ != NULL){
            afnp_clear_element(fn_Pop_back_from_linked_list(asp_list));
        }
    }else{
        while(asp_list->sp_first_ != NULL){
            fn_Pop_back_from_linked_list(asp_list);
        }
    }
    return;
}

#endif

