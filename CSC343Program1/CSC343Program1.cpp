#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;


struct ProcessInfo {
    int processId;
    int startAddress;
    int processSize;   // measured in MB
    int unusedSpace;   
};

void userMemoryAllocation(ProcessInfo processes[], int& processCount, int memory[], int& memoryIndex) {
    const int TOTAL_PAGES = 100;
    const int PAGE_SIZE = 160;   // each page is 160 MB
    static int currentStartAddress = 2000;

    while (memoryIndex < TOTAL_PAGES) {    // random number between 1 and 30
        int randomChunks = rand() % 30 + 1;  
        int processSize = randomChunks * 80; 
        int pagesNeeded = (processSize + PAGE_SIZE - 1) / PAGE_SIZE;

        if (memoryIndex + pagesNeeded > TOTAL_PAGES) {
            break;
        }

        for (int i = 0; i < pagesNeeded; i++) {   // mark the pages with the process id
            memory[memoryIndex++] = processCount + 1; 
        }

        int allocatedMemory = pagesNeeded * PAGE_SIZE;
        int unusedSpace = allocatedMemory - processSize;

        processes[processCount] = { processCount + 1, currentStartAddress, processSize, unusedSpace };
        currentStartAddress += allocatedMemory;
        processCount++;  // increment the process counter
    }
}
int main() {
    srand(static_cast<unsigned int>(time(0)));

    const int TOTAL_PAGES = 100; //max pages is 100
    int memory[TOTAL_PAGES] = { 0 };

    ProcessInfo processes[100];

    int processCount = 0;  // number of processes 
    int memoryIndex = 0;   // current index in memory 

    userMemoryAllocation(processes, processCount, memory, memoryIndex);

    cout << left << setw(15) << "Process Id"
        << left << setw(25) << "Starting Memory Address"        // printing summary header.
        << left << setw(30) << "Size of the Process MB"
        << left << setw(20) << "Unused Space MB" << endl;

    for (int i = 0; i < processCount; i++) {
        cout << left << setw(15) << processes[i].processId
            << left << setw(25) << processes[i].startAddress
            << left << setw(30) << processes[i].processSize
            << left << setw(20) << processes[i].unusedSpace << endl;
    }
    system("pause");
    return 0;
}