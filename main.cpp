#include<iostream>
#include <list>
#include <ctime>

int INFO = 0;
int DEBUG = 1;
int LOGLEVEL = INFO;

template <typename T>
class Matrix;

template <typename T>
std::ostream& operator<<(std::ostream& ostr, const Matrix<T>& matrix)
{
    for(int r=0; r < matrix.get_num_rows(); r ++)
    {
        for(int c=0; c < matrix.get_num_cols(); c ++)
            ostr << ' ' << matrix.get(r, c);
        ostr << std::endl;
    }
    return ostr;
}


template <typename T>
class Matrix
{
    private:
        T* m_data;
        int m_num_rows;
        int m_num_cols;
        int m_coord_to_index(int row, int col) const {return col*m_num_cols+row;};
    public:
        Matrix(int num_rows=2, int num_cols=2); 
        int get_num_rows() const; 
        int get_num_cols() const;
        T get(int m, int n) const;
        void set(int r, int c, T value);
        T* get_vector(int c) {return &m_data[c*m_num_rows];};
        friend std::ostream& operator<< <> (std::ostream& ostr, const Matrix<T>& matrix);
};

template <typename T>
Matrix<T>::Matrix(int num_rows, int num_cols):
    m_data(new T[num_rows*num_cols]),
    m_num_rows(num_rows), 
    m_num_cols(num_cols){
    for(int r=0; r<m_num_rows; r++)
    {
        for(int c=0; c<m_num_cols; c++)
        {
            m_data[m_coord_to_index(r, c)] = rand() % 10;
        }
    }
}; 


template <typename T>
int Matrix<T>::get_num_rows() const
{
    return this->m_num_rows;
}

template <typename T>
int Matrix<T>::get_num_cols() const
{
    return this->m_num_cols;
}

template <typename T>
T Matrix<T>::get(int m, int n) const
{

    return m_data[m_coord_to_index(m, n)];
}

template <typename T>
void Matrix<T>::set(int r, int c, T value)
{
    m_data[m_coord_to_index(r, c)] = value;
}

std::ostream& operator<<(std::ostream& ostr, const std::list<int>& list)
{
    for (const auto &i : list) {
        ostr << ' ' << i;
    }
    return ostr;
}

template <typename T>
void print_array(T* list, int size)
{
    std::cout << list[0];
    for (int i=1; i<size; i++) {
        std::cout << " " << list[i];
    }
}




class Graph
{
    private:
        int m_num_nodes; 
        Matrix<bool> m_graph;
        Matrix<int> m_weights;
        void m_init_graph(int num_nodes, double density);
    public:
        Graph(int num_nodes=5, double density=0.1);
        Matrix<bool>* get_graph() {return &m_graph;};
        Matrix<int>* get_weights() {return &m_weights;};
        bool* get_neighbourhood(int node);
        int num_nodes() const {return m_num_nodes;};
        bool is_connected();
};


void Graph::m_init_graph(int num_nodes, double density)
{
    m_graph = Matrix<bool>(num_nodes, num_nodes);
    int num_edges = 0;
    bool is_edge;
    for(int r=0; r < num_nodes; r++)
    {
        for(int c=r+1; c < num_nodes; c++)
        {
            is_edge = (static_cast<double>(std::rand()) / RAND_MAX) < density;
            m_graph.set(r, c, is_edge);
            m_graph.set(c, r, is_edge);
            if (is_edge)
                num_edges++;
        }
        m_graph.set(r, r, false);
    }
    std::cout << "Num of edges: " << num_edges << std::endl;
    m_weights = Matrix<int>(3, num_edges);
    int edge_num = 0;
    for(int r=0; r < num_nodes; r++)
    {
        for(int c=r+1; c < num_nodes; c++)
        {
            if (m_graph.get(r, c))
            {
                m_weights.set(0, edge_num, r);
                m_weights.set(1, edge_num, c);
                m_weights.set(2, edge_num, (rand() % 2) + 1);
                edge_num++;
            }
                
        }
    }
    
}

Graph::Graph(int num_nodes, double density)
{
    m_num_nodes = num_nodes;
    m_init_graph(m_num_nodes, density);
}


bool* Graph::get_neighbourhood(int node)
{
    return m_graph.get_vector(node);
}

bool Graph::is_connected()
{
    std::list<int> open;
    std::list<int> closed;
    int node;
    bool* nh; // neighbourhood
    bool* in_open = new bool[m_num_nodes];
    bool* in_closed = new bool[m_num_nodes];
    for (int i=0; i<m_num_nodes; i++)
    {
        in_open[i] = false;
        in_closed[i] = false;
    }
    open.push_front(0);
    in_open[0] = true;
    int num_iter = 0;

    while(! open.empty())
    {
        node = open.front();
        open.pop_front();
        in_open[node] = false;
        if (LOGLEVEL >= DEBUG)
        {
            std::cout << "Iteration: " << num_iter << std::endl;
            std::cout << "Node: " << node << std::endl;
            std::cout << "Open set: " << open << std::endl;
            std::cout << "Closed set: " << closed << std::endl;
            std::cout << std::endl << "-----------------------" << std::endl;    
        }
        num_iter++;
        // Move front in open to closed
        closed.push_front(node);
        in_closed[node] = true;

        // Get neighbourhood
        nh = get_neighbourhood(node);
        for(int i=0; i<m_num_nodes; i++)
        {
            if(nh[i] && ! in_open[i] && ! in_closed[i])
            {
                open.push_front(i);
                in_open[i] = true;
            }
        }
    }
    if (LOGLEVEL >= DEBUG)
    {
        std::cout << "Iteration: " << num_iter << std::endl;
        std::cout << "Open set: " << open << std::endl;
        std::cout << "Closed set: " << closed << std::endl;
        std::cout << std::endl << "-----------------------" << std::endl;    
    }
    delete [] in_open;
    delete [] in_closed;
    return num_iter == m_num_nodes;
}

int main(void)
{
    std::srand(time(0));
    Graph g = Graph(5, 0.5);
    if (LOGLEVEL >= DEBUG)
    {
        std::cout << "Current matrix: " << std::endl;
        std::cout << *(g.get_graph());
        std::cout << "Current weights: " << std::endl;
        std::cout << *(g.get_weights());
        std::cout << std::endl << "-----------------------" << std::endl;  
    }

    bool con = g.is_connected();
    std::cout << std::endl << "Is connected: " << con << std::endl;
    return 0;
}


