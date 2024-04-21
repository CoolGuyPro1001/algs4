#include <StdRandom.h>
#include <Merge.h>

int main()
{
   std::vector<int> array(10000000);
   for (int i = 0; i < array.size(); i++)
   {
      array[i] = StdRandom::uniformInt(0, 10);
   }

   Merge::sort(array);
}