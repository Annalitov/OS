#include <iostream>
#include <string>
#include <sys/types.h>
#include <fcntl.h>           
#include <sys/stat.h>        
#include <semaphore.h>
#include <unistd.h>
#include <fstream>
#include <errno.h>
#include <sys/mman.h> 
#include <cstdio>

using namespace std;
int flag_ = 0;

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

int child(string filename, char *mapped, string sem_file) {
    int count = 1;
    fstream file_1;
    file_1.open(filename, fstream::in | fstream::out | fstream::app);
    sem_t *semaphore = sem_open(sem_file.c_str(), 1); 

    while (true) {

        if (sem_wait(semaphore) == -1) {
            perror("Semaphore error");
            exit(EXIT_FAILURE);
        }

        if (mapped[count] == '!') {
            break;
        }

        int str_size = (int)mapped[count];

        int start = count;
        char mas[str_size];
        int i = 0;

        for(; count < start + str_size; count++) {
            mas[i] = mapped[count + 1];
            i += 1;
        }
        string result;

        for(int i = 0; i < str_size; i++) {
                result.push_back(mas[i]);
        }
        int number;
        int number_1;
        number =  stoi(result);
        number_1 = abs(number);
        if ( number > 0 && isNotPrime(number_1) > 0 ) {
            file_1 << result << endl;
            file_1 << endl;
            cout << "A number " << result << " is added to file!" << endl;
        } else {
            mapped[0] = 1;
        }
        sem_post(semaphore);
        count++;

        }
    return 0;
}

int main () 
{
    string filename;
    int flag;
    int strings_size;
    string sem_file = "a.semaphore";

    cout << "Enter a filename: ";
    cin >> filename;
    cout << endl;

    cout<<"Enter number of operations: ";
    int amount;
    cin >> amount;
    cout << endl;

    const int mapsize = amount*256;

    int flaccess = S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH;

    sem_t *semaphore = sem_open(sem_file.c_str(), O_CREAT, flaccess, 0);

    if (semaphore == SEM_FAILED) {
        perror("Semaphore error");
        exit(EXIT_FAILURE);
    }

    char *mapped = (char *)mmap(0, mapsize, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    pid_t id = fork();

    if (id == -1){

        perror("fork");
        cout << "1"; 
        exit(EXIT_FAILURE);
    } 

    else if (id == 0) {

        child(filename, mapped, sem_file);
        return 0;

    } 

    if (id != 0) {
        string string_r;
        int start = 1;
        mapped[0] = 0;
        for (int i = 0; i < amount + 1; ++i) {

            if (i == amount) {
                mapped[start] = '!';
                if (mapped[0] == 1) {
                    cout << "The number is prime or negative" << endl;
                    mapped[0] = 0;
                }
                sem_post(semaphore);
                break;
            }
            
            cin >> string_r;
            for (int j = 0; j < string_r.size() + 1; j++){
                if (j == 0) {
                    mapped[start] = (char)string_r.size();
                    continue;
                }
                mapped[start + j] = string_r[j - 1];
            }
            sem_post(semaphore);
            sem_wait(semaphore);
            start += string_r.size() + 1;
            if (mapped[0] == 1) {
                cout << "The number is prime or negative" << endl;
                mapped[0] = 0;
            }
        }
    }
    munmap(mapped, mapsize);
    sem_close(semaphore);
    sem_unlink(sem_file.c_str());

    return 0;
}
