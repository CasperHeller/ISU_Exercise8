#include <iostream>
#include "types.h"
#include "carclass.h"
#include "entryclass.h"
#include "exitclass.h"

using namespace std;

int main()
{
    cout << "PLCS started." << endl;

    EntryClass entryClass;
    ExitClass exitClass(&entryClass);
    CarClass carClass0(&entryClass, &exitClass, 1);
    CarClass carClass1(&entryClass, &exitClass, 2);
    CarClass carClass2(&entryClass, &exitClass, 3);
    CarClass carClass3(&entryClass, &exitClass, 4);
    CarClass carClass4(&entryClass, &exitClass, 5);

    osapi::Thread entryThread(&entryClass);
    osapi::Thread exitThread(&exitClass);
    osapi::Thread carThread0(&carClass0);
    osapi::Thread carThread1(&carClass1);
    osapi::Thread carThread2(&carClass2);
    osapi::Thread carThread3(&carClass3);
    osapi::Thread carThread4(&carClass4);

    entryThread.start();
    exitThread.start();
    carThread0.start();
    carThread1.start();
    carThread2.start();
    carThread3.start();
    carThread4.start();

    entryThread.join();
    exitThread.join();
    carThread0.join();
    carThread1.join();
    carThread2.join();
    carThread3.join();
    carThread4.join();

    cout << "PLCS ended." << endl;
    return EXIT_SUCCESS;
}


