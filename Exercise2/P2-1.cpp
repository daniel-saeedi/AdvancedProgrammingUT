#include <vector>

using namespace std;

struct HeightInfo {
    int height;
    int tallest_height_in_front;
};

int find_tallest_heights_in_front(const vector<HeightInfo *>& height_infos, int start_index) {
    // TODO: Implement
}

void set_tallest_heights_in_front(const vector<HeightInfo *>& height_infos) {
    find_tallest_heights_in_front(height_infos, 0);
}

vector<HeightInfo* > get_height_infos() {
    // TODO: Implement
}

void print_heights(const vector<HeightInfo *>& height_infos) {
    // TODO: Implement
}

int main() {
    vector<HeightInfo *> height_infos = get_height_infos();
    set_tallest_heights_in_front(height_infos);
    print_heights(height_infos);
    return 0;
}
