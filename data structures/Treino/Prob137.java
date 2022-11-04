public boolean strict(){
		return strict(root);
		}

private boolean strict(BSTNode<T>t){
		if(t==null){
		return true;
		}else if(t.left==null&&t.right==null){
		return true;
		}else if((t.left!=null&&t.right==null)||(t.left==null&&t.right!=null)){
		return false;
		}else
		return(strict(t.left)&&strict(t.right));
		}