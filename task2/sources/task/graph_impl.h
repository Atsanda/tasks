/**
 * @file: task/graph_impl.h
 * Solution implementation of the programming task 2
 */

namespace Task
{
// ---- Graph class implemention ----
    //
    // ---- Graph::Node class implemention ----
        //
        // ---- Graph::Node::pred_iterator class imlemention
            template < class NodeT, class EdgeT>
            Graph<NodeT,EdgeT>::Node::pred_iterator::pred_iterator():
                next_iter(NULL) , pred_edge(NULL) {}

            template < class NodeT, class EdgeT>
            Graph<NodeT,EdgeT>::Node::pred_iterator::pred_iterator(typename Graph<NodeT,EdgeT>::Node::pred_iterator *p,EdgeT *edg):
                next_iter(p) , pred_edge(edg) {}

            template < class NodeT, class EdgeT>
            Graph<NodeT,EdgeT>::Node::pred_iterator::~pred_iterator()
            {
                next_iter=NULL;
                pred_edge=NULL;
            }

            template < class NodeT, class EdgeT> bool
            Graph<NodeT,EdgeT>::Node::pred_iterator::operator ==(const typename Graph<NodeT,EdgeT>::Node::pred_iterator& other)
            {
                if( next_iter==other.get_next_iter() &&
                    pred_edge==other.get_pred_edge())
                    return true;
                else
                    return false;
            }

            template < class NodeT, class EdgeT> bool
            Graph<NodeT,EdgeT>::Node::pred_iterator::operator !=(const typename Graph<NodeT,EdgeT>::Node::pred_iterator& other)
            {
                if( next_iter!=other.get_next_iter() ||
                    pred_edge!=other.get_pred_edge())
                    return true;
                else
                    return false;
            }

            template < class NodeT, class EdgeT> typename Graph<NodeT,EdgeT>::Node::pred_iterator&
            Graph<NodeT,EdgeT>::Node::pred_iterator::operator ++()
            {
                if(next_iter==NULL)
                    throw Error();

                pred_edge=next_iter->get_pred_edge();
                next_iter=next_iter->get_next_iter();

                return *this;
            }

            template < class NodeT, class EdgeT> typename Graph<NodeT,EdgeT>::Node::pred_iterator
            Graph<NodeT,EdgeT>::Node::pred_iterator::operator ++(int)
            {
                if(next_iter==NULL)
                    throw Error();

                pred_iterator tmp(next_iter,pred_edge);

                pred_edge=next_iter->get_pred_edge();
                next_iter=next_iter->get_next_iter();

                return tmp;
            }

            template < class NodeT, class EdgeT> typename Graph<NodeT,EdgeT>::Node::pred_iterator&
            Graph<NodeT,EdgeT>::Node::pred_iterator::operator =(const typename Graph<NodeT,EdgeT>::Node::pred_iterator& other)
            {
                pred_edge=other.get_pred_edge();
                next_iter=other.get_next_iter();

                return *this;
            }

            template < class NodeT, class EdgeT> EdgeT&
            Graph<NodeT,EdgeT>::Node::pred_iterator::operator *()
            {
                return *(pred_edge);
            }

            template < class NodeT, class EdgeT> typename Graph<NodeT,EdgeT>::Node::pred_iterator*
            Graph<NodeT,EdgeT>::Node::pred_iterator::get_next_iter() const
            {
                return next_iter;
            }

            template < class NodeT, class EdgeT> EdgeT*
            Graph<NodeT,EdgeT>::Node::pred_iterator::get_pred_edge() const
            {
                return pred_edge;
            }
        //





}; // namespace Task
