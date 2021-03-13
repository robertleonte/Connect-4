#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>


void login(char *message, char *message_username, char *message_password)
{
  int contor1 = 0, contor2 = 0;
  char username[256], password[256];
  memset(username, 0, strlen(username));
  int ok = 0, ok1 = 0;
  FILE *fin = fopen("username.txt", "r");

  if (fin != NULL)
  {
    while (fgets(username, 256, fin) != NULL)
    {
      username[strlen(username) - 1] = 0;
      contor1++;
      if (strcmp(message_username, username) == 0)
      {
        ok = 1;
        break;
      }
    }
  }
  fclose(fin);
  if (ok == 1)
  {
    FILE *fd = fopen("parola.txt", "r");
    if (fd != NULL)
    {
      while (fgets(password, 256, fd) != NULL)
      {
        password[strlen(password) - 1] = 0;
        contor2++;
        if (strcmp(message_password, password) == 0)
        {
          ok1 = 1;
          break;
        }
      }
    }
    fclose(fd);
  }

  if (ok == 1 && ok1 == 1)
  {
    if (contor1 == contor2)
    {
      strcpy(message, "User si parola corecte!\n");
    }
  }
  else
  {
    strcpy(message, "User-ul si/sau parola incorecte sau nu corespund!\n");
  }

}

int score(char *message_username)
{

  int score;
  char username[256];
  int ok = 0, contor = 0, contor1 = 0;
  FILE *fin = fopen("username.txt", "r");

  if (fin != NULL)
  {
    while (fgets(username, 256, fin) != NULL)
    {
      username[strlen(username) - 1] = 0;
      contor++;
      if (strcmp(message_username, username) == 0)
      {
        ok = 1;
        break;
      }
    }
  }
  printf("%d\n", ok);
  if (ok == 1)
  {
    FILE *fd = fopen("score.txt", "r");
    if (fd != NULL)
    {
      for (int i = 1; i <= contor; i++)
        fscanf(fd, "%d", &score);
    }
  }
  printf("%d\n", score);
  return score;
}

void inc_score(char *message_username)
{
  int score, scoruri[100], j = 0;
  char username[256];
  int ok = 0, contor = 0, contor1 = 0;
  FILE *fin = fopen("username.txt", "r");

  if (fin != NULL)
  {
    while (fgets(username, 256, fin) != NULL)
    {
      username[strlen(username) - 1] = 0;
      contor++;
      if (strcmp(message_username, username) == 0)
      {
        ok = 1;
        break;
      }
    }
  }
  fclose(fin);
  printf("%d\n", ok);
  if (ok == 1)
  {
    FILE *fd = fopen("score.txt", "r");
    if (fd != NULL)
    {
      while (!feof(fd))
      {
        fscanf(fd, "%d", &score);
        if (j == contor - 1)
          scoruri[j] = score + 1;
        else
        {
          scoruri[j] = score;
        }

        j++;
      }
    }
    fclose(fd);
  }
  FILE *fd = fopen("score.txt", "w");
   for (int i = 0; i < j-1; i++)
    fprintf(fd, "%d ", scoruri[i]);
    fprintf(fd, "%d", scoruri[j-1]);
    fclose(fd);
}

void user_password(char *utilizator, char *parola, char *user)
{
  int i, j, poz = 0;
  for (i = 0; i < strlen(user); i++)
    if (user[i] == '/')
      poz = i;
  for (i = 0; i < poz; i++)
    utilizator[i] = user[i];
  utilizator[i] = 0;
  for (j = 0, i = poz + 1; i < strlen(user); j++, i++)
    parola[j] = user[i];
  parola[j] = 0;
}

void generateOrder(int *ordine1, int *ordine2)
{
  srand(time(NULL));
  *ordine1 = rand() % 2;
  if (*ordine1 == 0)
    *ordine2 = 1;
  else
    *ordine2 = 0;
}

void generateColour(char *colour1, char *colour2)
{
  srand(time(NULL));
  char colours[2] = {'Y', 'R'};
  *colour1 = colours[rand() % 2];
  if (*colour1 == 'Y')
    *colour2 = 'R';
  else
    *colour2 = 'Y';
}

bool gridFull(char grid[100][100], int n, int m)
{
  bool ok = 1;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      if (grid[i][j] == '0')
        ok = 0;
  return ok;
}

bool winnerR_horizontal(char grid[100][100], int n, int m, int sequence)
{
  int k;
  bool ok, ok1;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      if (grid[i][j] == 'R')
      {
        ok = 1;
        for (k = 1; k < sequence; k++)
          if ((j + k) >= m)
            ok = 0;
        if (ok == 1)
        {
          ok1 = 1;
          for (k = 1; k < sequence; k++)
            if (grid[i][j + k] != 'R')
            {
              ok1 = 0;
            }
        }
        if (ok1 == 1)
          return 1;
      }
  return 0;
}

bool winnerR_vertical(char grid[100][100], int n, int m, int sequence)
{
  bool ok, ok1;
  int k;
  for (int j = 0; j < m; j++)
    for (int i = 0; i < n; i++)
      if (grid[i][j] == 'R')
      {
        ok = 1;
        for (k = 1; k < sequence; k++)
          if ((i + k) >= n)
            ok = 0;
        if (ok == 1)
        {
          ok1 = 1;
          for (k = 1; k < sequence; k++)
            if (grid[i + k][j] != 'R')
            {
              ok1 = 0;
            }
        }
        if (ok1 == 1)
          return 1;
      }

  return 0;
}

bool winnerR_maindiag(char grid[100][100], int n, int m, int sequence)
{
  bool ok, ok1;
  int k;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      if (grid[i][j] == 'R')
      {
        ok = 1;
        for (k = 1; k < sequence; k++)
          if ((i + k) >= n || (j + k) >= m)
            ok = 0;
        if (ok == 1)
        {
          ok1 = 1;
          for (k = 1; k < sequence; k++)
            if (grid[i + k][j + k] != 'R')
              ok1 = 0;
        }
        if (ok1 == 1)
          return 1;
      }

  return 0;
}

bool winnerR_secdiag(char grid[100][100], int n, int m, int sequence)
{
  bool ok, ok1;
  int k = 1;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      if (grid[i][j] == 'R')
      {
        ok = 1;
        for (k = 1; k < sequence; k++)
          if ((i + k) >= n || (j - k) < 0)
            ok = 0;
        if (ok == 1)
        {
          ok1 = 1;
          for (k = 1; k < sequence; k++)
            if (grid[i + k][j - k] != 'R')
              ok1 = 0;
        }
        if (ok1 == 1)
          return 1;
      }

  return 0;
}

bool winnerR(char grid[100][100], int n, int m, int sequence)
{
  return winnerR_horizontal(grid, n, m, sequence) || winnerR_vertical(grid, n, m, sequence) || winnerR_maindiag(grid, n, m, sequence) || winnerR_secdiag(grid, n, m, sequence);
}

bool winnerY_horizontal(char grid[100][100], int n, int m, int sequence)
{
  int k;
  bool ok, ok1;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      if (grid[i][j] == 'Y')
      {
        ok = 1;
        for (k = 1; k < sequence; k++)
          if ((j + k) >= m)
            ok = 0;
        if (ok == 1)
        {
          ok1 = 1;
          for (k = 1; k < sequence; k++)
            if (grid[i][j + k] != 'Y')
            {
              ok1 = 0;
            }
        }
        if (ok1 == 1)
          return 1;
      }
  return 0;
}

bool winnerY_vertical(char grid[100][100], int n, int m, int sequence)
{
  bool ok, ok1;
  int k;
  for (int j = 0; j < m; j++)
    for (int i = 0; i < n; i++)
      if (grid[i][j] == 'Y')
      {
        ok = 1;
        for (k = 1; k < sequence; k++)
          if ((i + k) >= n)
            ok = 0;
        if (ok == 1)
        {
          ok1 = 1;
          for (k = 1; k < sequence; k++)
            if (grid[i + k][j] != 'Y')
            {
              ok1 = 0;
            }
        }
        if (ok1 == 1)
          return 1;
      }

  return 0;
}

bool winnerY_maindiag(char grid[100][100], int n, int m, int sequence)
{
  bool ok, ok1;
  int k;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      if (grid[i][j] == 'Y')
      {
        ok = 1;
        for (k = 1; k < sequence; k++)
          if ((i + k) >= n || (j + k) >= m)
            ok = 0;
        if (ok == 1)
        {
          ok1 = 1;
          for (k = 1; k < sequence; k++)
            if (grid[i + k][j + k] != 'Y')
              ok1 = 0;
        }
        if (ok1 == 1)
          return 1;
      }

  return 0;
}

bool winnerY_secdiag(char grid[100][100], int n, int m, int sequence)
{
  bool ok, ok1;
  int k = 1;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      if (grid[i][j] == 'Y')
      {
        ok = 1;
        for (k = 1; k < sequence; k++)
          if ((i + k) >= n || (j - k) < 0)
            ok = 0;
        if (ok == 1)
        {
          ok1 = 1;
          for (k = 1; k < sequence; k++)
            if (grid[i + k][j - k] != 'Y')
              ok1 = 0;
        }
        if (ok1 == 1)
          return 1;
      }

  return 0;
}
bool winnerY(char grid[100][100], int n, int m, int sequence)
{
  return winnerY_horizontal(grid, n, m, sequence) || winnerY_vertical(grid, n, m, sequence) || winnerY_maindiag(grid, n, m, sequence) || winnerY_secdiag(grid, n, m, sequence);
}

bool gameFinished(char grid[100][100], int n, int m, int sequence)
{
  return winnerR(grid, n, m, sequence) || winnerY(grid, n, m, sequence);
}

void moveClient(char culoare, int move, char grid[100][100], int n)
{
  int j = move - 1;
  for (int i = n - 1; i >= 0; i--)
    if (grid[i][j] == '0')
    {
      grid[i][j] = culoare;
      break;
    }
}

void displayGrid(int client1, int client2, char grid[100][100])
{
  write(client1, grid, 100 * 100 * sizeof(char));
  write(client2, grid, 100 * 100 * sizeof(char));
}
#define PORT 2728
extern int errno; 

int main()
{
  struct sockaddr_in server; 
  struct sockaddr_in client_nr1;
  struct sockaddr_in client_nr2;
  int sd, linii, coloane, secventa;
  int client1, client2, nr_clients = 0;
  int clients[100];
  int optval = 1; 

  if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
  {
    perror("[server] Eroare la socket().\n");
    return errno;
  }

  setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

  bzero(&server, sizeof(server));

  server.sin_family = AF_INET;
  server.sin_addr.s_addr = htonl(INADDR_ANY);
  server.sin_port = htons(PORT);

  if (bind(sd, (struct sockaddr *)&server, sizeof(struct sockaddr)) == -1)
  {
    perror("[server] Eroare la bind().\n");
    return errno;
  }

  if (listen(sd, 5) == -1)
  {
    perror("[server] Eroare la listen().\n");
    return errno;
  }

  while (1)
  {
    printf("[server]Asteptam la portul %d...\n", PORT);
    fflush(stdout);
    int lungime1 = sizeof(client_nr1);
    int lungime2 = sizeof(client_nr2);
    client1 = accept(sd, (struct sockaddr *)&client_nr1, &lungime1);
    printf("[server] S-a conectat primul client.\n");
    char message[256], user[256], utilizator[256], parola[256], user1[256], utilizator1[256], parola1[256], welcome[256];

    do
    {
      write(client1, "[server] Login (user/parola): ", 31);
      if (read(client1, user, 256) < 0)
      {
        perror("[server] Eroare la read user si parola de la client");
        return errno;
      }
      user_password(utilizator, parola, user);
      printf("%s %s\n", utilizator, parola);
      login(message, utilizator, parola);
      write(client1, message, 256);
    } while (strcmp(message, "User si parola corecte!\n"));
    strcpy(utilizator1, utilizator);
    strcpy(parola1, parola);
    sprintf(welcome,"Welcome, %s! Scorul tau este %d\n",utilizator, score(utilizator));
    write(client1, welcome, sizeof(welcome));
    client2 = accept(sd, (struct sockaddr *)&client_nr2, &lungime2);
    printf("[server] S-a conectat si al doilea client.\n");

    do
    {
      write(client2, "[server] Login (user/parola): ", 31);
      if (read(client2, user, 256) < 0)
      {
        perror("[server] Eroare la read user si parola de la client");
        return errno;
      }
      user_password(utilizator, parola, user);
      printf("%s %s\n", utilizator, parola);
      login(message, utilizator, parola);
      write(client2, message, 256);
    } while (strcmp(message, "User si parola corecte!\n"));
    sprintf(welcome,"Welcome, %s! Scorul tau este %d\n",utilizator, score(utilizator));
    write(client2, welcome, sizeof(welcome));
    write(client2, "[server] Ai venit al doilea, vei juca ce alege primul!\n", 47);
    if (client1 < 0)
    {
      perror("[server] Eroare la accept() primul client.\n");
      continue;
    }
    if (client2 < 0)
    {
      perror("[server] Eroare la accept() al doilea client.\n");
      continue;
    }
    write(client1, "[server] Primul venit, primul servit! Alege dimensiunile tablei de joc si secventa: ", 85);
    read(client1, &linii, sizeof(int));
    read(client1, &coloane, sizeof(int));
    read(client1, &secventa, sizeof(int));
    write(client2, &linii, sizeof(int));
    write(client2, &coloane, sizeof(int));
    write(client2, &secventa, sizeof(int));
    printf("%d %d %d", linii, coloane, secventa);
    printf("[server]Am acceptat o pereche de 2 jucatori, se va ocupa procesul fiu de ei.\n");
    nr_clients += 2;
    clients[nr_clients - 2] = client1;
    clients[nr_clients - 1] = client2;
    client1 = client2 = 0;

    switch (fork())
    {
    case -1:
      perror("[server]Eroare la fork().\n");
      return errno;
    case 0:
    { 
      int counter = nr_clients;
      int rand, move = -1, contor = 0;
      int ordine1, ordine2;
      char culoare1, culoare2;
      char gameTable[100][100];
      for (int i = 0; i < 100; i++)
        for (int j = 0; j < 100; j++)
          gameTable[i][j] = '0';
      generateOrder(&ordine1, &ordine2);
      ordine1 += 1;
      ordine2 += 1;
      generateColour(&culoare1, &culoare2);
      printf("Ordine1 este %d, ordine2 este %d", ordine1, ordine2);
      write(clients[counter - 1], &ordine1, sizeof(int));
      write(clients[counter - 1], &culoare1, sizeof(char));
      write(clients[counter - 2], &ordine2, sizeof(int));
      write(clients[counter - 2], &culoare2, sizeof(char));
      rand = 1;
      while (gameFinished(gameTable, linii, coloane, secventa) == 0 && gridFull(gameTable, linii, coloane) == 0)
      {
        contor++;
        write(clients[counter - 1], &rand, sizeof(int));
        write(clients[counter - 2], &rand, sizeof(int));
        if (ordine1 == 1)
        {
          if (rand == 1)
          {
            printf("[fiu]Este randul clientului 1. Astept sa citesc.\n");
            move = -1;
            char msg[256];
            sprintf(msg, "Your turn (choice between 1-%d): ", coloane);
            if (write(clients[counter - 1], msg, sizeof(msg)) < 0)
            {
              perror("[client]Eroare la write() spre fiu\n");
              return errno;
            }
            read(clients[counter - 1], &move, sizeof(int));
            moveClient(culoare1, move, gameTable, linii);
            displayGrid(clients[counter - 1], clients[counter - 2], gameTable);
            rand = 2;
          }
          else if (rand == 2)
          {
            printf("[fiu]Este randul clientului 2. Astept sa citesc.\n");
            move = -1;
            char msg[256];
            sprintf(msg, "Your turn (choice between 1-%d): ", coloane);
            if (write(clients[counter - 2], msg, sizeof(msg)) < 0)
            {
              perror("[client]Eroare la write() spre fiu\n");
              return errno;
            }
            read(clients[counter - 2], &move, sizeof(int));
            moveClient(culoare2, move, gameTable, linii);
            displayGrid(clients[counter - 1], clients[counter - 2], gameTable);
            rand = 1;
          }
        }
        else
        {
          if (rand == 1)
          {
            printf("[fiu]Este randul clientului 1. Astept sa citesc.\n");
            move = -1;
            char msg[256];
            sprintf(msg, "Your turn (choice between 1-%d): ", coloane);
            if (write(clients[counter - 2], msg, sizeof(msg)) < 0)
            {
              perror("[client]Eroare la write() spre fiu\n");
              return errno;
            }
            read(clients[counter - 2], &move, sizeof(int));
            moveClient(culoare2, move, gameTable, linii);
            displayGrid(clients[counter - 1], clients[counter - 2], gameTable);
            rand = 2;
          }
          else if (rand == 2)
          {
            printf("[fiu]Este randul clientului 2. Astept sa citesc.\n");
            move = -1;
            char msg[256];
            sprintf(msg, "Your turn (choice between 1-%d): ", coloane);
            if (write(clients[counter - 1], msg, sizeof(msg)) < 0)
            {
              perror("[client]Eroare la write() spre fiu\n");
              return errno;
            }
            read(clients[counter - 1], &move, sizeof(int));
            moveClient(culoare1, move, gameTable, linii);
            displayGrid(clients[counter - 1], clients[counter - 2], gameTable);
            rand = 1;
          }
        }
      }
      if (winnerR(gameTable, linii, coloane, secventa) == 1)
      {
        if (culoare1 == 'R')
        {
          write(clients[counter - 1], "Felicitari! Ai castigat!", 25);
          write(clients[counter - 2], "Imi pare rau! Ai pierdut!", 26);
          inc_score(utilizator);
        }
        else
        {
          write(clients[counter - 2], "Felicitari! Ai castigat!", 25);
          write(clients[counter - 1], "Imi pare rau! Ai pierdut!", 26);
          inc_score(utilizator1);
        }
      }
      if (winnerY(gameTable, linii, coloane, secventa) == 1)
      {
        if (culoare1 == 'Y')
        {
          write(clients[counter - 1], "Felicitari! Ai castigat!", 25);
          write(clients[counter - 2], "Imi pare rau! Ai pierdut!", 26);
          inc_score(utilizator);
        }
        else
        {
          write(clients[counter - 2], "Felicitari! Ai castigat!", 25);
          write(clients[counter - 1], "Imi pare rau! Ai pierdut!", 26);
          inc_score(utilizator1);
        }
      }
      if (gridFull(gameTable, linii, coloane) == 1)
      {
        write(clients[counter - 1], "Tabla de joc  plina! Remiza!", 29);
        write(clients[counter - 2], "Tabla de joc  plina! Remiza!", 29);
      }

      close(clients[nr_clients - 2]);
      close(clients[nr_clients - 1]);
      exit(99);
    } 
    break;
    } 
    close(clients[nr_clients - 2]);
    close(clients[nr_clients - 1]);
    printf("[server] - accept conexiuni in continuare\n");
  }
}
