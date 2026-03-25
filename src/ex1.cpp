#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <vector>

void print_vector(const std::vector<int> & vec){
    for (int i : vec) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
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
        quick_sort(vec, left, pivot_index - 1);
        quick_sort(vec, pivot_index + 1, right);
    }
}
void quick_sort(std::vector<int> & vec) {
    quick_sort(vec, 0, vec.size() - 1);
}

int main() {
    std::vector<int> tab_selection = {5, 2, 9, 1, 5, 6};
    std::cout << "Avant le tri : ";
    print_vector(tab_selection);
    selection_sort(tab_selection);
    std::cout << "Après le tri : ";
    print_vector(tab_selection);

    std::vector<int> tab_bubble = {5, 2, 9, 1, 5, 6};
    std::cout << "Avant le tri : ";
    print_vector(tab_bubble);
    bubble_sort(tab_bubble);
    std::cout << "Après le tri : ";
    print_vector(tab_bubble);

    std::vector<int> tab_quick = {};
    for (int i = 0; i < 10; i++) {
        tab_quick.push_back(rand() % 100);
    }
    std::cout << "Avant le tri : ";
    print_vector(tab_quick);
    quick_sort(tab_quick);
    std::cout << "Après le tri : ";
    print_vector(tab_quick);

    return 0;
}