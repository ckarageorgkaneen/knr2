/* Define a macro swap(t,x,y) that interchanges two arguments of type t . (Block structure will help.) */
#include <stdio.h>
#include <assert.h>

#define swap(t, x, y) do{t z=x;x=y;y=z;}while(0)

void main()
{
	int x = 4;
	int y = 29;
	swap(int, x, y);
	assert(x == 29 && y == 4);
}
