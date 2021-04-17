class matrix_walker
{
public: 
};

class naive_matrix_walker : public matrix_walker{
    private:
        int n;
        int *arr;
        int i, j;
        int value;
        int translate(int i, int j);
    public:
        naive_matrix_walker(int n);
        void teleport(int i, int j);
        void move_left();
        void move_right();
        void move_up();
        void move_down();
        int get();
        void set(int i, int j, int value);
};

class co_matrix_walker : public matrix_walker{
    private:
        int n;
        int n_pw2;
        int *arr;
        int translate(int i, int j);
        int i, j;
        int value;
        int z_value;
        int even_bits;
        int odd_bits;

    public:
        co_matrix_walker(int n);
        void teleport(int i, int j);
        void move_left();
        void move_right();
        void move_up();
        void move_down();
        int get();
        void set(int i, int j, int value);
};