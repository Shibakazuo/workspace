void clearStack(int min, int depth) {
	dbg(min);
	int len = open.size();
   	rep(i, len) {
   		if(open.top().puzzle[10] != depth) {
   			tmp.push(open.top());
   		}
   		if(open.top().puzzle[9] == min && open.top().puzzle[10] == depth) tmp.push(open.top());
   		//push min cost and other branch to tmp 
   		open.pop();
   	}
   	len =tmp.size();
   	rep(i, len){
   		open.push(tmp.top());
   		tmp.pop();
   		output(open.top());
		dbg(open.top().puzzle[9]);
		dbg(open.top().puzzle[10]);
   	}
   	dbg(open.size());
}

// void dbgopen(){
// 	rep(i, open.size()) {
//    		output(open.top());
//    		dbg(open.top().cost-open.top().depth);
//    		tmp.push(open.top());
//    		open.pop();
//    	}
//    	rep(i,tmp.size()) {
//    		open.push(tmp.top());
//    		tmp.pop();
//    	}

// }
bool isSamePuzzle(state x1, state x2) {
	rep(i, 9){
		if(x1.puzzle[i] != x2.puzzle[i]) return false;
	}
	return true;
}



void aStarH1(){
	state now = open.top();

	if(open.empty()){
		cout<<"Open list is empty"<<endl;
		return;
	}
	
	open.pop();	
	now.depth++;
	state x = now;
	int min = 99999;

	int index;
	rep(i,9){
		if (x.puzzle[i] == 0) {
            index = i;
            break;
        }
    }//index of 0 panel


	if(isFinished(x)){
		cout << "Finished" << endl;
		close.push_back(x);
		rep(i,close.size()) {
			cout << i << endl;
			output(close[i]);
		}
		return;
	} 

    if(index-3 >= 0) {
    	swap(x.puzzle[index-3], x.puzzle[index]);
    	x.cost = x.depth + calCost(x);
    	open.push(x);
    	x = now;
   	} 
   	if(index % 3 != 0) {
    	swap(x.puzzle[index-1], x.puzzle[index]);
    	x.cost = x.depth + calCost(x);  	
    	open.push(x);
    	x = now;
   	}
    if(index % 3 != 2) {
    	swap(x.puzzle[index+1], x.puzzle[index]);
    	x.cost = x.depth + calCost(x);  	
    	open.push(x);
    	x = now;
   	}  
    if(index+3 < 9) {
    	swap(x.puzzle[index+3], x.puzzle[index]);
    	x.cost = x.depth + calCost(x);  	
    	open.push(x);
    	x = now;
   	}

   	dbg(open.size());

   	// dbgopen();
   	// return;
   	// if(m)
   	clearStack(min, now.depth);
   	aStarH1();
   	return;
}