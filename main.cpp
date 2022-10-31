#include<iostream>
#include <list>

template <typename T>
class Matrix
{
    private:
        T* m_data;
        int m_num_rows;
        int m_num_cols;
        int m_coord_to_index(int row, int col){return col*m_num_cols+row;}
    public:
        Matrix(int, int); 
        T max();
        int get_num_rows(){return m_num_rows;}
        int get_num_cols(){return m_num_cols;}
};

template <typename T>
Matrix<T>::Matrix(int num_rows=2, int num_cols=2):
    m_data(new T[num_cols*num_rows]),
    m_num_rows(num_rows),
    m_num_cols(num_cols)
{
    for(int r=0; r<m_num_rows; r++)
    {
        for(int c=0; c<m_num_cols; c++)
        {
            m_data[m_coord_to_index(r, c)] = rand() % 10;
        }
    }
}


template <typename T>
std::ostream& operator<<(std::ostream& ostr, const Matrix<T>& matrix)
{
    for(int r=0; r < matrix.get_num_cols(); r ++)
    {
        for(int c=0; r < matrix.m_num_cols; r ++)
            ostr << ' ' << matrix.m_data[matrix.m_coord_to_index(r, c)];
        ostr << std::endl;
    }
    return ostr;
}

std::ostream& operator<<(std::ostream& ostr, const std::list<int>& list)
{
    for (const auto &i : list) {
        ostr << ' ' << i;
    }
    return ostr;
}

int main(void)
{
    std::list<int> node_stack;
    node_stack.push_front(5);
    Matrix<int> m = Matrix<int>(3, 4);

    std::cout << "Current node stack: " << node_stack << std::endl;
    std::cout << "Current matrix: " << std::endl;
    std::cout << m;
    node_stack.~list();
    return 0;
}


