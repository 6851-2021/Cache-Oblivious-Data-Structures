#include "ordered-file-maintenance-in-c/OrderedFileMaintenance.h"
#include "static-search-trees.h"

class co_dynamic_serach_tree {
    private:
        int n;
        list_t list;
        CO_static_search_tree *tree;
    public:
        void add(int value);
        int get_successor(int value);
        co_dynamic_serach_tree();
        ~co_dynamic_serach_tree();
};