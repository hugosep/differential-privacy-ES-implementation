#include <stdio.h>
#include <librdf.h>
#include <rasqal.h>
#include <stdbool.h>

bool readInput(const char * argv[])
{
    char *inputFileName = (char*)argv[1];

    FILE *fp;
    char buff[255];
    fp = fopen(inputFileName, "r+");
    fgets(buff, 255, fp);
    fclose(fp);
    
    return true;
}

int main(int argc, const char* argv[]) {

    //readInput(argc, argv);
    rasqal_world *world = rasqal_new_world();
    rasqal_world_open(world);
    if(!world) {
        printf("World is NULL");
    }
    rasqal_query_results *results;
    raptor_world* rptr_world = rasqal_world_get_raptor(world);
    const char* query_string = "PREFIX rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> \
PREFIX foaf: <http://xmlns.com/foaf/0.1/> \
SELECT ?nick, ?name \
WHERE { ?x rdf:type foaf:Person . ?x foaf:nick ?nick . ?x foaf:name ?name }";
    raptor_uri *base_uri=raptor_new_uri(rptr_world, (const unsigned char*)"http://www.dajobe.org/foaf.rdf");
    if(!base_uri) {
        printf("World is NULL");
    }

    rasqal_query *rq = rasqal_new_query(world, NULL, (const unsigned char*)"http://www.dajobe.org/foaf.rdf");
    if(!rq){
        printf("is NULL\n");
    }
    rasqal_query_prepare(rq, (const unsigned char*)query_string, base_uri);
    results = rasqal_query_execute(rq);
    if(results == NULL){
        printf("is NULL");
    }
    printf("a=%d\n", rasqal_query_results_finished(results));

    if(rasqal_query_results_finished(results)) {
        int i = rasqal_query_results_get_bindings_count(results);
        printf("i=%d count=%d\n", i, rasqal_query_results_get_bindings_count(results));

        for(int i = 0; i < rasqal_query_results_get_bindings_count(results); i++) {   
            const unsigned char *name=rasqal_query_results_get_binding_name(results,i);
            printf("a %s\n", name);
            //rasqal_literal *value=rasqal_query_results_get_binding_value(results,i);
        }  
        rasqal_query_results_next(results);
    }
    rasqal_free_query_results(results);
    rasqal_free_query(rq);
    rasqal_free_world(world);
}