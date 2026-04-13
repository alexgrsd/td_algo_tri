#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include "ScopedTimer.hpp"

void print_vector(const std::vector<int> & vec){
    for (int i : vec) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

std::vector<int> generate_random_vector(size_t const size, int const max = 100) {
    std::vector<int> vec(size);
    std::generate(vec.begin(), vec.end(), [&max]() { return std::rand() % max;} );
    return vec;
}

void selection_sort(std::vector<int> & vec){
    for (int i = 0; i < vec.size(); i++){ // boucle de l'élément qu'on va swap
        int min = __INT_MAX__;
        int min_index = i;
        for (int j = i; j< vec.size(); j++){
            if (vec[j] < min){
                min = vec[j];
                min_index = j;
            }
        }
        std::swap(vec[i], vec[min_index]);
    }
}

void bubble_sort(std::vector<int> & vec){
    for (int i = 0; i < vec.size(); i++){
        for (int j = 0; j < vec.size() - 1 - i; j++){
            if (vec[j] > vec[j + 1]){
                std::swap(vec[j], vec[j + 1]);
            }
        }
    }
}

size_t quick_sort_partition(std::vector<int> & vec, size_t left, size_t right){ // partitionne le tableau et retourne l'indice du pivot
    int pivot = vec[right];
    size_t i = left;
    for (size_t j = left; j < right; j++) {
        if (vec[j] < pivot) {
            std::swap(vec[i], vec[j]);
            i++;
        }
    }
    std::swap(vec[i], vec[right]);
    return i;
}
void quick_sort(std::vector<int> & vec, size_t const left, size_t const right){
    if (left < right) {
        size_t pivot_index = quick_sort_partition(vec, left, right);

        if (pivot_index > left) {
            quick_sort(vec, left, pivot_index - 1);
        }

        quick_sort(vec, pivot_index + 1, right);
    }
}
void quick_sort(std::vector<int> & vec) {
    quick_sort(vec, 0, vec.size() - 1);
}

int iterative_search(const std::vector<int> & vec,const int number){ // iterative
    int left = 0, right = vec.size();
    while (left+1 != right){
        int middle = (left+right)/2;
        if (vec[middle] == number) return middle; // on a trouvé le chiffre
        if (vec[middle] > number) right = middle;
        if (vec[middle] < number) left = middle;
    }
    return -1;
}

int recursive_search_algo(const std::vector<int> & vec, int number, int left, int right){
    if (left > right) return -1;
    int middle = left + (right - left) / 2;
    if (vec[middle] == number) return middle;
    if (vec[middle] > number)
        return recursive_search_algo(vec, number, left, middle - 1);
    else
        return recursive_search_algo(vec, number, middle + 1, right);
}

int recursive_search(const std::vector<int> &vec, const int number){
    return recursive_search_algo(vec,number,0,vec.size());
}

int main() {
    srand(time(NULL));
    std::vector<int> vec = generate_random_vector(50);
    std::vector vec_search = generate_random_vector(50);
    std::sort(vec_search.begin(),vec_search.end());
    print_vector(vec_search);
    int search_ite = iterative_search(vec_search, 21);
    std::cout << "incide trouvé iterativement : " << search_ite << std::endl;
    int search_rec = recursive_search(vec_search, 21);
    std::cout << "incide trouvé recursivement : " << search_rec << std::endl;
    /*
    {
        std::vector<int> copy_vec = vec;
        ScopedTimer timer("Selection Sort");
        selection_sort(copy_vec);
    }
    {
        std::vector<int> copy_vec = vec;
        ScopedTimer timer("Bubble Sort");
        bubble_sort(copy_vec);
    }
    {
        std::vector<int> copy_vec = vec;
        ScopedTimer timer("Quick Sort");
        quick_sort(copy_vec);
    }
    
    {
        std::vector<int> copy_vec = vec;
        ScopedTimer timer("std::Sort");
        std::sort(copy_vec.begin(),copy_vec.end());
    }
        */
    

    return 0;
}