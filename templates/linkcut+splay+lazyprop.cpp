// First used in https://www.hackerrank.com/contests/university-codesprint-3/challenges/simple-tree-counting/problem

struct node {
	node *left, *right, *par, *path_parent;
  int val, lazy;
	
	node(int _val = 1) {
		left = right = par = path_parent = 0;
    val = _val;
    lazy = 0;
	}
} *root;

void propagate(node *p) {
  if (p->left) {
    p->left->val += p->lazy;
    p->left->lazy += p->lazy;
  }
  if (p->right) {
    p->right->val += p->lazy;
    p->right->lazy += p->lazy;
  }
  p->lazy = 0;
}

void zig(node *p) {
	node *q = p->par;
	node *r = q->par;
	
	if (q->left = p->right) q->left->par = q;
	q->par = p; p->right = q;

	if (p->par = r) {
		if (r->left == q) r->left = p;
		else r->right = p;
	}
  
  p->path_parent = q->path_parent;
  q->path_parent = 0;
}

void zag(node *p) {
	node *q = p->par;
	node *r = q->par;
	
	if (q->right = p->left) q->right->par = q;
	q->par = p; p->left = q;
	
	if (p->par = r) {
		if (r->left == q) r->left = p;
		else r->right = p;
	}
	
  p->path_parent = q->path_parent;
  q->path_parent = 0;
}

void splay(node *p, node *par = 0) {
	while (p->par != par) {
		node *q = p->par;
		node *r = q->par;
		
		if (r != par) {	
      propagate(r); propagate(q); propagate(p);
		  if (r->left == q) {
        if (q->left == p) zig(q), zig(p);
        else zag(p), zig(p);
      } else {
        if (q->left == p) zig(p), zag(p);
        else zag(q), zag(p);
      }
    } else {
      propagate(q); propagate(p);
      if (q->left == p) {
        zig(p);
      } else zag(p);
    }
  }
  propagate(p);
}

void access(node *p) {
  splay(p); 
  if (p->right) {
    p->right->path_parent = p;
    p->right->par = 0;
    p->right = 0;
  }
  
  while (p->path_parent) {
    node *q = p->path_parent;
    splay(q);
    
    if (q->right) {
      q->right->path_parent = q;
      q->right->par = 0;
    }
    q->right = p;
    p->par = q;
    p->path_parent = 0;
    zag(p);
  }
}

node *findRoot(node *v) {
  access(v);
  while (v->left) {
    propagate(v);
    v = v->left;
  }
  splay(v);
  return v;
}

// Assumption: v is root, v and w are in different trees.
// Output: v will be child of w.
void link(node *v, node *w) {
  access(v); access(w);
  v->left = w;
  w->par = v;
  w->val += v->val;
  w->lazy += v->val;
}

// Assumption: parent of v exists.
// Output: Cut v from its parent.
void cut(node *v) {
  access(v);
  if (v->left) {
    v->left->val -= v->val;
    v->left->lazy -= v->val;
    
    v->left->par = 0;
    v->left = 0;
  }
}
