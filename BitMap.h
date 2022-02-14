#include <iostream>
#include <vector>

using namespace std;

class BitMap {
public:
  BitMap(int num): bits(1 + num / 32, 0)
  {

  }

  void Set(uint32_t num) 
  {
    bits[num >> 5] |= (1 << (num % 32));
  }

  void Reset(uint32_t num) 
  {
    bits[num >> 5] &= ~(1 << (num % 32));
  }

  bool Exist(uint32_t num) 
  {
    if (bits[num >> 5] & (1 << (num % 32))) {
      return true;
    }
    return false;
  }

  void Show() 
  {  
    int n = bits.size();
    for (int i = 0; i < n; i++){
      for (int j = 0; j < 32; j++) {
        if (bits[i] & (1 << j)) {
          cout << i * 31 + j<< endl;
        }
      }
    }
  }
private:
  vector<uint32_t>bits;
};

int main()
{
  BitMap bits(10);
  vector<int>nums = {7, 5, 6, 8, 9};
  for (auto &i : nums) {
    bits.Set(i);
  }
  bits.Show();
  return 0;
}