#include<vector>

class indirection_group {
    private:
        int capacity;
        int max_value;
        std::vector<int> vec;

    public:
        /**
         * @brief Construct a new indirection group object
         * 
         *        Constructs an indirection group of a given capacity
         *        must manually manage once the capacity has exceeded.
         * 
         * @param capacity  the capacity of the group
         */
        indirection_group(int capacity);

        /**
         * @brief insert a new value into the group
         * 
         * Throws an exception if adding this element
         * will cause the group to exceed double
         * the allocated capacity.
         * 
         * @param value  the value to add
         * @return true  if inserting led to exceeding the capacity
         * @return false otherwise
         */
        bool insert(int value);

        /**
         * @brief Split the given indirection group
         * into two groups of equal size.
         * Keep the smallest numbers in this group, 
         * put the largest numbers in the returned group.
         * 
         * The resulting group will have a capacity equal 
         * to the this group's capacity
         * 
         * @return indirection_group* a pointer to the resulting group from split
         */
        indirection_group *split();

        /**
         * @brief Check if we can merge the group that into this group
         *        without needing to split.
         * 
         * @param that  the group to merge
         * @return true  if the two can be merge into this without spliting
         * @return false  otherwise
         */
        bool can_merge(indirection_group *that);

        
        /**
         /**
         * @brief Merge the two groups into this group, and then possibly split
         *        if merging exceeds the capacity.
         * 
         * all elements that go into this must be smaller than 
         * all the elements which goes into that
         * 
         * The two groups sizes must be less or equal to the capacity.
         * The two groups must be of equal capacity
         * 
         * @param that  the indirection group to merge  
         * @return true  if the merge happened with a split
         * @return false  otherwise
         */
        bool merge_and_split(indirection_group *that);

        /**
         * @brief Get the maximum value in the group
         * 
         * @return int  the max value
         */
        int get_max();

        /**
         * @brief Get the successor element in this group lower bounding value.
         *
         * @param value  value to lower bound
         *
         * @return successor of value or -1 if value > max_value
         */
        int lower_bound(int value);

        /**
         * @brief check if the current size of the group exceeds the capacity.
         * 
         * @return true  if the size exceeds the capacity
         * @return false  otherwise
         */
        bool overloaded();

        /**
         * @brief Checks if the group is empty
         * 
         * @return true  if the group is empty
         * @return false  otherwise
         */
        bool empty();

        /**
         * @brief swap that indirection_group into this.
         *
         * @return that  indirection_group to copy into this
         */
        void swap(indirection_group *that);

        /**
         * @brief clear this indirection group.
         *
         */
        void clear();

        /**
         * @brief reset the capacity of this group to new_cap.
         *
         * @param new_cap  new capacity of this group
         */
        void reset_capacity(int new_cap);

        /**
         * @brief calculates the size of the group
         * 
         * @return int  the size of the group
         */
        int size();
};