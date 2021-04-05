#include<iostream>
#include<unordered_map>
#include<map>
#include<string>
#include<algorithm>
#include<stdlib.h>

using namespace std;

// Global Variables
//unordered_map<string,pair<int,int>> NodePool;
map<string,pair<int,int>> NodePool;
map<string,pair<int,int>>::iterator itr;
int i = 1;

// Create Worker Node
class WorkerNode {
	private:
		int cpu;
		int mem;
	
	public:
		WorkerNode() {
			this->cpu = 200;
			this->mem = 2048;
		}
		
		pair<int,int> get(){
			return {cpu,mem};
		}
};

// Initialize Node Pool
void Init_NodePool() {
	 // node pool size = 5
	 while(i < 6){
	 	WorkerNode node;
	 	pair<int,int> p = node.get();
	 	p.first *=0.80;
	 	p.second *= 0.80;
	 	string nodeName = "Node_" + to_string(i);
	 	NodePool[nodeName] = p;
	 	++i;
	 }
}

void Metrics_Collector(){
	for(itr=NodePool.begin();itr!=NodePool.end();itr++){
		int curr_cpu_usage = (rand() % (160 + 1 - 20) + 20);
		int curr_mem_usage = (rand() % (1638 + 1 - 80) + 80);
		(itr->second).first = curr_cpu_usage;
		(itr->second).second = curr_mem_usage;
	}
	
}



int main() {
    Init_NodePool();
    return 0;
}