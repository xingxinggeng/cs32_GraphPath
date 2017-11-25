//XIngxing,Geng 11/24/2017
//Header file and implementation of derived class wtdgraph

#ifndef WTDGRAPH_H
#define WTDGRAPH_H
#include <cstdlib>
#include <set>
#include <map>
#include <cassert>
#include <utility>
#include "graph.h"

using namespace std;
using std::size_t;
//using std::map;
typedef pair<size_t, size_t> Pair;
typedef map<Pair, size_t> Map;

namespace main_savitch_15{

template <class Item>
class wtdgraph : public graph<Item>
{
	public:
			wtdgraph() : graph<Item>(){ }

			wtdgraph( size_t initial_allocation ) : graph<Item>(initial_allocation){//weights=NULL;
			}

			wtdgraph(const wtdgraph &source) : graph<Item>(source){
				for(size_t i=0;i<source.size();i++){
					for(size_t j=0;j<source.size();j++){
							if (i == j) continue;
							if(source.is_edge(i,j)){
									Pair ij(i,j);
									weights[ij] = source.edge_weight(i,j);//ij is not a size_t type?
							}
					}
				}
			}

			//destructor
			virtual ~wtdgraph(){				
				weights.clear();
			}

			//overload add_edge
			void add_edge(size_t source, size_t target, size_t weight = 0){
					graph<Item>::add_edge(source,target);
					size_t i = source;
					size_t j = target;
					Pair ij(i,j);
					weights[ij] = weight;
			}

			//redefine
			void remove_edge(size_t source, size_t target){
					graph<Item>::remove_edge(source,target);
					size_t i = source;
					size_t j = target;
					Pair ij(i,j);
					weights.erase(ij);
			}

			wtdgraph<Item> &operator=(const wtdgraph &source){
					if(this == &source){return *this;}
					graph<Item>::operator=(source);
					weights.clear();//is this valid
					for(size_t i=0;i<source.size();i++){
							for(size_t j=0;j<source.size();j++){
									if(i == j)continue;
									if(source.is_edge(i,j)){
											Pair ij(i,j);
											weights[ij] = source.edge_weight(i,j);
									}
							}
					}
				}

			//override resize
			virtual void resize(size_t new_allocation){
					if(new_allocation <=graph<Item>::size()){return ;}
					else{
						graph<Item>::resize(new_allocation);	
					}
			}


			//add new function
			size_t edge_weight(size_t source,size_t target) const{
					assert(graph<Item>::is_edge(source,target));
					size_t i = source;
					size_t j = target;
					Pair ij(i,j);
					return weights.at(ij);
			}
	
	private:
			Map weights;


	};
}
#endif
