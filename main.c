#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define THREADS_COUNT 4

typedef struct {
  int ThreadNum;
  int n;
  int debut;
  int fin;
  unsigned long long produit;
} Parametres;

void * CalculerProduit(void * data) {
  Parametres * mesParametres = data;
  printf("Je suis le thread %d qui calcule le produit de %d a %d\n", mesParametres->ThreadNum, mesParametres->debut, mesParametres->fin);

  int i;
  int n = mesParametres->debut;

  for (i = n; i < mesParametres->fin; i++) {
    n = n * (i + 1);
  }

  mesParametres->produit = (unsigned long long) n;

  return mesParametres;
}

int main(int argc, char * argv[]) {
  int n = 15;
  pthread_t threads[THREADS_COUNT];
  Parametres mesParametres[THREADS_COUNT] = {
      {1, n, 1, 3, 0},
      {2, n, 4, 6, 0},
      {3, n, 7, 9, 0},
      {4, n, 10, 15, 0}
  };

  printf("Calcul de la factorielle de %d\n", n);

  int i;
  for(i = 0; i < THREADS_COUNT; i++) {
    printf("Main(): en train de creer thread %d\n", i + 1);

    if (pthread_create(& threads[i], NULL, CalculerProduit, (void *) & mesParametres[i]) != 0) {
      printf("Une erreur s'est produite. Fin du programme\n");
      exit(-1);
    }
  }

  // Attendre la fin de l'execution des threads
  int j;
  for (j = 0; j < THREADS_COUNT; j++) {
    pthread_join(threads[j], NULL);
  }

  printf("Main(): Tous les threads ont terminés! Je calcule la factorielle...\n");

  unsigned long long fact = 1;

  // Calcul de la factorielle
  int k;
  for(k = 0; k < THREADS_COUNT; k++) {
    fact = fact * mesParametres[k].produit;
  }

  printf("La factorielle de %d est %llu\n", n, fact);

  return 0;
}