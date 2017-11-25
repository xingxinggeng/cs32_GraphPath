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

namespace main_savitch_15{

template <class Item>
class wtdgraph : public graph<Item>
{
	public:
			wtdgraph() : graph<Item>(){ weights = NULL;}

			wtdgraph( size_t initial_allocation ) : graph<Item>(initial_allocation){//weights=NULL;
			}

			wtdgraph(const wtdgraph &source) : graph<Item>(source){
				weights = new map<size_t,size_t>[source.size()];
				for(size_t i=0;i<source.size();i++){
					for(size_t j=0;j<source.size();j++){
							if(source.is_edge(i,j)){
									weights[i][j] = source.edge_weight(i,j);//no need if statement?
							}
					}
				}
			}

			//destructor
			virtual ~wtdgraph(){
					if(weights != NULL){
							delete [] weights;
					}
			}

			//overload add_edge
			void add_edge(size_t source, size_t target, size_t weight = 0){
					graph<Item>::add_edge(source,target);
					weights[source][target] = weight;
			}

			//redefine
			void remove_edge(size_t source, size_t target){
					graph<Item>::remove_edge(source,target);
					weights[source][target]=0;
			}

			wtdgraph<Item> &operator=(const wtdgraph &source){
					if(this == &source){return *this;}
					size_t current_allocation = size();//no need?
					graph<Item>::operator=(source);
					delete [] weights;
					weights = new map<size_t,size_t>[source.size()];
					for(size_t i=0;i<source.size();i++){
							for(size_t j=0;j<source.size();j++){
									if(source.is_edge(i,j)){
											weights[i][j] = source.edge_weight(i,j);
									}
							}
					}
			}

			//override resize
			virtual void resize(size_t new_allocation){
					if(new_allocation <= size()){return ;}
					else{
						size_t current_allocation = size();
						graph<Item>::resize(new_allocation);
						map<size_t,size_t>* new_weights = new map<size_t,size_t>[new_allocation];
						for(size_t i = 0;i < current_allocation;i++){
								for(size_t j = 0;j < current_allocation;j++){
										new_weights[i][j] = weights[i][j];
								}
						}
						delete [] weights;
						weights = new_weights;
					}
			}


			//add new function
			size_t edge_weight(size_t source,size_t target) const{
					assert(is_edge(source,target));
					return weights[source][target];
									}
	
	private:
			map<size_t,size_t>* weights;


	};
}
#endif
