#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> get_tallest_heights_in_front(const vector<int>& heights, int start_index) 
{
    
    vector<int> tallest_hight_vector;
    tallest_hight_vector.push_back(-1);
    //Base Case
    if(start_index >= heights.size() -1) return tallest_hight_vector;

    for(int i = start_index+1;i < heights.size();i++)
    {
        if(heights[i] >= tallest_hight_vector[0])
        {
            tallest_hight_vector[0] = heights[i];
        }
    }

    //Recursive Case
    vector<int> test = get_tallest_heights_in_front(heights,start_index+1);

    vector<int> results;
    //contatenating two vectors
    results.reserve( tallest_hight_vector.size() + test.size() ); // preallocate memory
    results.insert( results.end(), tallest_hight_vector.begin(), tallest_hight_vector.end() );
    results.insert( results.end(), test.begin(), test.end() );

    return results;
}

vector<int> get_tallest_heights_in_front(const vector<int>& heights) 
{
    return get_tallest_heights_in_front(heights, 0);
}

vector<int> get_heights() 
{
    string heights_with_spaces;
    getline(cin,heights_with_spaces);

    int index = 0;

    vector<int > heights;

    while(index <= heights_with_spaces.length()-1)
    {
        heights.push_back(stoi(heights_with_spaces.substr(index,1)));
        index += 2;
    }

    return heights;
}

void print_heights(const vector<int>& heights) 
{
    for(int i = 0;i < heights.size();i++)
    {
        cout << heights[i];
        if(i != heights.size()-1)cout << " ";
    }

    cout << endl;
}

int main() 
{
    vector<int> heights = get_heights();

    vector<int> tallest_heights_in_front = get_tallest_heights_in_front(heights);
   
    print_heights(tallest_heights_in_front);
    return 0;
}
