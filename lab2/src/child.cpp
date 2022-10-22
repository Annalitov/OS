#include <iostream>
#include <string>
#include <cstdlib>
#include <sys/types.h>
#include <unistd.h>
#include <fstream>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>


using namespace std;

int isNotPrime(int n)
{
    if (n < 2) {
        return 0;
    } else {
        for (int i = 2; i * i < n + 1; i++) {
            if (n % i == 0) {
                return 1;
            }
        }
    }
    return 0;
}


int main(int argc, char *argv[]){	

	string filename = argv[4];
	int fd_1[2];
	int fd_2[2];
	int flag_1 = 1;
	int flag_2 = 2;

	fd_1[0] = stoi(argv[0]);
	fd_1[1] = stoi(argv[1]);

	fd_2[0] = stoi(argv[2]);
	fd_2[1] = stoi(argv[3]);

	
	fstream f;
	f.open(filename, fstream::in | fstream::out | fstream::app);

	while(true) {
		int num_size;

		read(fd_1[0], &num_size, sizeof(int));
		char num_str[num_size];
		read(fd_1[0], &num_str, sizeof(char)*num_size);

		string result;
		for (int i = 0; i < num_size; i++) {
			result.push_back(num_str[i]);
		}

		int number;
		int number_1;
		number =  stoi(result);
		number_1 = abs(number);
		if ( number > 0 && isNotPrime(number_1) > 0 ) {
			f << result << endl;
			cout << "A number " << result << " is added to file!" << endl;

			write(fd_2[1], &flag_2, sizeof(int));

		} else {

			write(fd_2[1], &flag_1, sizeof(int));

		}

	}

	return 0;





}