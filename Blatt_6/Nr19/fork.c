#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
	int cnt = 0;
	int fork_pid = getppid();
	printf("cnt = %d, fork_pid = %5d, my_pid = %5d\n", cnt, fork_pid, getpid()); // 1 ausgabe mit cnt 0 (original prozess)
	fork_pid = fork();
	cnt++;
	printf("cnt = %d, fork_pid = %5d, my_pid = %5d\n", cnt, fork_pid, getpid()); //2 ausgaben mit cnt 2 (original + child_org_1)
	fork_pid = fork();
	cnt++;
	printf("cnt = %d, fork_pid = %5d, my_pid = %5d\n", cnt, fork_pid, getpid()); //4 ausgaben mit cnt 3 (original + child_org_1 + child_org_2 + child_org_1_child)
}

// die pids ändern sich, da sie vom Betriebssystem vergeben werden und unteranderem von der anzahl der anderen laufenden prozessen abhängen.
//die reihenfolge ändert sich auch, da der schedular frei festlegt wann welcher prozess rechenzeit bekommt