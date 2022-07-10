#ifndef ATTEMPT_LINKED_LIST_H
#define ATTEMPT_LINKED_LIST_H

#include <stdbool.h>
struct s_Linked_list_{
    unsigned int ui_nodes_count;
    struct s_Linked_list_node_* sp_first_;
    struct s_Linked_list_node_* sp_last_;
};

struct s_Linked_list_node_{
    struct s_Linked_list_node_* sp_next_;
    struct s_Linked_list_node_* sp_prev_;
    void* vp_data;
};

bool fn_Instantiate_linked_list(struct s_Linked_list_*);
bool fn_Push_back_to_linked_list(struct s_Linked_list_*, void*);
bool fn_Push_front_to_linked_list(struct s_Linked_list_*, void*);

bool fn_Insert_into_linked_list(struct s_Linked_list_*, unsigned int, void*);

void* fn_Pop_back_from_linked_list(struct s_Linked_list_*);
void* fn_Pop_front_from_linked_list(struct s_Linked_list_*);


#endif
