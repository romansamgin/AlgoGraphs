#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

class Fibonacci {
 public:      
  static int get_remainder(long long n, int m) {
    assert(n >= 1);
    assert(m >= 2);
      
    int cur = 1;
    int prev = 0;
    int period = 0;

    vector<int> p;
    bool is_period = false;
    for(int i = 0; i < 6*m; ++i){          
        if (prev == 0 && cur == 1 && period > 0){
            is_period = true;
            break;
        }
        p.push_back(prev);
        cur = prev % m + cur % m;
        prev = cur - prev;
        period++;
    }
        
    if (is_period == false){
        return n % m;
    }   
    return p[n % p.size()];
  }
};

int main(void) {
  long long n;
  int m;
  std::cin >> n >> m;
  std::cout << Fibonacci::get_remainder(n, m) << std::endl;
  return 0;
}