#include<iostream>
#include<unordered_map>
#include<string>
#include<algorithm>

using namespace std;

// Create Worker Node
class WorkerNode {
	private:
		double cpu;
		double mem;
	
	public:
		WorkerNode() {
			this->cpu = 200.0;
			this->mem = 2048.0;
		}
		
		pair<double,double> get(){
			return {cpu,mem};
		}
};

int main() {
    
    return 0;
}