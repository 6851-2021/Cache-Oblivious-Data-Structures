class matrix_walker
{
public: 
};

class naive_matrix_walker : public matrix_walker{
    private:
        int n, m;
        int *arr;
        int i, j;
        int value;
        int translate(int i, int j);
    public:
        naive_matrix_walker(int n, int m);
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
        int n, m;
        int *arr;
        int translate(int i, int j);
        int i, j;
        int value;

    public:
        co_matrix_walker(int n, int m);
        void teleport(int i, int j);
        void move_left();
        void move_right();
        void move_up();
        void move_down();
        int get();
        void set(int i, int j, int value);
};