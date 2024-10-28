#include <bits/stdc++.h>
#include <pthread.h>
#include <semaphore.h>
using namespace std;

struct th {
    int id;
	int map_threads;
	int reduce_threads;
	int N;
	vector<vector<int>> l;
	char filename[20];
	int putere;
	int ready;
};

pthread_mutex_t mutex1;

void *f_reduce(void *arg)
{
	struct th *t = (struct th*) arg;
	int stop;
	while(1) {
		stop = 1;
		for (int id = 0; id < t[0].map_threads; id++){
			if (t[id].ready != 1){
				stop = 0;
				break;
			}
		}
		if (stop == 1)
			break;

	}
	pthread_mutex_lock(&mutex1);
	t[0].putere++;
	int putere = t[0].putere;
	pthread_mutex_unlock(&mutex1);
	set<int> list_reduce;
	
	for (int id = 0; id < t[0].map_threads; id++){
		for (int i : t[id].l.at(putere-2)) {
			list_reduce.insert(i);
		}
		
	}
	int nr = 0;
	for(auto& str : list_reduce)
	{
		nr++;
	}
	FILE* fp3;
	
	
	char filename[] = "out";
	char p[5];
	sprintf(p, "%d", putere);

	strcat(filename, p);
	strcat(filename, ".txt");

	fp3 = fopen(filename, "w");
	fprintf(fp3, "%d", nr);
	fclose(fp3);

	pthread_exit(NULL);
}

void *f_map(void *arg) {

	
    struct th *t = (struct th*) arg;
	FILE* fp2;
	int r;
	int nr;

	fp2 = fopen(t->filename, "r");
	
	if(fp2 == NULL)
	{
		printf("Error!");   
		exit(1);             
	}
	fscanf(fp2, "%d", &r);
	int laput;
	for (int k = 0; k < r; k++){
		fscanf(fp2, "%d", &nr);

		if (nr == 1){
			for (int p = 2; p <= t->reduce_threads + 1; p++){
				t->l[p-2].push_back(nr);
			}
		}
		else
		{
			for (int p = 2; p <= t->reduce_threads + 1; p++){
				for (int i = 2; i <= nr/2; i++){
					laput = 1;
					for (int j = 0; j < p; j++) {
						laput = laput * i;
						
					}
					
					if (laput == nr) {
						t->l[p-2].push_back(nr);
						i = nr;
						break;
					}
					else if (laput > nr){
						i = nr;
						break;
					}

				}
			}
		}
	}
	fclose(fp2);

	t->ready = 1;
	pthread_exit(NULL);
}


int main(int argc, char **argv)
{
	int map_threads = atoi(argv[1]);
	int reduce_threads = atoi(argv[2]);
	int cores = map_threads + reduce_threads;
	int N, i, r;
	char s[20];
	int stop = 0;
	FILE *fp;
	pthread_t threads[cores];

	r = pthread_mutex_init(&mutex1, NULL);
	if (r != 0) {
		printf("ERR");
		exit(0);
	}

	fp = fopen(argv[3], "r");

	if(fp == NULL)
	{
		printf("Error!");   
		exit(1);             
	}

	fscanf(fp, "%d", &N);
	r = 0;


	struct th *t = (struct th*)malloc(sizeof(struct th)*map_threads);

	int id;

	
	for (id = 0; id < map_threads; id++){ 
		fscanf(fp, "%s", s);  
		
		t[id].id = id;
		t[id].map_threads = map_threads;
		t[id].reduce_threads = reduce_threads;
		t[id].N = N;
		t[id].putere = 1;
		t[id].l.resize(reduce_threads);
		strcpy(t[id].filename, s);
		
		t[id].ready = 0;

		r = pthread_create(&threads[id], NULL, f_map, &t[id]);

		if (r) {
			printf("Eroare la crearea thread-ului %d\n", id);
			exit(-1);
		}
	}
	
	
	for (int i = 0; i < N - map_threads; i++){ 
		fscanf(fp, "%s", s);
		stop = 0;

		while (1){
			for (id = 0; id < map_threads; id++){
				if (t[id].ready == 1){
					stop = 1;
					strcpy(t[id].filename, s);
					t[id].ready = 0;
					r = pthread_create(&threads[id], NULL, f_map, &t[id]); 
					if (r) {
						printf("Eroare la crearea thread-ului %d\n", id);
						exit(-1);
					}
					break;
				}
			}
			if (stop == 1) {
				break;
			}
		}
	}

	for (id = map_threads; id < cores; id++) {
		r = pthread_create(&threads[id], NULL, f_reduce, t);
		if (r) {
			printf("Eroare la crearea thread-ului %d\n", id);
			exit(-1);
		}
	}

	for (i = 0; i < cores; i++) {
		r = pthread_join(threads[i], NULL);

		if (r) {
			printf("Eroare la asteptarea thread-ului %d\n", i);
			exit(-1);
		}
	}
	
	pthread_mutex_destroy(&mutex1);
	fclose(fp);
	
	return 0;
}
