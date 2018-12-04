// Todd Vorisek
// build.hpp
// CS 411 Assignment 5
// 11/23/2018

#include "build.hpp"
#include <vector>
#include <algorithm>

using std::vector;
using std::sort;

using Bridge = vector<int>;

#include <iostream>
void print_bridges(const vector<Bridge> & bridges)
{
    for(auto const& i: bridges){
        std::cout << i[WEST] << " " << i[EAST] << " " << i[TOLL] << std::endl;
    }
}

bool crosses(const Bridge & l, const Bridge & r) {
    return ( l[WEST] == r[WEST] ||  l[EAST] >= r[EAST]);
}

vector<Bridge> sort_bridges(const vector<Bridge> & bridges)
{
    vector<Bridge> sorted_bridges(bridges);
    sort(sorted_bridges.begin(), sorted_bridges.end());

    // Throw out identical bridges with smaller tolls.
    if(sorted_bridges.size()>0) 
    {
        for (unsigned int i = 0; i < sorted_bridges.size()-1; ++i){
            if (sorted_bridges[i][WEST]==sorted_bridges[i+1][WEST] &&
                sorted_bridges[i][EAST]==sorted_bridges[i+1][EAST])
            {
                sorted_bridges.erase(sorted_bridges.begin()+i);
            }
        }
    }

    return sorted_bridges;
}

int build(int east, int west, const vector<Bridge> & bridges)
{
    vector<Bridge> sorted_bridges = sort_bridges(bridges);
    vector<unsigned int> bridge_gcs(sorted_bridges.size(), 0);
    // print_bridges(sorted_bridges);

    for(unsigned int i=0; i < sorted_bridges.size(); ++i){
        Bridge r_bridge = sorted_bridges[i];
        bridge_gcs[i] = r_bridge[TOLL];

        for(int j = i; j >= 0; --j){
            Bridge l_bridge = sorted_bridges[j];
            if (!crosses(l_bridge,r_bridge)){
                if (bridge_gcs[i] < (bridge_gcs[j] + r_bridge[TOLL]))
                    bridge_gcs[i] = bridge_gcs[j] + r_bridge[TOLL];
            }
        }
    }

    int max = 0;
    for (auto i : bridge_gcs){
        max = i > max ? i : max;
    }

    return max; 
}
