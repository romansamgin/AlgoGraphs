#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

int get_pos(const std::vector<int> &numbers, int number) {
  int l = 0, r = numbers.size() - 1;  
  while (l <= r) {
   int m = (l + (r - l)) / 2;
   if (numbers[m] == number)
       return m + 1;
   else if (numbers[m] > number)
       r = m - 1;
   else 
       l = m + 1;  
    }
    return - 1;
}

int main(int argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  size_t number_count;
  cin >> number_count;
  vector<int> numbers(number_count);
  for (size_t i = 0; i < number_count; i++) {
    cin >> numbers[i];
  }

  size_t query_count;
  cin >> query_count;
  while (query_count-- > 0) {
    int number;
    cin >> number;
    cout << get_pos(numbers, number) << ' ';
  }
  cout << '\n';
}
