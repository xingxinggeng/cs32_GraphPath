//Xingxing,Geng 11/25/2017
//Implementation of paths.cpp

#include "graph.h"
#include <climits> // provides ULONG_MAX, maximum size_t
#include <list>
#include <vector>
#include "wtdgraph.h"//?
using main_savitch_15::wtdgraph;//?
using std::size_t;
using std::vector;
using std::list;
using std::string;

const size_t INF = ULONG_MAX;

void shortest(wtdgraph<string> &g,size_t start,vector<size_t> &distances,vector<list<size_t> > &paths){
//		distances.resize(g.size(),INF);
		for(size_t i=0;i<g.size();++i){
				distances[i] = INF;
		}
		distances[start] = 0;
		std::set<size_t> allowed_vertices;
		std::vector<size_t> predecessor(g.size());
//		allowed_vertices.insert(start);//no need?
//		for(std::set<size_t>::iterator it = g.neighbors(start).begin();i != g.neighbors(start).end();i++){
//				distances[*it] = g.edge_weight(start,*it);
//		}//can use is_edge() and for loop to finish this step as well
		for(size_t j = 1;j<g.size();++j){
				size_t next;
				size_t smallest_value = INF;
				for(size_t k=0;k<g.size();k++){
						if(allowed_vertices.find(k) == allowed_vertices.end() && distances[k]<smallest_value){
								next = k;
								smallest_value = distances[k];
						}//find the next
				}
				allowed_vertices.insert(next);
				for(size_t v = 0; v< g.size();v++){
						if(allowed_vertices.find(v) == allowed_vertices.end() && g.is_edge(next,v)){
								size_t sum = distances[next] + g.edge_weight(next,v);
								if(sum < distances[v]){
										distances[v] = sum;
										predecessor[v] = next;
								}
						}
				}
		}
		for(size_t ve = 0; ve<g.size();++ve){
				size_t vertex_on_path = ve;
				paths[ve].push_front(vertex_on_path);
				while (vertex_on_path != start){
						vertex_on_path = predecessor[vertex_on_path];
						paths[ve].push_front(vertex_on_path);
				}
				paths[ve].push_front(start);//need?
		}
}
