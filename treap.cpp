//Normal Treap : O(logn) average
struct Treap{
	int val , random , cnt;
	Treap *left , *right;

	Treap(){
		left = right = NULL;
	}

	Treap(int _val){
		val = _val;
		cnt = 1;
		random = rand();
		keft = right = NULL;
	}

	void split(Treap *t , int x , Treap *l , Treap *r){
		if(!t){
			l = NULL;
			r = NULL;
		}
		else if(t->x  > x){
			r = t;
			split(r->left , x , l , r->left);
		}
		else{
			l = t;
			split(l->right , x , l->right , r);
		}

		update(l);
		update(r);
	}

	void merge(Treap *t , Treap *l , Treap *r){
		if(!t){
			return;
		}
		else if(l->random > r->random){
			l = t;
			merge(l->right , l->right , r);
		}
		else{
			r = t;
			merge(r->left , l , r->left);
		}
		update(t);
	}

	void insert(Treap *t , int val){
		if(!t){
			t = new Treap(val);
		}
		Treap *l = new Treap() , *r = new Treap() , *m = new Treap(val);
		split(t , val , l , r);
		merge(m , l , m);
		merge(t , m , r);
	}

	void erase(Treap *t , int val){
		if(!t){
			return;
		}
		Treap *l = new Treap() , *r = new Treap();
		split(t , val , l , r);
		merge(t , l , r);
	}

	int get(Treap *t){
		if(!t) return 0;
		else{
			return t->cnt;
		}
	}

	void update(Treap *t){
		return 1 + get(t->left) + get(t->right);
	}
};

//Implicit Treap:
//Like an array with: 
//Insert at arbitrary location
//Delete at arbitrary location
//merge two array
//split array
//all in O(logn) , no auxilliary space

//Treap to solve sum range query update replacing segment tree
//lazy propagation

struct Treap{
	int val , size , random , sum;
	Treap *left , *right;

	Treap(int _val){
		val = _val;
		size = 1;
		random = rand();
		sum = 0;
		left = right = NULL;
	}

	int size(Treap *t){
		if(!t){
			return 0;
		}
		return t->size;
	}

	int sum(Treap *t){
		if(!t){
			return 0;
		}
		return t->sum;
	}

	void update(Treap *t){
		t->size = 1 + size(t->left) + size(t->right);
	}
	void reset(Treap *t){
		if(!t) return;
		t->sum = t->val;
	}
	void lazyupdate(Treap *t){
		if(!t) return;
		int lazyval = t->lazy;
		t->sum += lazyval * size(t);
		if(t->left) t->left->lazy += lazyval;
		if(t->right) t->right->lazy += lazyval;
		t->lazy = 0;
	}
	void combine(Treap *t){
		if(!t) return;
		reset(t);
		if(t->left) lazyupdate(t->left);
		if(t->right) lazyupdate(t->right);
		t->sum += t->left->sum;
		t->sum += t->right->sum;
	}
	void split(Treap *t , Treap *l , Treap *r , int pos , int add = 0){
		if(!t) return;
		lazyupdate(t);
		int cur_pos = add + size(t->left);
		if(cur_pos <= pos){
			l = t;
			split(t->right , t->right , r , pos , cur_pos + 1);
		}
		else{
			r = t;
			split(t->left , l , t->left);
		}
		update(l);
		update(r);
		combine(l);
		combine(r);
	}

	void merge(Treap *t , Treap *l , Treap *r){
		if(!l || !r){
			t = !l ? r : l;
		}
		lazyupdate(l);
		lazyupdate(r);
		else if(l->random > r->random){
			l = t;
			merge(t->right , t->right , r);
		}
		else{
			r = t;
			merge(t->left , l , t->left);
		}
		update(t);
		combine(t);
	}
	void rangeupdate(Treap *t , int left , int right , int val){
		if(!t) return;
		Tree *l = new Treap() , *r = new Treap(), *mid = new Treap();
		split(t , l , r , left);
		split(r , m , r , right + 1);
		r->lazy += val;
		merge(r , m , r);
		merge(t , l , r);
	}
	int rangequery(Treap *t , int left , int right){
		if(!t) return;
		Tree *l = new Treap() , *r = new Treap() , *m = new Treap();
		split(t , l , r , left);
		split(r , m , r , right + 1);
		int res = r->sum;
		merge(r , m , r);
		merge(t , l , r);
		return res;
	}
};