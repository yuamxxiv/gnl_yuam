/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amancheg <amancheg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 17:04:24 by amancheg          #+#    #+#             */
/*   Updated: 2026/02/06 22:50:17 by amancheg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
 // Serve per printf

int main(void)
{
    int     fd;
    char    *riga;
    int     i;

    // 1. Apro un file di prova (crealo tu dopo!)
    fd = open("test.txt", O_RDONLY);
    if (fd == -1)
    {
        printf("Errore nell'apertura del file test.txt\n");
        return (1);
    }

    i = 1;
    // 2. Ciclo infinito: chiamo GNL finché non mi dà NULL
    while (1)
    {
        riga = get_next_line(fd);
        
        if (riga == NULL) // Se è NULL, ho finito il file
            break; 

        // 3. Stampo la riga (il %d serve solo per contare le righe)
        printf("Riga %d: %s", i, riga);
        
        // 4. IMPORTANTE: Chi chiama GNL deve liberare la riga!
        free(riga);
        i++;
    }

    // 5. Chiudo il file
    close(fd);
    return (0);
}