#include <iostream>
#include <cstring>
using namespace std;

int bsdChecksumFromstr(char *input) /* The file handle for input data */
{
    int checksum = 0;             /* The checksum mod 2^16. */

    for (int x=0;x<strlen(input);x++) {
        checksum = (checksum >> 1) + ((checksum & 1) << 15);
        checksum += input[x];
        checksum &= 0xffff;       /* Keep it within bounds. */
    }
    return checksum;
}

char in[1000];
int n;

int main() {
	scanf("%d",&n);
	for(int x=0;x<n;x++)
	{
		scanf("%s",in);
	printf("%d\n",bsdChecksumFromstr(in));
	}
	
	return 0;
}