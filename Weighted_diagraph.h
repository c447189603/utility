#ifndef WEIGHTED_DIAGRAPH_H
#define WEIGHTED_DIAGRAPH_H

#include "utility.h"
typedef int Vertex;

template<class Weight, int max_size>
class Diagraph{
    public:
    	Diagraph();
    	void read();
    	void write();
    	void set_distances(Vertex source, Weight distance[]) const;
    protected:
    	int count;
    	Weight adjacency[max_size][max_size];
};

template<class Weight, int max_size>
Diagraph<Weight, max_size>::Diagraph()
{
	count = 0;
}

template<class Weight, int max_size>
void Diagraph<Weight, max_size>::read()
{
	cin >> count;
	for (int i = 0; i < count; i++) {
		for (int j = 0; j < count; j++) {
			int temp;
			cin >> temp;
			if (temp == -1) adjacency[i][j] = numeric_limits<int>::max();
			else adjacency[i][j] = temp;
		}
	}
}

template<class Weight, int max_size>
void Diagraph<Weight, max_size>::write()
{
	cout << count << endl;
	for (int i = 0; i < count; i++) {
		for (int j = 0; j < count; j++) {
			cout <<  adjacency[i][j] << " ";
		}
		cout << endl;
	}
}

template<class Weight, int max_size>
void Diagraph<Weight, max_size>::set_distances(Vertex source, Weight distance[]) const
/* Post: The array distance gives the minimal path weight from vertex source to each
         vertex of the Diagraph. */
{
	Vertex v, w;
	bool found[max_size];  //   Vertices found in S
	for (v = 0; v < count; v++){
		found[v] = false;
		distance[v] = adjacency[source][v];
	}
	found[source] = true;  // Initialize with vertex source alone in the set S.
	distance[source] = 0;
	for (int i = 0; i < count; i++){  // Add one vertex to S on each pass.   
	    Weight min = infinity;
		for(w = 0; w < count; w++)if(!found[w])
		  if (distance[w] < min){
		  	v = w;
		  	min = distance[w];
		  }
		found[v] = true;
		for (w = 0; w < count; w++)if(!found[w])
		  if (min + adjacency[v][w] < distance[w])
		    distance[w] = min + adjacency[v][w];      
	}	
}

#endif 
