/*
  Matthew Pavia
  mfp215
  CSE 109
  Program #8
*/

#include "node.t"

template <class KEY,class DAT>
class Tree{
private:
  Node<KEY,DAT> *root;
public:
  Tree();
  Tree(const Tree<KEY,DAT> &t);
  const Tree<KEY,DAT>& operator =(const Tree<KEY,DAT> &t);

  template <class K,class D>
  friend ostream & operator<<(ostream & out, const Tree<K,D> &t);

  bool inTree(KEY k) const;
  DAT& operator [](KEY k);
  DAT& operator [](KEY k) const;
  ~Tree();
private:
  Node<KEY,DAT> * locate(KEY k, Node<KEY,DAT> * rt) const;
  ostream& display(ostream &out, Node<KEY,DAT> * r, int dir=1)const;
  void add(KEY k, Node<KEY,DAT> *&r);
  void kill(Node<KEY,DAT> *&rt);
  void copy(Node<KEY,DAT> *rt, Node<KEY,DAT> *&newRt);
};

template <class KEY,class DAT>
Tree<KEY,DAT>::Tree(){
  root = NULL;
}

template <class KEY,class DAT>
Tree<KEY,DAT>::Tree(const Tree<KEY,DAT> &t){
  copy(t.root,root);
}

template <class KEY,class DAT>
void Tree<KEY,DAT>::copy(Node<KEY,DAT> *rt, Node<KEY,DAT> *&newRt){
  if(rt !=NULL){
    newRt = new Node<KEY,DAT>(rt->getKey(),rt->data);
    // check(newRt != NULL,"(Tree::copy(()) heap overflow");
    copy(rt->child[Node<KEY,DAT>::L],newRt->child[Node<KEY,DAT>::L]);
    copy(rt->child[Node<KEY,DAT>::R], newRt->child[Node<KEY,DAT>::R]);
  }
}

template <class KEY,class DAT>
const Tree<KEY,DAT> & Tree<KEY,DAT>::operator=(const Tree<KEY,DAT> &t){
  if(this != &t){
    kill(root);
    copy(t.root,root);
  }
  return *this;
}

template <class KEY,class DAT>
void Tree<KEY,DAT>::kill(Node<KEY,DAT> *&rt){
  if(rt !=NULL){
    kill(rt->child[Node<KEY,DAT>::L]);
    kill(rt->child[Node<KEY,DAT>::R]);
    delete rt;
    rt =NULL;
  }
}

template <class KEY,class DAT>
DAT & Tree<KEY,DAT>::operator[](KEY k){
  if(!inTree(k)){
    add(k,root);
  }
  return locate(k,root)->data;
}

template <class KEY,class DAT>
DAT & Tree<KEY,DAT>::operator[](KEY k) const{
  if(!inTree(k)){
    //error
  }
  return locate(k,root)->data;
}

template <class KEY,class DAT>
void Tree<KEY,DAT>::add(KEY k, Node<KEY,DAT> *&r){
  if(r== NULL){
    r = new Node<KEY,DAT>(k);
  //check(heap area);
  }
  else if(k<r->getKey())
    add(k,r->child[Node<KEY,DAT>::L]);
  else
    add(k,r->child[Node<KEY,DAT>::R]);
}

template <class KEY,class DAT>
Tree<KEY,DAT>::~Tree(){
  kill(root);
}

template <class KEY,class DAT>
bool Tree<KEY,DAT>::inTree(KEY k) const{
  return locate(k,root) != NULL;
}

template <class KEY,class DAT>
Node<KEY,DAT> * Tree<KEY,DAT>::locate(KEY k, Node<KEY,DAT> *rt) const{
  if(rt==NULL)
    return rt;
  if(k==rt->getKey())
    return rt;
  if(k<rt->getKey())
    return locate(k,rt->child[Node<KEY,DAT>::L]);
  else
    return locate(k,rt->child[Node<KEY,DAT>::R]);
}

template <class K, class D>
ostream& operator <<(ostream &out, const Tree<K,D> &t){
  return t.display(out, t.root);
}

template <class KEY,class DAT>
ostream & Tree<KEY,DAT>::display(ostream &out, Node<KEY,DAT> *r, int dir) const
{
  if(r != NULL){
    display(out,r->child[dir],dir);
    out<<*r<<endl;
    display(out,r->child[1-dir],dir);
  }
return out;
}


  
  


