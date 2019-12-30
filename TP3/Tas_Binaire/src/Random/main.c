#include <stdio.h>
#include "Tas.h"
#include "analyzer.h"
#include <time.h>

int main()
{
    random(time(NULL));   // Initialization, should only be called once.

    Heap *tas = createHeap();
     // Analyse du temps pris par les opérations.
  analyzer_t * time_analysis = analyzer_create();
  // Analyse du nombre de copies faites par les opérations.
  analyzer_t * copy_analysis = analyzer_create();
  // Analyse de l'espace mémoire inutilisé.
  analyzer_t * memory_analysis = analyzer_create(); 
     // Analyse du temps pris par les opérations.
  analyzer_t * time_analysis1 = analyzer_create();
  // Analyse de l'espace mémoire inutilisé.
  analyzer_t * memory_analysis1 = analyzer_create(); 
  // Mesure de la durée d'une opération.
  struct timespec before, after;
  clockid_t clk_id = CLOCK_REALTIME;

for(int i=0;i<100;i++){
     clock_gettime(clk_id, &before);
    pushNode(tas, random());
     clock_gettime(clk_id, &after);
       // Enregistrement du temps pris par l'opération
    analyzer_append(time_analysis, after.tv_nsec - before.tv_nsec);
	// Enregistrement de l'espace mémoire non-utilisé.
	printf("%d \t",tas->capacity-tas->size);
    analyzer_append(memory_analysis,tas->capacity-tas->size);
}

for(int i=0;i<100;i++){
	
     clock_gettime(clk_id, &before);
    pushNode(tas, random());
     clock_gettime(clk_id, &after);
       // Enregistrement du temps pris par l'opération
    analyzer_append(time_analysis1, after.tv_nsec - before.tv_nsec);
	// Enregistrement de l'espace mémoire non-utilisé.
	printf("%d \t",tas->capacity-tas->size);
    analyzer_append(memory_analysis1,tas->capacity-tas->size);
     clock_gettime(clk_id, &before);
    printf("Valeur retiree : %d\n", popNode(tas));
     clock_gettime(clk_id, &after);
       // Enregistrement du temps pris par l'opération
    analyzer_append(time_analysis1, after.tv_nsec - before.tv_nsec);
	// Enregistrement de l'espace mémoire non-utilisé.
	printf("%d \t",tas->capacity-tas->size);
    analyzer_append(memory_analysis1,tas->capacity-tas->size);
    
}
       
    freeHeap(tas);

  // Affichage de quelques statistiques sur l'expérience.
  printf("Push node STAT :\n ");
  printf("\t Total cost: %Lf\n", get_total_cost(time_analysis));
  printf("\t Average cost: %Lf\n", get_average_cost(time_analysis));
  printf("\t Variance: %Lf\n", get_variance(time_analysis));
  printf("\t Standard deviation: %Lf\n", get_standard_deviation(time_analysis));
// Sauvegarde les données de l'expérience.
  save_values(time_analysis, "../plots/dynamic_array_time_random.plot");
// Sauvegarde les données de l'expérience.
  save_values(memory_analysis, "../plots/dynamic_array_memory_random.plot");
// Sauvegarde les données de l'expérience.
  save_values(time_analysis1, "../plots/dynamic_array_time_randompop.plot");
// Sauvegarde les données de l'expérience.
  save_values(memory_analysis1, "../plots/dynamic_array_memory_randompop.plot");

analyzer_destroy(time_analysis);
analyzer_destroy(memory_analysis);

    return 0;
}
