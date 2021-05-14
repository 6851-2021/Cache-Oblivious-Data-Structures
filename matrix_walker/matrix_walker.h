class matrix_walker
{
public: 
};

/**
 * @brief an NxN 2D array with a pointer that can be moved up/down/left/right/teleported.
 *        Allows reading the value at the pointer.
 *        Allows updating the value at an arbitrary position.
 * 
 *        Internal structure is an array that uses row-major order (not cache-oblivious).
 */
class naive_matrix_walker : public matrix_walker{
    private:
        int N;
        int *arr;
        int i, j;
        int value;

        /**
         * @brief Translates a coordinate (i, j) into a memory offset in arr.
         * 
         * Uses row major-order.
         * 
         * @param i  the row value
         * @param j  the column value
         * @return int   the memory offset in arr
         */
        int translate(int i, int j);
    public:
        /**
         * @brief Construct a new Naive Matrix Walker object
         * 
         * Constructs a naive matrix walker of size NxN.
         * The matrix is intitialized with zeros.
         * The pointer starts at the top-left corder (0, 0).
         * The bottom-right corder is at (N - 1, N - 1).
         * 
         * @param N  the edge size of the matrix
         */
        naive_matrix_walker(int N);

        /**
         * @brief teleport to the pointer to a new location (i, j)
         * 
         * @param i  the row value of the new coordinate (0 <= i < N)
         * @param j  the column value of the new coordinate (0 <= j < N)
         */
        void teleport(int i, int j);

        /**
         * @brief Move the pointer one step to the left.
         * If moving will leave the boundry, the pointer doesn't move.
         */
        void move_left();

        /**
         * @brief Move the pointer one step to the right.
         * If moving will leave the boundry, the pointer doesn't move.
         */
        void move_right();

        /**
         * @brief Move the pointer one step up.
         * If moving will leave the boundry, the pointer doesn't move.
         */
        void move_up();

        /**
         * @brief Move the pointer one step down.
         * If moving will leave the boundry, the pointer doesn't move.
         */
        void move_down();

        /**
         * @brief Get the value that the pointer points to in the matrix.
         * 
         * @return int   the value that the pointer points to.
         */
        int get();

        /**
         * @brief Set the value at the given coordinate (i, j) to value.
         * 
         * @param i  the row number of the coordinate (0 <= i < N)
         * @param j  the column number of the coordinate (0 <= j < N)
         * @param value  the value to set
         */
        void set(int i, int j, int value);
};

/**
 * @brief an NxN Cache Oblivious 2D array with a pointer that can be moved up/down/left/right/teleported.
 *        Allows reading the value at the pointer.
 *        Allows updating the value at an arbitrary position.
 * 
 *        Internal structure is an array built by recusrively doing
 *        divide and conqure on the rows and columns. Then, storing 
 *        each of the 4 sub-matrices recursively as one block in memory.
 *        The sub-matrices are stored using Z-order.
 * 
 *        We pad the array to make its dimensions a power of 2.
 *        This way we can use binary-interleaving to calculate
 *        the Z-order based on coordinates in O(1).
 */
class co_matrix_walker : public matrix_walker{
    private:
        int N;
        int N_pw2;
        int *arr;
        int i, j;
        int value;
        int z_value;
        int even_bits;
        int odd_bits;
        
        /**
         * @brief Translates a coordinate (i, j) into a memory offset in arr.
         * 
         * Uses Z-order.
         * 
         * @param i  the row value
         * @param j  the column value
         * @return int   the memory offset in arr
         */
        int translate(int i, int j);
    public:
        /**
         * @brief Construct a new Cache Oblivious Matrix Walker object
         * 
         * Constructs a cache oblivious matrix walker of size NxN.
         * The matrix is intitialized with zeros.
         * The pointer starts at the top-left corder (0, 0).
         * The bottom-right corder is at (N - 1, N - 1).
         * 
         * @param N  the edge size of the matrix
         */
        co_matrix_walker(int N);

        /**
         * @brief teleport to the pointer to a new location (i, j)
         * 
         * @param i  the row value of the new coordinate (0 <= i < N)
         * @param j  the column value of the new coordinate (0 <= j < N)
         */
        void teleport(int i, int j);

        /**
         * @brief Move the pointer one step to the left.
         * If moving will leave the boundry, the pointer doesn't move.
         */
        void move_left();

        /**
         * @brief Move the pointer one step to the right.
         * If moving will leave the boundry, the pointer doesn't move.
         */
        void move_right();

        /**
         * @brief Move the pointer one step up.
         * If moving will leave the boundry, the pointer doesn't move.
         */
        void move_up();

        /**
         * @brief Move the pointer one step down.
         * If moving will leave the boundry, the pointer doesn't move.
         */
        void move_down();

        /**
         * @brief Get the value that the pointer points to in the matrix.
         * 
         * @return int   the value that the pointer points to.
         */
        int get();

        /**
         * @brief Set the value at the given coordinate (i, j) to value.
         * 
         * @param i  the row number of the coordinate (0 <= i < N)
         * @param j  the column number of the coordinate (0 <= j < N)
         * @param value  the value to set
         */
        void set(int i, int j, int value);
};