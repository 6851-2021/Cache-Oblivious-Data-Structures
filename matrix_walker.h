class matrix_walker
{
public: 
};

class naive_matrix_walker : public matrix_walker{

    public:
        matrix_walker_naive(int n, int m);
        void teleport(int i, int j);
        void move_left();
        void move_right();
        void move_up();
        void move_down();
        int get();
        void set(int i, int j, int val);
};

class co_matrix_walker : public matrix_walker{

    public:
        co_matrix_walker(int n, int m);
        void teleport(int i, int j);
        void move_left();
        void move_right();
        void move_up();
        void move_down();
        int get();
        void set();
};