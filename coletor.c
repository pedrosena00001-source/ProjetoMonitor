#include <stdio.h>

int main () {
    FILE *memory = fopen("/proc/meminfo", "r");
    FILE *load = fopen("/proc/loadavg", "r");
    char buff_memory[200];
    char buff_load[200];
    unsigned long MemTotal;
    unsigned long MemAvailable;
    float Load;
    int TotalAchado= 0;
    int DisponivelAchado= 0;
    int LoadAchado = 0;

    if(memory == NULL){
        perror("Não Foi Possível Abrir O Arquivo Memory");
        return 1;
    }

    if(load == NULL){
        perror("Não Foi Possível Abrir O Arquivo Load");
        return 1;
    }

    //MEMORY
    while (fgets(buff_memory, sizeof(buff_memory), memory) != NULL) {
        if (sscanf(buff_memory, "MemTotal: %lu kB", &MemTotal) == 1){
            printf("MemTotal: %lu kB\n", MemTotal);
            TotalAchado = 1;
        } else if (sscanf(buff_memory, "MemAvailable: %lu kB", &MemAvailable) == 1){
            printf("MemAvailable: %lu kB\n", MemAvailable);
            DisponivelAchado = 1;
    }
        if (TotalAchado && DisponivelAchado == 1){
            break;
        }
    }
    //Tratamento de Erros Memory
    if (TotalAchado != 1){
        fprintf(stderr, "Error Ao Carregar Memory Total");
        fclose(memory);
        fclose(load);
        return 1;
    }

    if (DisponivelAchado != 1){
        fprintf(stderr, "Error Ao Carregar Memory Avaiable");
        fclose(memory);
        fclose(load);
        return 1;
    }

    //LOAD
    while (fgets(buff_load, sizeof(buff_load), load) != NULL) {
        if(sscanf(buff_load, "%f", &Load) == 1){
            LoadAchado = 1;
        if (LoadAchado == 1){
            //Verificar Somente a Primeira Variavel que corresponde com o Float
            printf("Load: %.2f\n", Load);
            break;
        }
    }
}
        if (LoadAchado != 1) {
            fprintf(stderr, "Erro Ao Carregar O Load");
            fclose(memory);
            fclose(load);
            return 1;
        }

        fclose(memory);
        fclose(load);
        return 0;
}
