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

int main(){

	fstream f;

	string filename;
	cout<<"Enter a filename: "<<endl;

	cin >> filename;


	int fd_1[2];
	int fd_2[2];
	int pipe_1[2];
	int pipe_2[2];

	if (pipe(pipe_1) == -1){
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	if (pipe(pipe_2) == -1){
		perror("pipe");
		exit(EXIT_FAILURE);
	}


	string num;

	pid_t id = fork();

	if (id == -1){

		perror("fork");
		exit(EXIT_FAILURE);
	} else if (id == 0) {

		fd_1[0] = pipe_1[0];
		fd_1[1] = pipe_1[1];
		fd_2[0] = pipe_2[0];
		fd_2[1] = pipe_2[1];
		execl("./child", to_string(fd_1[0]).c_str(), to_string(fd_1[1]).c_str(), to_string(fd_2[0]).c_str(), to_string(fd_2[1]).c_str(), filename.c_str(), NULL);

	} else {

		cout << "Enter a number: " << endl;
		cin >> num;
		int s_size = num.size();
		char str_array[s_size];
		for (int k = 0; k < s_size; ++k) {
			str_array[k] = num[k];
		}
		write(pipe_1[1], &s_size, sizeof(int));
		write(pipe_1[1], str_array, sizeof(char)*s_size);
		int flag_0;
		read(pipe_2[0], &flag_0, sizeof(int));
		if (flag_0 == 1) {
			cout << "The number is prime or negative" << endl;
		}
	}

	close(pipe_1[0]);
	close(pipe_1[1]);
	close(pipe_2[0]);
	close(pipe_2[1]);

	return 0;

}
