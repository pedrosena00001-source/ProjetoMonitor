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
            TotalAchado = 1;
        } else if (sscanf(buff_memory, "MemAvailable: %lu kB", &MemAvailable) == 1){
            DisponivelAchado = 1;
    }
        if (TotalAchado && DisponivelAchado == 1){
            break;
        }
    }
    //Tratamento de Erros Memory Total
    if (TotalAchado != 1){
        fprintf(stderr, "Error Ao Carregar Memory Total\n");
        fclose(memory);
        fclose(load);
        return 1;
    }

    //Tratamento de Erros Memory Avaiable
    if (DisponivelAchado != 1){
        fprintf(stderr, "Error Ao Carregar Memory Avaiable\n");
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
        break;
    }
  }
}
        if (LoadAchado != 1) {
            fprintf(stderr, "Erro Ao Carregar O Load\n");
            fclose(memory);
            fclose(load);
            return 1;
        }

        //Print de Todas As Informações
         printf("{\"mem_total_kb\": %lu, " "\"mem_available_lb\": %lu, " "\"load1\": %.2f}\n", MemTotal, MemAvailable, Load);

        fclose(memory);
        fclose(load);
        return 0;
}
