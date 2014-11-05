/**
 * @file: task/graph_impl.h
 * Solution implementation of the programming task 2
 */

namespace Task
{
// ----iterator class implemention ----
    template <class T>
    Iterator<T>::Iterator():
        next_iter(NULL) , prev_iter(NULL), data(NULL) {}

    template <class T>
    Iterator<T>::Iterator(Iterator *nxt, Iterator* prv,T *d):
        next_iter(nxt) , prev_iter(prv), data(d) {}

    template <class T>
    Iterator<T>::Iterator(const Iterator& itr):
        next_iter(itr.next_iter) , prev_iter(itr.prev_iter), data(itr.data) {}

    template <class T>
    Iterator<T>::~Iterator()
    {
        next_iter = NULL;
        prev_iter = NULL;
        data      = NULL;
    }

    template <class T> bool
    Iterator<T>::operator ==(const Iterator& other)
    {
        if( next_iter == other.next_iter &&
            prev_iter == other.prev_iter &&
            data      == other.data)
            return true;
        else
            return false;
    }

    template <class T> bool
    Iterator<T>::operator !=(const Iterator& other)
    {
        if( next_iter != other.next_iter ||
            prev_iter != other.prev_iter ||
            data      != other.data)
            return true;
        else
            return false;
    }

    template <class T> Iterator<T>&
    Iterator<T>::operator ++()
    {
        if(next_iter==NULL)
            throw Error();

        data      = next_iter->data;
        prev_iter = next_iter->prev_iter;
        next_iter = next_iter->next_iter;

        return *this;
    }

    template <class T> Iterator<T>
    Iterator<T>::operator ++(int)
    {
        if(next_iter==NULL)
            throw Error();

        Iterator tmp(next_iter, prev_iter, data);

        data      = next_iter->data;
        prev_iter = next_iter->prev_iter;
        next_iter = next_iter->next_iter;

        return tmp;
    }

    template <class T> Iterator<T>&
    Iterator<T>::operator =(const Iterator& other)
    {
        data      = other.data;
        prev_iter = other.prev_iter;
        next_iter = other.next_iter;

        return *this;
    }

    template <class T> T&
    Iterator<T>::operator *()
    {
        return *(data);
    }

    template <class T> Iterator<T>*
    Iterator<T>::get_next_iter() const
    {
        return next_iter;
    }

    template <class T> T*
    Iterator<T>::get_data() const
    {
        return data;
    }
//
//! ---Graph class implementation ----
//
    //
    //! --- Node class ---- implemention
    //
        template <class NodeT,class EdgeT> typename Graph<NodeT,EdgeT>::Node::pred_iterator
        Graph<NodeT,EdgeT>::Node::preds_begin()
        {
            //!throw here
            return *head_pred;
        }

        template <class NodeT,class EdgeT> typename Graph<NodeT,EdgeT>::Node::pred_iterator
        Graph<NodeT,EdgeT>::Node::preds_end()
        {
            //!throw here
            return *tail_pred;
        }

        template <class NodeT,class EdgeT> typename Graph<NodeT,EdgeT>::Node::pred_iterator*
        Graph<NodeT,EdgeT>::Node::add_pred_iter(EdgeT* p)
        {
            //!throw here p!=NULL *graph must be the same

            pred_iterator *New_pred_itr;

            try {
                pred_iterator *New_pred_itr = new pred_iterator;
                New_pred_itr->data = p;
            } catch (std::bad_alloc& ba)
            {
            std::cerr << "bad_alloc caught: " << ba.what() << endl;
            }

            if( preds_num == 0 )
            {
                head_pred = New_pred_itr;
                tail_pred = New_pred_itr;
                preds_num++;
                return New_pred_itr;
            }

            New_pred_itr->next_iter = head_pred;
            head_pred   ->prev_iter =
            head_pred               = New_pred_itr;
            preds_num++;
            return New_pred_itr;
        }

        template <class NodeT,class EdgeT> void
        Graph<NodeT,EdgeT>::Node::remove_pred(void *p)
        {
            pred_iterator* to_delete = (pred_iterator*) p;
            if(preds_num == 0)
            {
                //!throw
            }
            if(to_delete->next_iter == NULL &&
               to_delete->prev_iter == NULL &&
               to_delete            == head_pred &&
               to_delete            == tail_pred &&
               preds_num            == 1)
            {
                delete to_delete;
                head_pred = NULL;
                tail_pred = NULL;
                preds_num = 0;
                return ;
            }
            if(to_delete->prev_iter == NULL &&
               to_delete            == head_pred &&
               preds_num            != 0)
            {
                head_pred            = to_delete->next_iter;
                head_pred->prev_iter = NULL;
                preds_num--;
                delete to_delete;
                return;
            }
            if(to_delete->next_iter == NULL &&
               to_delete            == tail_pred &&
               preds_num            != 0)
            {
                tail_pred = to_delete->prev_iter;
                tail_pred->next_iter = NULL;
                preds_num--;
                delete to_delete;
                return;
            }
            if(to_delete->next_iter != NULL &&
               to_delete->prev_iter != NULL &&
               preds_num            != 0)
            {
                (to_delete->prev_iter)->next_iter = to_delete->next_iter;
                (to_delete->next_iter)->prev_iter = to_delete->prev_iter;
                preds_num--;
                delete to_delete;
                return;
            }

            //!throw

        }

        template <class NodeT,class EdgeT> typename Graph<NodeT,EdgeT>::Node::succ_iterator
        Graph<NodeT,EdgeT>::Node::succs_begin()
        {
            //!throw here
            return *head_succ;
        }

        template <class NodeT,class EdgeT> typename Graph<NodeT,EdgeT>::Node::succ_iterator
        Graph<NodeT,EdgeT>::Node::succs_end()
        {
            //!throw here
            return *tail_succ;
        }

        template <class NodeT,class EdgeT> typename Graph<NodeT,EdgeT>::Node::succ_iterator*
        Graph<NodeT,EdgeT>::Node::add_succ_iter(EdgeT* s)
        {
            //!throw here p!=NULL *graph must be the same
            succ_iterator *New_succ_itr;
            try {
                New_succ_itr = new succ_iterator;
                New_succ_itr->data = s;
            } catch (std::bad_alloc& ba)
            {
            std::cerr << "bad_alloc caught: " << ba.what() << endl;
            }

            if( succs_num == 0 )
            {
                head_succ = New_succ_itr;
                tail_succ = New_succ_itr;
                succs_num++;
                return New_succ_itr;
            }

            New_succ_itr->next_iter = head_succ;
            head_succ   ->prev_iter = New_succ_itr;
            head_succ               = New_succ_itr;
            succs_num++;
            return New_succ_itr;
        }

        template <class NodeT,class EdgeT> void
        Graph<NodeT,EdgeT>::Node::remove_succ(void *s)
        {
            succ_iterator* to_delete = (succ_iterator*) s;
            if(succs_num == 0)
            {
                //!throw
            }
            if(to_delete->next_iter == NULL &&
               to_delete->prev_iter == NULL &&
               to_delete            == head_succ &&
               to_delete            == tail_succ &&
               succs_num            == 1)
            {
                delete to_delete;
                head_succ = NULL;
                tail_succ = NULL;
                succs_num = 0;
                return ;
            }
            if(to_delete->prev_iter == NULL &&
               to_delete            == head_succ &&
               succs_num            != 0)
            {
                head_succ            = to_delete->next_iter;
                head_succ->prev_iter = NULL;
                succs_num--;
                delete to_delete;
                return;
            }
            if(to_delete->next_iter == NULL &&
               to_delete            == tail_succ &&
               succs_num            != 0)
            {
                tail_succ = to_delete->prev_iter;
                tail_succ->next_iter = NULL;
                succs_num--;
                delete to_delete;
                return;
            }
            if(to_delete->next_iter != NULL &&
               to_delete->prev_iter != NULL &&
               succs_num            != 0)
            {
                (to_delete->prev_iter)->next_iter = to_delete->next_iter;
                (to_delete->next_iter)->prev_iter = to_delete->prev_iter;
                succs_num--;
                delete to_delete;
                return;
            }

            //!throw

        }

        template <class NodeT,class EdgeT> Graph<NodeT,EdgeT>&
        Graph<NodeT,EdgeT>::Node::graph()
        {
            return parent_graph;
        }

        template <class NodeT,class EdgeT> typename Graph<NodeT,EdgeT>::UId
        Graph<NodeT,EdgeT>::Node::uid() const
        {
            return id;
        }

        template <class NodeT,class EdgeT> EdgeT&
        Graph<NodeT,EdgeT>::Node::first_pred()
        {
            //!another throw may be and getdata must return !NULL
            if(preds_num == 0)
                throw Error();

            return *( head_pred->data );
        }

        template <class NodeT,class EdgeT> EdgeT&
        Graph<NodeT,EdgeT>::Node::first_succ()
        {
            //!another throw may be and getdata must return !NULL
            if(succs_num == 0)
                throw Error();

            return *( head_succ->data );
        }

        template <class NodeT,class EdgeT> UInt32
        Graph<NodeT,EdgeT>::Node::num_preds() const
        {
            return preds_num;
        }

        template <class NodeT,class EdgeT> UInt32
        Graph<NodeT,EdgeT>::Node::num_succs() const
        {
            return succs_num;
        }

        template <class NodeT,class EdgeT>
        Graph<NodeT,EdgeT>::Node::Node(Graph& g) :

            parent_graph(g) , id((g.num_nodes())+1),
            preds_num(0), head_pred(NULL), tail_pred(NULL),
            succs_num(0), head_succ(NULL), tail_succ(NULL)
        {}

        template <class NodeT,class EdgeT>//! ????????????????
        Graph<NodeT,EdgeT>::Node::~Node()
        {
            /*for( ; head_)

            delete &succs_first;
            delete &succs_last;
            succs_num = 0;*/

            //UID!!!
        }

        template <class NodeT,class EdgeT> //useless?
        Graph<NodeT,EdgeT>::Node::Node() {}

        template <class NodeT,class EdgeT> //need implemention?
        Graph<NodeT,EdgeT>::Node::Node(const Node &n) {}


    //
    // ---- Edge class ---- implemention
    //
        template <class NodeT,class EdgeT> NodeT&
        Graph<NodeT,EdgeT>::Edge::pred()
        {
            return pred_node;
        }

        template <class NodeT,class EdgeT> NodeT&
        Graph<NodeT,EdgeT>::Edge::succ()
        {
            return succ_node;
        }

        template <class NodeT,class EdgeT> Graph<NodeT,EdgeT>&
        Graph<NodeT,EdgeT>::Edge::graph()
        {
            return parent_graph;
        }

        template <class NodeT,class EdgeT> typename Graph<NodeT,EdgeT>::UId
        Graph<NodeT,EdgeT>::Edge::uid() const
        {
            return id;
        }

        template <class NodeT,class EdgeT>
        Graph<NodeT,EdgeT>::Edge::Edge( NodeT& p, NodeT& s ):
            pred_node(p), succ_node(s), parent_graph(p.graph()), id( parent_graph.num_edges()+1)//!check for belonging to one graph
        {}

        template <class NodeT,class EdgeT>
        Graph<NodeT,EdgeT>::Edge::~Edge()
        {
        //some implemention with node and graph
        }

        template <class NodeT,class EdgeT>
        Graph<NodeT,EdgeT>::Edge::Edge() {} //useless?

        template <class NodeT,class EdgeT>
        Graph<NodeT,EdgeT>::Edge::Edge( const Edge& e):
            parent_graph(e.graph()), pred_node(e.pred()), succ_node(e.succ()), id(e.uid())
        {}
    //
    //
    //

    template <class NodeT,class EdgeT> typename Graph<NodeT,EdgeT>::node_iterator
    Graph<NodeT,EdgeT>::nodes_begin()
    {
        //!throw here
        return *head_node;
    }

    template <class NodeT,class EdgeT> typename Graph<NodeT,EdgeT>::node_iterator
    Graph<NodeT,EdgeT>::nodes_end()
    {
        //!throw here
        return *tail_node;
    }

    template <class NodeT,class EdgeT> typename Graph<NodeT,EdgeT>::edge_iterator
    Graph<NodeT,EdgeT>::edges_begin()
    {
        //!throw here
        return *head_edge;
    }

    template <class NodeT,class EdgeT> typename Graph<NodeT,EdgeT>::edge_iterator
    Graph<NodeT,EdgeT>::edges_end()
    {
        //!throw here
        return *tail_edge;
    }

    template <class NodeT,class EdgeT> UInt32
    Graph<NodeT,EdgeT>::num_nodes() const
    {
        return nodes_numbr;
    }

    template <class NodeT,class EdgeT> UInt32
    Graph<NodeT,EdgeT>::num_edges() const
    {
        return edges_numbr;
    }

    template <class NodeT, class EdgeT> NodeT&
    Graph<NodeT, EdgeT>::create_node()
    {
        NodeT *New_Node;
        node_iterator *New_iter;
        try {
                New_Node = new NodeT(*this);
            } catch (std::bad_alloc& ba)
            {
            std::cerr << "bad_alloc caught: " << ba.what() << endl;
            }

        try {
                New_iter = new node_iterator;
                New_iter->data = New_Node;
            } catch (std::bad_alloc& ba)
            {
            std::cerr << "bad_alloc caught: " << ba.what() << endl;
            }

        if( nodes_numbr == 0 )
        {
            head_node  = New_iter;
            tail_node  = New_iter;
            New_Node->graph_itr_loc = (void*) New_iter;
            nodes_numbr++;
            return *New_Node;
        }

        New_iter ->next_iter = head_node;
        head_node->prev_iter = New_iter;
        head_node            = New_iter;
        New_Node->graph_itr_loc = (void*) New_iter;
        nodes_numbr++;

        return *New_Node;
    }

    template <class NodeT, class EdgeT> EdgeT&
    Graph<NodeT, EdgeT>::create_edge( NodeT& pred, NodeT& succ)
    {
        EdgeT *New_Edge;
        edge_iterator *New_iter;
        try {
                New_Edge = new EdgeT(pred, succ);
            } catch (std::bad_alloc& ba)
            {
            std::cerr << "bad_alloc caught: " << ba.what() << endl;
            }

        try {
                New_iter = new edge_iterator;
                New_iter->data = New_Edge;
            } catch (std::bad_alloc& ba)
            {
            std::cerr << "bad_alloc caught: " << ba.what() << endl;
            }

        if( edges_numbr == 0 )
        {
            head_edge   = New_iter;
            tail_edge   = New_iter;
            edges_numbr++;
            New_Edge->pred_itr_loc  = (void*) pred.add_pred_iter(New_Edge);
            New_Edge->succ_itr_loc  = (void*) succ.add_succ_iter(New_Edge);
            New_Edge->graph_itr_loc = (void*) New_iter;
            return *New_Edge;
        }

        New_iter ->next_iter = head_edge;
        head_edge->prev_iter = New_iter;
        head_edge            = New_iter;
        nodes_numbr++;
        New_Edge->pred_itr_loc  = (void*) pred.add_pred_iter(New_Edge);
        New_Edge->succ_itr_loc  = (void*) succ.add_succ_iter(New_Edge);
        return *New_Edge;
    }


    template <class NodeT, class EdgeT> void
    Graph<NodeT, EdgeT>::remove(EdgeT& edge)
    {
        edge_iterator* to_delete = (edge_iterator*) edge.graph_itr_loc;
        if(edges_numbr == 0)
        {
            //!throw
        }
        if( to_delete->next_iter == NULL &&
            to_delete->prev_iter == NULL &&
            to_delete            == head_edge &&
            to_delete            == tail_edge &&
            edges_numbr          == 1)
        {

            head_edge   = NULL;
            tail_edge   = NULL;
            edges_numbr = 0;
            (edge.pred_node).remove_pred(edge.pred_itr_loc);
            (edge.succ_node).remove_succ(edge.succ_itr_loc);
            delete to_delete->data;
            delete to_delete;
            return ;
        }
        if( to_delete->prev_iter == NULL &&
            to_delete            == head_edge &&
            edges_numbr          != 0)
        {
            head_edge            = to_delete->next_iter;
            head_edge->prev_iter = NULL;
            edges_numbr--;
            (edge.pred_node).remove_pred(edge.pred_itr_loc);
            (edge.succ_node).remove_succ(edge.succ_itr_loc);
            delete to_delete->data;
            delete to_delete;
            return;
        }
        if( to_delete->next_iter == NULL &&
            to_delete            == tail_edge &&
            edges_numbr          != 0)
        {
            tail_edge = to_delete->prev_iter;
            tail_edge->next_iter = NULL;
            edges_numbr--;
            (edge.pred_node).remove_pred(edge.pred_itr_loc);
            (edge.succ_node).remove_succ(edge.succ_itr_loc);
            delete to_delete->data;
            delete to_delete;
            return;
        }
        if( to_delete->next_iter != NULL &&
            to_delete->prev_iter != NULL &&
            edges_numbr          != 0)
        {
            (to_delete->prev_iter)->next_iter = to_delete->next_iter;
            (to_delete->next_iter)->prev_iter = to_delete->prev_iter;
            edges_numbr--;
            (edge.pred_node).remove_pred(edge.pred_itr_loc);
            (edge.succ_node).remove_succ(edge.succ_itr_loc);
            delete to_delete->data;
            delete to_delete;
            return;
        }

            //!throw
    }

    template <class NodeT, class EdgeT> void
    Graph<NodeT, EdgeT>::remove(NodeT& node)
    {
        node_iterator* to_delete = (node_iterator*) node.graph_itr_loc;
        if( nodes_numbr == 0)
        {
            //!throw
        }
        if( to_delete->next_iter == NULL &&
            to_delete->prev_iter == NULL &&
            to_delete            == head_node &&
            to_delete            == tail_node &&
            nodes_numbr          == 1)
        {

            head_node   = NULL;
            tail_edge   = NULL;
            edges_numbr = 0;

            while( node.head_pred != NULL )
                remove(node.first_pred());
            while( node.head_succ != NULL )
                remove(node.first_succ());
            delete to_delete->data;

            delete to_delete;
            return ;
        }
        if( to_delete->prev_iter == NULL &&
            to_delete            == head_node &&
            nodes_numbr          != 0)
        {
            head_node            = to_delete->next_iter;
            head_node->prev_iter = NULL;
            nodes_numbr--;

            while( node.head_pred != NULL )
                remove(node.first_pred());
            while( node.head_succ != NULL )
                remove(node.first_succ());
            delete to_delete->data;

            delete to_delete;
            return;
        }
        if( to_delete->next_iter == NULL &&
            to_delete            == tail_node &&
            nodes_numbr          != 0)
        {
            tail_node = to_delete->prev_iter;
            tail_node->next_iter = NULL;
            nodes_numbr--;

            while( node.head_pred != NULL )
                remove(node.first_pred());
            while( node.head_succ != NULL )
                remove(node.first_succ());
            delete to_delete->data;

            delete to_delete;
            return;
        }
        if( to_delete->next_iter != NULL &&
            to_delete->prev_iter != NULL &&
            nodes_numbr          != 0)
        {
            (to_delete->prev_iter)->next_iter = to_delete->next_iter;
            (to_delete->next_iter)->prev_iter = to_delete->prev_iter;
            nodes_numbr--;

            while( node.head_pred != NULL )
                remove(node.first_pred());
            while( node.head_succ != NULL )
                remove(node.first_succ());
            delete to_delete->data;

            delete to_delete;
            return;
        }

            //!throw

    }

    template <class NodeT, class EdgeT>
    Graph<NodeT, EdgeT>::~Graph()
    {
        while( head_node != NULL )
            remove(*(head_node->data));
    }

}; // namespace Task
