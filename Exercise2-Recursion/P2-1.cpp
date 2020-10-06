#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct HeightInfo {
    int height;
    int tallest_height_in_front;
};

int find_tallest_heights_in_front(const vector<HeightInfo *>& height_infos, int start_index) {
    int tallest_hight = -1;
    //Base Case
    if(start_index >= height_infos.size() -1) return tallest_hight;

    for(int i = start_index+1;i < height_infos.size();i++)
    {
        if(height_infos[i]->height >= tallest_hight)
        {
            tallest_hight = height_infos[i]->height;
        }
    }

    height_infos[start_index]->tallest_height_in_front = tallest_hight;

    //Recursive Case

    return find_tallest_heights_in_front(height_infos,start_index+1);
}

void set_tallest_heights_in_front(const vector<HeightInfo *>& height_infos) {
    find_tallest_heights_in_front(height_infos, 0);
}

vector<HeightInfo* > get_height_infos() {
    string heights_with_spaces;
    getline(cin,heights_with_spaces);

    int index = 0;

    vector<HeightInfo* > heights;

    HeightInfo *temp;
    while(index <= heights_with_spaces.length()-1)
    {
        temp = new HeightInfo;

        temp->height = stoi(heights_with_spaces.substr(index,1));
        temp->tallest_height_in_front = -1;
        heights.push_back(temp);
        index += 2;
    }
    return heights;
}

void print_heights(const vector<HeightInfo *>& height_infos) {
    for(int i = 0; i < height_infos.size();i++)
    {
        cout << height_infos[i]->tallest_height_in_front;
        if(i != height_infos.size()-1)cout << " ";
    }
    cout << endl;
}

int main() {
    vector<HeightInfo *> height_infos =  get_height_infos();
    set_tallest_heights_in_front(height_infos);
    print_heights(height_infos);
    return 0;
}
