/**
 * @file: task/iface.h
 * Interface of a programming task 2
 */
#include "../Utils/utils_iface.h"
#include <unordered_set>

/* namespaces import */
using namespace Utils;

//Debug assert with diagnostic info
#if !defined(GRAPH_ASSERTXD)
#    define GRAPH_ASSERTXD(cond, what) ASSERT_XD(cond, "Graph", what)
#endif

// Simple debug assert
#if !defined(GRAPH_ASSERTD)
#    define GRAPH_ASSERTD(cond) ASSERT_XD(cond, "Graph", "")
#endif

/**
 * Namespace for the programming task
 */
namespace Task
{
    //
    //Iterator
    //
    template <class T> class Iterator
    {
        public:
            template <class NodeT, class EdgeT> friend class Graph;//! temp
            Iterator();//<Constructor private may be
            Iterator(Iterator *nxt, Iterator* prv,T *d);//<Constructor with parameters
            Iterator(const Iterator& itr);//<Copy constructor
            virtual ~Iterator();//<Destructor

            bool           operator ==(const Iterator& other);
            bool           operator !=(const Iterator& other);
            Iterator&      operator ++(); //prefix incremention
            Iterator       operator ++(int); //postfix incremention
            Iterator&      operator =(const Iterator& other);
            T&             operator *();

            Iterator*      get_next_iter() const;
            T*             get_data() const;

            class Error: public std::exception
            {
            };

        public: //!to be fixed
            Iterator<T> *next_iter;
            Iterator<T> *prev_iter;
            T *data;
    };
    //
    // Graph representation template
    // @param NodeT class representing nodes of graph, should be inherited from Graph::Node
    // @param EdgeT class representing edges of graph, should be inherited from Graph::Edge
    //
    template < class NodeT, class EdgeT> class Graph
    {
    public:
        typedef UInt32 UId; //< Unique id type for node and edge
        static const UId INVALID_UID = (UId) (-1);

        class Error: public std::exception
        {
        };
        //
        // Graph edge representation
        //
        class Edge
        {
        public:
            friend EdgeT& Graph<NodeT,EdgeT>::create_edge( NodeT& pred, NodeT& succ);
            friend void Graph<NodeT,EdgeT>::remove( EdgeT& edge);

            NodeT &pred(); // Get edge predecessor
            NodeT &succ(); // Get edge successor

            Graph& graph(); // Get the graph
            UId uid() const;// Get the edge's unique id
        protected:
            Edge( NodeT& p, NodeT& s); // Construct an edge between given nodes
            virtual ~Edge();
        private:
            // ---- Default  and copy constructors turned off ---
            Edge();
            Edge( const Edge &e);
            // ---- The internal implementation routines ----
            // ---- The data involved in the implementation ----
            Graph& parent_graph;
            void* graph_itr_loc;


            NodeT& pred_node;
            void *pred_itr_loc;

            NodeT& succ_node;
            void *succ_itr_loc;

            UId id;
        };

        //
        // Graph node representation
        //

        template <class T> friend class Iterator;

        class Node
        {
        public:
            friend NodeT& Graph<NodeT,EdgeT>::create_node();
            friend void Graph<NodeT,EdgeT>::remove( NodeT& node);

            typedef Iterator<EdgeT> succ_iterator ;// iterator for node's successor edges
            typedef Iterator<EdgeT> pred_iterator ;// iterator for node's predecessor edges

            pred_iterator preds_begin(); // Get iterator to the first predecessor edge
            pred_iterator preds_end();   // Get end iterator for the predecessors
            pred_iterator* add_pred_iter(EdgeT *p);// Creates a new iterator for new predecessor
            void remove_pred(void *p);

            succ_iterator succs_begin(); // Get iterator to the first successor edge
            succ_iterator succs_end();   // Get end iterator for the successors
            succ_iterator* add_succ_iter(EdgeT *s);// Creates a new iterator for new successor
            void remove_succ(void *s);

            Graph& graph();  // Get the graph reference
            UId uid() const; // Get the node's unique id

            EdgeT& first_pred(); // Convinience routine returns first predecessor edge or throws an exception
            EdgeT& first_succ(); // Convinience routine returns first successor edge or throws an exception

            UInt32 num_preds() const; // Get the number of predecessors
            UInt32 num_succs() const; // Get the number of successors

            //bool operator ==(const Node& other) const;

        protected:
            Node( Graph& g); // Constructor of the node
            virtual ~Node();
        private:
            // ---- Default  and copy constructors turned off ---
            Node();
            Node(const Node &n);

            // ---- The internal implementation routines ----

            // ---- The data involved in the implementation ----
            Graph& parent_graph;
            void *graph_itr_loc;

            pred_iterator* head_pred;
            pred_iterator* tail_pred;
            UInt32 preds_num;

            succ_iterator* head_succ;
            succ_iterator* tail_succ;
            UInt32 succs_num;

            UId id;
        };



    public:
    // ---- Graph interface ----
        typedef Iterator<NodeT> node_iterator;// Iterator for the graph's nodes
        typedef Iterator<EdgeT> edge_iterator; // Iterator for the graph's edges

        node_iterator nodes_begin(); // Get the iterator to the first node
        node_iterator nodes_end();   // Get the end iterator for the nodes

        edge_iterator edges_begin(); // Get the iterator to the first edge
        edge_iterator edges_end();   // Get the end iterator for the edges

        UInt32 num_nodes() const; // Get the number of nodes
        UInt32 num_edges() const; // Get the number of edges

        NodeT &create_node();                   // Create a new node and return reference to it
        EdgeT &create_edge( NodeT& pred, NodeT& succ); // Create a new edge between given nodes

        void remove( NodeT& node); // Remove and delete node
        void remove( EdgeT& edge); // Remove and delete edge

        virtual ~Graph(); // Destructor, deletes all nodes and edges
		Graph();
    private:
        // ---- The internal implementation ----
        // ---- The data involved in the implementation ----
        node_iterator* head_node;
        node_iterator* tail_node;
        UInt32 nodes_numbr;

        edge_iterator* head_edge;
        edge_iterator* tail_edge;
        UInt32 edges_numbr;
    };



    bool uTest( UnitTest *utest_p);
};

#include "graph_impl.h"
