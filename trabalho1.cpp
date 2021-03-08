#include <iostream>
#include <algorithm>
#include <vector>

int nplays, best = 1000;
int debug = false;


std::vector<std::vector<int>> moveleft(std::vector<std::vector<int>> vect, int dim) {

    int number, position, countz = 0;

    for (int i = 0; i < dim; i++) {
        number = -1;
        position = -1;
        for (int j = 0; j < dim; j++) {

            if (vect[i][j] != 0 && vect[i][j] != number) {
                number = vect[i][j];
                position = j;
            }

            else if (vect[i][j] == number) {
                vect[i][position] = vect[i][position] * 2;
                vect[i][j] = 0;
                number = -1;
                position = -1;
            }
        }
    }
    for (int i = 0; i < dim; i++){
        for(int j = 0; j < dim; j++){
            if (vect[i][j] == 0){
                countz++;
            }
            else if( vect[i][j] != 0 && countz != 0){
                vect[i][j - countz] = vect[i][j];
                vect[i][j] = 0;
            }
        }
        countz = 0;
    }
    return vect;

}

std::vector<std::vector<int>> moveright(std::vector<std::vector<int>> vect, int dim){

    int number, position, countz = 0;

    for (int i = 0; i < dim; i++) {
        number = -1;
        position = -1;
        for (int j = dim - 1; j >= 0; j--) {

            if (vect[i][j] != 0 && vect[i][j] != number) {
                number = vect[i][j];
                position = j;
            }

            else if (vect[i][j] == number) {
                vect[i][position] = vect[i][position] * 2;
                vect[i][j] = 0;
                number = -1;
                position = -1;
            }

        }
    }
    for (int i = 0; i < dim; i++){
        for(int j = dim - 1; j >= 0; j--){
            if (vect[i][j] == 0){
                countz++;
            }
            else if( vect[i][j] != 0 && countz != 0){
                vect[i][j + countz] = vect[i][j];
                vect[i][j] = 0;
            }
        }
        countz = 0;
    }
    return vect;

}

std::vector<std::vector<int>> moveup(std::vector<std::vector<int>> vect, int dim){

    int number, position, countz = 0;

    for (int i = 0; i < dim; i++) {
        number = -1;
        position = -1;
        for (int j = 0; j < dim; j++) {

            if (vect[j][i] != 0 && vect[j][i] != number) {
                number = vect[j][i];
                position = j;
            }

            else if (vect[j][i] == number) {
                vect[position][i] = vect[position][i] * 2;
                vect[j][i] = 0;
                number = -1;
                position = -1;
            }
        }
    }
    for (int i = 0; i < dim; i++){
        for(int j = 0; j < dim; j++){
            if (vect[j][i] == 0){
                countz++;
            }
            else if( vect[j][i] != 0 && countz != 0){
                vect[j - countz][i] = vect[j][i];
                vect[j][i] = 0;
            }
        }
        countz = 0;
    }
    return vect;

}

std::vector<std::vector<int>> movedown(std::vector<std::vector<int>> vect, int dim){

    int number, position, countz = 0;

    for (int i = 0; i < dim; i++) {
        number = -1;
        position = -1;
        for (int j = dim - 1; j >= 0; j--) {

            if (vect[j][i] != 0 && vect[j][i] != number) {
                number = vect[j][i];
                position = j;
            }

            else if (vect[j][i] == number) {
                vect[position][i] = vect[position][i] * 2;
                vect[j][i] = 0;
                number = -1;
                position = -1;
            }

        }
    }
    for (int i = 0; i < dim; i++){
        for(int j = dim - 1; j >= 0; j--){
            if (vect[j][i] == 0){
                countz++;
            }
            else if(vect[j][i] != 0 && countz != 0){
                vect[j + countz][i] = vect[j][i];
                vect[j][i] = 0;
            }
        }
        countz = 0;
    }
    return vect;

}

bool diffmtrx(std::vector<std::vector<int>> v1, std::vector<std::vector<int>> v2, int dim){

    bool flag = false;

    for(int i = 0; i < dim; i++){
        for(int j = 0; j < dim; j++){

            if (v1[i][j] != v2[i][j]){
                flag = true;
            }
            if(flag){
                j = dim;
                i = dim;
            }
        }
    }
    return flag;
}

int contazeros(std::vector<std::vector<int>> vect, int dim){
    int conta = 0;
    for (int i = 0; i < dim; i++){
        for (int j = 0; j < dim; j++){
            if (vect[i][j] == 0){
                conta ++;
            }
        }
    }
    return conta;
}

void printvector(const int& dim, std::vector<std::vector<int>>& v) {

    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            std::cout << v[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void play(const std::vector<std::vector<int>> before, const std::vector<std::vector<int>> vect, int dim, int moves){

    std::vector<std::vector<int>> vect2(dim);

    int nzeros = contazeros(vect, dim);

    if (nzeros == dim*dim - 1 && moves < best ){
        best = moves;
        if(debug) std::cout << "return melhor\n";
        return;
    }

    // podemos fazer best -1 porque se chega a best -1 é porque no max apenas iguala o best
    if (moves > nplays || moves >= best -1 ){
        if(debug) std::cout << "return igual\n";
        return;
    }

    vect2=moveup(vect, dim);
    if( diffmtrx(vect, vect2, dim) && diffmtrx(before, vect2, dim)){
        if(debug){
            std::cout << "moveu up\n";
            printvector(dim, vect2);
        }
         
        play(vect,vect2,dim, moves+1);
    }


    vect2=moveright(vect, dim);
    if( diffmtrx(vect, vect2, dim) && diffmtrx(before, vect2, dim)){
        if(debug){
            std::cout << "moveu direita\n";
            printvector(dim, vect2);
        }
         
        play(vect,vect2,dim, moves+1);
    }


    vect2=movedown(vect, dim);
    if( diffmtrx(vect, vect2, dim) && diffmtrx(before, vect2, dim)){
        if(debug){
            std::cout << "moveu down\n";
            printvector(dim, vect2);
        }
         
        play(vect,vect2,dim, moves+1);
    }


    vect2=moveleft(vect, dim);
    if( diffmtrx(vect, vect2, dim) && diffmtrx(before, vect2, dim)){
        if(debug){
            std::cout << "moveu left\n";
            printvector(dim, vect2);
        }
         
        play(vect,vect2,dim, moves+1);
    }

    if(debug)std::cout << "end of this branch\n";

}

int check(const int& dim, std::vector<std::vector<int>>& v){
    int sum=0;
    int count=0;
    for(int i=0; i<dim; i++){
        for(int j=0; j<dim; j++){
            sum+= v[i][j];
            if (v[i][j]>0) count++;
        }
    }

    int m=2;
    while(m<sum){
        m *= 2;
        if(m==sum) return count;
    }

    return 0;

}

int main(){
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    int n, v, i, j, dim;
    std::vector<int> values;
    std::vector<std::vector<int>> vect;

    std::cin >> n;

    for (i = 0; i < n; i++){
        std::cin >> dim;
        std::cin >> nplays;

        for(j = 0; j < dim * dim; j++){
            std::cin >> v;
            values.push_back(v);

            if (((j + 1) % dim) == 0){
                vect.push_back(values);
                values.clear();
            }
        }

        int total_tiles= check(dim, vect);
        if(total_tiles) {

            play(vect, vect, dim, 0);
            if (best <= nplays){
                std::cout << best << '\n';
            }
            else{
                std::cout<< "no solution\n";
            }

            best = 1000;
        }
        else std::cout<< "no solution\n";
        vect.clear();
    }

    return 0;
}
