#include<iostream>
#include<unordered_map>
#include<map>
#include<string>
#include<algorithm>
#include<stdlib.h>
#include<ctime>

using namespace std;

// Global Variables
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

		// Initialize Node Pool
		// node pool size = 5
		void Init_NodePool() {
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
};


// Generating random traffic on the nodes in the NodePool by assigning nodes random values in the given range
void Metrics_Aggregator(){
	// srand((unsigned int)time(0));
	// Refer https://stackoverflow.com/questions/9459035/why-does-rand-yield-the-same-sequence-of-numbers-on-every-run 
	for(itr=NodePool.begin();itr!=NodePool.end();itr++){
		// generate random CPU usage in range [20,160]
		// generate random Memory usage in range [80,1638]
		int curr_cpu_usage = (rand() % (160 + 1 - 20) + 20);
		int curr_mem_usage = (rand() % (1638 + 1 - 80) + 80);
		(itr->second).first = curr_cpu_usage;
		(itr->second).second = curr_mem_usage;
	}
	
}

// Insert New Node in the NodePool
bool Insert_NewNode() {
	WorkerNode node;
	pair<double,double> p = node.get();
	p.first = (rand() % (160 + 1 - 20) + 20);
	p.second = (rand() % (1638 + 1 - 80) + 80);
	string nodeName = "Node_" + to_string(i);
	NodePool[nodeName] = p;
	++i;
	return true;
}

// Remove Node from the NodePool 
bool Remove_Node(string NodeName){
	if(NodePool.find(NodeName)!=NodePool.end()){
		NodePool.erase(NodeName);
		return true;
	}
	return false;
}

// Go over the NodePool. 
// Compare the current utilization of CPU and Memory with the Thresholds
void Cluster_Autoscaler() {
	for(itr=NodePool.begin();itr!=NodePool.end();itr++){

		int curr_cpu_utilization = (((itr->second).first) * 100) / 160;
		int curr_mem_utilization = (((itr->second).second) * 100) / 1638;

		cout<<itr->first<<" ";
		cout<<"Current CPU utilization: "<<curr_cpu_utilization<<"%\n";
		cout<<itr->first<<" ";
		cout<<"Current Memory utilization: "<<curr_mem_utilization<<"%\n\n";
		
		// Scale DOWN -> If both CPU and Memory current Utilization is less than 50%
		// If using srand() (at line 49) then change the min threshold to 80 (below is 50) for testing purpose
		if(curr_cpu_utilization < 50 && curr_mem_utilization < 50){
			cout<<"Scaling Down NodePool"<<"\n";
			if(Remove_Node(itr->first)){
				cout<<"Scale Down SUCCESS! "<<"\n";
				--itr;
			}else{
				cout<<"Scale Down FAILED! "<<"\n";
			}
		}
		
		// Scale UP -> If anyone of the CPU and Memory current Utilization is greater than 80%
		else if(curr_cpu_utilization > 80 || curr_mem_utilization > 80){
			cout<<"Scaling Up NodePool"<<"\n";
			if(Insert_NewNode()){
				cout<<"Scale Up SUCCESS! "<<"\n";
			}else{
				cout<<"Scale Up FAILED! "<<"\n";
			}
		}

		cout<<"NodePool Size: "<<NodePool.size()<<"\n\n";
	}
}


// keep scraping the data from Metrics_Collector() in every 10 seconds and invoke CA
void Prometheus() {
	int cnt = 0;
	while(cnt<2){
		Metrics_Aggregator();   // collect data
		Cluster_Autoscaler();  // send data
		cout<<"\n\n--------------------------------------------------------------\n\n";
		for(int j=0;j<10;j++);  // Wait for 10 seconds before next check
		++cnt;
	}
}

void display() {
    
	for(itr=NodePool.begin();itr!=NodePool.end();itr++) {
		cout<<itr->first<<" -> "<<(itr->second).first<<" "<<(itr->second).second<<"\n";
	}
}

int main() {
	WorkerNode obj;
	obj.Init_NodePool();
	Prometheus();
	display();
	NodePool.clear();
	return 0;
}
