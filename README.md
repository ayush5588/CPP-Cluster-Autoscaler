# CPP-Cluster-Autoscaler
Cluster Autoscaler prototype in C++

Use this online c++ compiler to execute the code: https://www.onlinegdb.com/online_c++_compiler

### ```What is Cluster Autoscaler?```
The cluster autoscaler is a Kubernetes tool that increases or decreases the size of a Kubernetes cluster (by adding or removing nodes), based on the presence of pending pods and node utilization metrics.

### ```When Cluster Autoscaler scales up?```
Cluster Autoscaler scales up when it sees pending pods which are unscheduled because the resources requested by them can't be allocated as lack of resources so it scales up
the number of nodes and the pending pods gets scheduled on the newly created nodes with the help of scheduler.

### ```When Cluster Autoscaler scales down?```
When the cluster autoscaler sees that certain nodes are underutilized (i.e resources such as CPU, Memory is being utilized lesser than the specified minimum threshold for them) or the current time belongs to the specified downtime of the application, the CA does the pre-removal checks on them. These pre-removal checks involve making sure that the node that has being selected to be removed does not contain pods which have their local storage attached or the pods have PDB (Pod Disruption Budget) defined for them, etc. 
