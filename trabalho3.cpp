#include <vector>
#include <iostream>
#include <algorithm>
#include <math.h>
#include <array>

//int total = 0;
int debug = false;

//kruskal
std::vector<int> set;
std::vector<int> rank;
std::vector<std::array<int, 3>> edges;
int circuits, biggest_circuit, longest_lane, total; 

//tarjan
int t;
std::vector<int> low;
std::vector<int> dfs;
std::vector<int> S;
std::vector<int> C;
std::vector<std::vector<int>> Scc;


bool sort_vector(const std::array<int,3>& struct1, const std::array<int,3>& struct2)
{
    return (struct1[2] < struct2[2]);    
}

void make_set(int i){
    set[i]=i;
    rank[i]=0;
}

int find(int a){
    if(set[a]!=a){
        set[a]=find(set[a]);
    }
    return set[a];
}

void link(int a, int b){
    if(rank[a]> rank[b]){
        set[b]=a;
    }
    else{
        set[a]=b;
    }
    if(rank[a]==rank[b]){
        rank[b]++;
    }
}

void unionof(int a, int b){
    link(find(a), find(b));
}



void tarjan(int v){
    low[v]= t;
    dfs[v]=t;
    t++;
    S.push_back(v);
    int w, aux;
    for (auto& it : edges) {
        w=it[1];
        aux= it[0];
        if(aux==v){
            if(dfs[w]==-1){
                tarjan(w);
                low[v]=std::min(low[v],low[w]);
            }
            else if(std::find(S.begin(), S.end(), w)!= S.end()){
                low[v]=std::min(low[v], dfs[w]);
            }
                    
        }
    }


    if(low[v]==dfs[v]){
        C = std::vector<int> ();
        do{
            w= S.back();
            S.pop_back();
            C.push_back(w);

        }while(w!=v);

        Scc.push_back(C);
    }

}



void kruskal(const int& n, std::vector<int>& circuit){
    set = std::vector<int> (n);
    rank= std::vector<int> (n);
    for(int v=0; v<n; v++){
        make_set(v);
        std::sort(edges.begin(), edges.end(), sort_vector);
    }

    int sum=0;

    int u, w;
    for (auto& it : edges) {
        w=it[1];
        u= it[0];
        if(std::find(circuit.begin(), circuit.end(), u)!= circuit.end() && std::find(circuit.begin(), circuit.end(), w)!= circuit.end()){
            if(find(u)!= find(w)){
                unionof(w,u);
                sum += it[2];
            }
            
        }
    }
    

    total+= sum;
    if((int) circuit.size()> biggest_circuit) biggest_circuit=(int) circuit.size();
    if(sum > longest_lane) longest_lane=sum;

    if(debug) std::cout<< "\nNew circuit in kruskal: sum: " << sum <<" total: "<< total << " biggest_circuit: "<< biggest_circuit << " longest lane: "<< longest_lane << "\n";


}




void questions(const int& n, const int& q){

    biggest_circuit=0;
    longest_lane=0;
    total=0;
    
    t=0;
    low= std::vector<int> (n);
    dfs=std::vector<int>(n,-1);
    Scc = std::vector<std::vector<int>>  ();
    C=std::vector<int>();

    for(int i=0; i<n; i++) tarjan(i);

    Scc.erase(std::remove_if(
    Scc.begin(), Scc.end(),
    [](const std::vector<int>& x) { 
        return (int) x.size() <= 1; // put your condition here
    }), Scc.end());

    // remover os circuits with only 1 vect

    if(debug){
        for(int i=0; i<(int) Scc.size(); i++){
            std::cout<< "\nCircuito "<< i <<"\n";
            for(int j=0; j<(int) Scc[i].size(); j++){
                std::cout<< Scc[i][j] <<" ";
            }
        }

    }


    
    for(int i=0; i<(int) Scc.size(); i++){
        kruskal(n, Scc[i]);
    }


    std::vector<int> quest (4,-1);
    quest[0]= (int) Scc.size();
    quest[1]= biggest_circuit;
    quest[2]= longest_lane;
    quest[3]= total;
    if(debug) std::cout<< "\nResult\n";
    for(int aux=0; aux<q; aux++){
        std::cout<< quest[aux];
        if(aux<q-1) std::cout<<" ";
    }
    std::cout<< "\n";
}


int main(){
    //std::ios_base::sync_with_stdio(0);
    //std::cin.tie(0);
    int test, n, m, q;
    int A, B, D;
    //std::vector<int> grafos;

    std::cin >> test;

    for(int aux=0; aux<test; aux++){
        std::cin >> n;
        std::cin >> m;
        std::cin >> q;
        edges= std::vector<std::array<int,3>>();
        
        for (int i = 0; i < m; i++){
            std::cin >> A;
            std::cin >> B;
            std::cin >> D;
            edges.push_back({A-1,B-1,D});
            //grafo[A][B]=D;
            
        }

        questions(n, q);
             
    }


    return 0;
}
