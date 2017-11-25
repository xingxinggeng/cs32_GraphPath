//Xingxing,Geng 11/24/2017
// FILE: graph.cpp (part of the namespace main_savitch_15)
// TEMPLATE CLASS IMPLEMENTED: graph<Item> (See graph.h for documentation.)
// This file is included in the header file and not compiled separately.
// INVARIANT for the graph class:
//   1. The number of vertices in the graph is stored in the member variable
//      many_vertices.
//   1. These vertices are numbered from 0 to many_vertices-1.
//   2. edges is the adjacency matrix for the graph (with true in edges[i][j]
//      to indicate an edge from vertex i to vertex j).
//   3. For each i < many_vertices, labels[i] is the label of vertex i.

#include <cassert>    // Provides assert
#include <cstdlib>    // Provides size_t
#include <set>        // Provides set
using std::size_t;

namespace main_savitch_15
{
   template <class Item>
    graph<Item>::graph ( )// : many_vertices(0),allocated(0) 
   {
	  many_vertices = 0;
	   allocated = 0;
	   edges = NULL;
	   labels = NULL;
        // intentionally empty
    }

	template <class Item>
	graph<Item>::graph(size_t initial_allocation){
			many_vertices = 0;//important
			allocated = initial_allocation;
			labels = new Item[allocated];
			edges = new bool*[allocated];
			for(size_t i=0 ; i<allocated; i++){
					edges[i]= new bool[allocated];
			}
			for(size_t idx=0;idx<allocated;idx++){
					for(size_t ind=0;ind<allocated;ind++){
							edges[idx][ind]=false;//important
					}
			}
	}

	template <class Item>
	graph<Item>::graph(const graph &source){
//			operator = (source);
//			many_vertices = allocated = 0;
			resize(source.size());
			for(size_t i=0; i< source.size();++i){
					add_vertex(source[i]);
			}
			for(size_t j=0; j< source.size();++j){
					for(size_t idx = 0;idx < source.size(); idx++){
							edges[j][idx]= source.is_edge(j,idx);
					}
			}
	}

	template <class Item>
	graph<Item>::~graph(){
			for(size_t i=0;i<many_vertices;++i){
					delete [] edges[i];
			}
			delete [] edges;
			delete [] labels;
	}

	template<class Item>//not finished yet should this be a friend function?
	graph<Item>& graph<Item>::operator=(const graph &source){
			if(this == &source){
					return *this;
			}
			else{      
	//				many_vertices = allocated = 0;
					resize(source.size());
					for(size_t i=0; i< source.size();++i){
							add_vertex(source[i]);
					}//data in source may not true
					for(size_t j=0; j< source.size();++j){
						for(size_t idx = 0;idx < source.size(); idx++){
								edges[j][idx]= source.is_edge(j,idx);
								}
					}
				
								
			}
			return *this;
	}

	template<class Item>
	void graph<Item>:: resize(size_t new_allocation){
			if(new_allocation <=  allocated){return ;}
			else{
				Item* new_label = new Item[new_allocation];
				bool** new_edges = new bool*[new_allocation];
				for(size_t j=0; j<new_allocation;j++){
						new_edges[j] = new bool[new_allocation];//do I need to set other edges to be false and give labels 0.0
				}
/*				for(size_t a=0;a<new_allocation;a++){
						for(size_t b=0;b<new_allocation;b++){
								new_edges[a][b] = false;
						}
				}*///importent to set all edges to false
				for(size_t i=0;i<many_vertices;i++){
						new_label[i]=labels[i];
						for(size_t k=0; k< many_vertices;++k){
								new_edges[i][k]=edges[i][k];
						}
				}
				for(size_t m=0;m<allocated;m++){
						delete [] edges[m];
				}
				delete [] edges;	
				delete [] labels;
				allocated = new_allocation;
				labels = new_label;
				edges = new_edges;//have not changed many_vertices
			}
	}


    template <class Item>
    void graph<Item>::add_edge(size_t source, size_t target)
    // Library facilities used: cassert, cstdlib
    {
        assert(source < many_vertices);//need to resize? if source and target beyond many_vertices
        assert(target < many_vertices);
        edges[source][target] = true;
    }

    template <class Item>
    void graph<Item>::add_vertex(const Item& label)
    // Library facilities used: cassert, cstdlib
    {
        size_t new_vertex_number;
        size_t other_number;
		if(many_vertices == allocated){ 
				if(many_vertices == 0){resize(10);}
				else{
				resize(2*allocated);
				}
		}
        new_vertex_number = many_vertices;
        many_vertices++;
        for (other_number = 0; other_number < many_vertices; ++other_number)
        {
            edges[other_number][new_vertex_number] = false;
            edges[new_vertex_number][other_number] = false;
        }
        labels[new_vertex_number] = label;
    }

    template <class Item>
    bool graph<Item>::is_edge(size_t source, size_t target) const
    // Library facilities used: cassert, cstdlib
    {
        assert(source < many_vertices);//will this have memory leak since I have not set edges all to be false in resize()
        assert(target < many_vertices);
        return edges[source][target];
    }

    template <class Item>
    Item& graph<Item>::operator[ ] (size_t vertex)
    // Library facilities used: cassert, cstdlib
    {
        assert(vertex < many_vertices);
        return labels[vertex];     // Returns a reference to the label
    }

    template <class Item>
    Item graph<Item>::operator[ ] (size_t vertex) const
    // Library facilities used: cassert, cstdlib
    {
        assert(vertex < many_vertices);
        return labels[vertex];     // Returns only a copy of the label
    }

    template <class Item>
    std::set<size_t> graph<Item>::neighbors(size_t vertex) const
    // Library facilities used: cassert, cstdlib, set
    {
        std::set<size_t> answer;
        size_t i;

        assert(vertex < many_vertices);

        for (i = 0; i < many_vertices; ++i)
        {
            if (edges[vertex][i])
                answer.insert(i);
        }
        return answer;
    }

    template <class Item>
    void graph<Item>::remove_edge(size_t source, size_t target)
    // Library facilities used: cassert, cstdlib
    {
        assert(source < many_vertices);
        assert(target < many_vertices);
        edges[source][target] = false;
    }
}
