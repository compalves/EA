#include <vector>
#include <iostream>
#include <algorithm>
#include <math.h>

//int total = 0;
int debug = false;

struct direction {
    int up=0;
    int down=0;

}d;




int mod_abs(int a, int mod){
    return ((a%mod )+ mod )% mod;
}

int mod_add(int a, int b, int mod){
    return(mod_abs(a,mod)+ mod_abs(b,mod))%mod;
}

int mod_sub(int a, int b, int mod){
    return mod_add(a, -b, mod);
}

void print_vector(const int& n,const int& k, std::vector<std::vector<direction>>& v){
    //print the vector
    std::cout << "0\t";
    for(int i=0; i<k; i++) std::cout << i << "\t";

    std::cout << "\n\n";
    for(int i=0; i<n; i++){
        std::cout << i << "\t";
        for(int j=0; j<k; j++){
            std::cout << "u:" <<v[i][j].up << "d:" <<v[i][j].down <<"\t";
        }
        std::cout << std::endl;
    }

    std::cout <<"\nresultado: ";

}


int arch(const int& n,const int& h,const int& H){
    std::vector<std::vector<direction>> T(n);
    for(int i = 0; i < n; i++){
        T[i] = std::vector<direction>(H, direction()); //inicia todos os values a false
    }


    // meter o primeiro elemento como up, não podemos meter como down porque isso nao conta como um arco nem se pode descer obviamente
    T[0][0].up=1;
    T[0][0].down=0;

    for(int r=1; r<n; r++){
        for(int i=0; i < H-1; i++){
            if(T[r-1][i].up<0 && T[r-1][i].down>0) break;
            //check up
            if(T[r-1][i].up>0){


                for(int j=i+1; j < H-h + 1 && j < i+h ; j++){ //se j tiver espaço acima para a peça
                    // comeca em j=i+1 (1 acima do atual) e termina em j=i+h-1 (1 abaixo do tamanho da peça)
                    T[r][j].up = mod_add(T[r][j].up,T[r-1][i].up, 1000000007 );
                }
    

                for(int j=i+1 -h; j <i; j++){ //ate chegar antes de i pois em i ja ficaria do mesmo nivel
                    //comeca em j=i - (h-1) (peça mais abaixo ainda a tocar na peça anterior) e termina em i-1 (nunca fica igual à peça anterior)
                    if(j >=0) T[r][j].down = mod_add(T[r][j].down ,T[r-1][i].up, 1000000007 );
                }

            }

            //check down
            if(T[r-1][i].down>0){
                if(debug) std::cout <<"entrou em down";
                for(int j=i+1 -h; j <i; j++){ //ate chegar antes de i pois em i ja ficaria do mesmo nivel
                    //comeca em j=i - (h-1) (peça mais abaixo ainda a tocar na peça anterior) e termina em i-1 (nunca fica igual à peça anterior)
                    if(j >=0) T[r][j].down = mod_add(T[r][j].down ,T[r-1][i].down, 1000000007 );
                }

            }

        }
    }

    int total=0;
    for(int r=1; r<n; r++){
        total= mod_add(total, T[r][0].down, 1000000007 );
    }

    if(debug) print_vector(n,H,T);
    return total;

}



        /*
         if(i-h>=0){
                    if(debug) std::cout <<"\nr= " << r<<" posicao " << i << "inferior a" << h << "h, resultado: "<< i-h ;
                    for(int j=0; j < h; j++){
                    T[r][i-1-j].down +=T[r-1][i].up;
                    }

                }
        */

            /*

            //check down, quando down apenas podemos descer


            if(T[r-1][i].down>0 && T[r-1][i+1].down>0){
                for(int j=0; j < h; j++){
                    T[r][i-j].down +=T[r-1][i].down;
                }

            }
            */



/*
            if(i-h>=0 && (T[r-1][i].up>0 ||  T[r-1][i].down>0) ) {
                for(int j=0; j <h; j++){
                T[r][i-j].down +=T[r-1][i].down;
                T[r][i-j].down +=T[r-1][i].up;
                }
            }
            */

    




int main(){
    //std::ios_base::sync_with_stdio(0);
    //std::cin.tie(0);
    int x, n, h, H;
    std::vector<int> values;
    std::vector<std::vector<int>> vect;

    std::cin >> x;

    for (int i = 0; i < x; i++){
        std::cin >> n;
        std::cin >> h;
        std::cin >> H;
        int aux=arch(n,h,H);
         
        std::cout<< mod_abs(aux,1000000007)<< "\n";
      
    }

    return 0;
}