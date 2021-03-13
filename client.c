#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdbool.h>

bool slash(char *sir)
{
  int i;
  for (i = 0; i < strlen(sir); i++)
    if (sir[i] == '/')
      return 1;

  return 0;
}

bool columnFull(char grid[100][100], int n, int column)
{
  for (int i = 0; i < n; i++)
    if (grid[i][column - 1] == '0')
      return 0;
  return 1;
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

/* codul de eroare returnat de anumite apeluri */
extern int errno;

/* portul de conectare la server*/
int port = 2728;

int main(int argc, char *argv[])
{
  int sd;                    // descriptorul de socket
  struct sockaddr_in server; // structura folosita pentru conectare

  /* cream socketul */
  if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
  {
    perror("Eroare la socket().\n");
    return errno;
  }

  /* umplem structura folosita pentru realizarea conexiunii cu serverul */
  /* familia socket-ului */
  server.sin_family = AF_INET;
  /* adresa IP a serverului */
  server.sin_addr.s_addr = inet_addr("127.0.0.1");
  /* portul de conectare */
  server.sin_port = htons(port);

  /* ne conectam la server */
  if (connect(sd, (struct sockaddr *)&server, sizeof(struct sockaddr)) == -1)
  {
    perror("[client]Eroare la connect().\n");
    return errno;
  }

  int nr_jucator, linii, coloane, secventa;
  char culoare_jucator, login[31], user[256], message[256], eroare[256];
  do
  {
    if (read(sd, login, sizeof(login)) < 0)
    {
      perror("[client]Eroare la read() login message de la server.\n");
      return errno;
    }
    printf("%s", login);
    scanf("%s", user);
    if (write(sd, user, 256) < 0)
    {
      perror("[client] Eroare la write() user si parola catre server.\n");
      return errno;
    }
    read(sd, message, 256);
    printf("%s", message);
  } while (strcmp(message, "User si parola corecte!\n"));
  char welcome[256];
  if (read(sd, welcome, sizeof(welcome)) < 0)
  {
    perror("[client]Eroare la read() mesaj de la server.\n");
    return errno;
  }
  printf("%s", welcome);
  fflush(stdout);
  
  char mesaj[85];
  if (read(sd, mesaj, 85) < 0)
  {
    perror("[client]Eroare la read() mesaj de la server.\n");
    return errno;
  }

  if (!strcmp(mesaj, "[server] Primul venit, primul servit! Alege dimensiunile tablei de joc si secventa: "))
  {
    do
    {
      printf("%s", mesaj);
      scanf("%d %d %d", &linii, &coloane, &secventa);
      if (linii > secventa && coloane > secventa && linii < 25 && coloane < 25)
      {
        strcpy(eroare, "Variabile acceptate");
      }
      else
      {
        strcpy(eroare, "Variabilele nu sunt corecte");
      }

      printf("%s", eroare);
    } while (strcmp(eroare, "Variabile acceptate"));
    write(sd, &linii, sizeof(int));
    write(sd, &coloane, sizeof(int));
    write(sd, &secventa, sizeof(int));
  }
  else
  {
    read(sd, &linii, sizeof(int));
    read(sd, &coloane, sizeof(int));
    read(sd, &secventa, sizeof(int));
  }

  if (read(sd, &nr_jucator, sizeof(int)) < 0)
  {
    perror("[client]Eroare la read() numar jucator de la server.\n");
    return errno;
  }
  printf("Sunt jucatorul numarul: %d\n", nr_jucator);
  fflush(stdout);
  if (read(sd, &culoare_jucator, sizeof(char)) < 0)
  {
    perror("[client]Eroare la read() numar jucator de la server.\n");
    return errno;
  }
  printf("Culoarea mea este: %c\n", culoare_jucator);
  fflush(stdout);
  char table[100][100];
  for (int i = 0; i < 100; i++)
    for (int j = 0; j < 100; j++)
      table[i][j] = '0';
  int rand = 1;
  while (gameFinished(table, linii, coloane, secventa) == 0 && gridFull(table, linii, coloane) == 0)
  {
    if (read(sd, &rand, sizeof(int)) < 0)
    {
      perror("[client]Eroare la read() rand de la server.\n");
      return errno;
    }
    int nr;
    if (rand == nr_jucator)
    {
      fflush(stdout);
      char ms[256];
      if (read(sd, ms, 256) < 0)
      {
        perror("eroare la read() mesaj de la server\n");
        return errno;
      }
      do
      {
        printf("%s", ms);
        scanf("%d", &nr);
      } while (columnFull(table, linii, nr) == 1 || nr > coloane);
      if (write(sd, &nr, sizeof(int)) <= 0)
      {
        perror("[client]Eroare la write() spre server.\n");
        return errno;
      }
      if (read(sd, table, 100 * 100 * sizeof(char)) < 0)
      {
        perror("[client]Eroare la read() rand de la server.\n");
        return errno;
      }
      for (int i = 0; i < linii; i++)
      {
        for (int j = 0; j < coloane; j++)
          printf("%c ", table[i][j]);
        printf("\n");
        fflush(stdout);
      }
    }
    else
    {
      printf("Nu este randul meu, astept urmatoarea runda.\n");
      if (read(sd, table, 100 * 100 * sizeof(char)) < 0)
      {
        perror("[client]Eroare la read() rand de la server.\n");
        return errno;
      }
      for (int i = 0; i < linii; i++)
      {
        for (int j = 0; j < coloane; j++)
          printf("%c ", table[i][j]);
        printf("\n");
        fflush(stdout);
      }
    }
    fflush(stdout);
  }
  char result[256];
  read(sd, result, sizeof(result));
  printf("%s\n", result);
  close(sd);
}
