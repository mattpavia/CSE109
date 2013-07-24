/*
  Matthew Pavia
  mfp215
  CSE 109
  Program #8
*/

template <class KEY,class DAT>
class Node{
private:
  KEY key;
public:
  DAT data;
  Node<KEY, DAT> *child[2];
  static const int L=0, R=1;
  Node(KEY k, DAT d, Node *left =NULL,Node * right=NULL);
  Node(const Node<KEY, DAT> &n);
  KEY getKey() const;

  template <class K,class D>
  friend ostream & operator <<(ostream &out, const Node<K,D> &n);
};

template <class KEY,class DAT>
Node<KEY,DAT>::Node(KEY k, DAT d = 0, Node*left, Node*right):key(k),data(d){
  child[L] = left;
  child[R]= right;
}

template <class KEY,class DAT>
Node<KEY,DAT>::Node(const Node<KEY,DAT> &n):key(n.key),data(n.data){
  child[L] = n.child[L];
  child[R] = n.child[R];
}

template <class KEY,class DAT>
KEY Node<KEY,DAT>::getKey() const {return key;}

template <class K,class D>
ostream & operator << (ostream &out, const Node<K,D> &n){
  out << "["<<n.key<<"," <<n.data<<"]";
  return out;
}
