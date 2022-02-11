# philosophers
Multithreading in C. How do escape deadlock

<img width="1160" alt="Screen Shot 2022-02-11 at 6 53 40 PM" src="https://user-images.githubusercontent.com/77155006/153624324-8d94b231-e736-4a4c-8187-caf3118bd612.png">

Dining philosophers problem. 
One table. Number of forks == number of men.

Each philosopher has to take up two forks to eat.
So the problem is to avoid deadlock - when each man has only one fork and cannot eat.

Mandatory part - each philosopher has to be **a thread**.
Forks are implemented as **mutexes**.

Bonus part - each philosopher has to be **a proccess**.
Forks are implemented as **semaphore**.
