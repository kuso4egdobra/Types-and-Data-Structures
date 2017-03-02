#include "head.h"

int find(int **Matr, int n, int *path, int *p_l)
{
    int M[n], Q[n], q_l, *path_t, p_l_t;
    path_t = malloc(sizeof(int)*n);
    if (path_t == NULL)
    {
        return -1;
    }

    for (int i=0; i < n; i++)
    {
        q_l = 0;
        p_l_t = 0;
        if (is_in_q(path_t, p_l_t, i) == 0)
        {
            for (int j=0; j < n; j++)
                M[j] = 0;
            Q[q_l++] = i;

            shir(Matr, n, i, Q, &q_l, M, path_t, &p_l_t);
        }
        /*for (int i=0; i <p_l_t; i++)
            printf("%d ", path_t[i]+1);
        printf("\n");*/
        if (p_l_t > *p_l)
        {
            *p_l = p_l_t;
            for (int i=0; i < *p_l; i++)
                path[i] = path_t[i];
        }
    }

    free(path_t);
    return 0;
}

int shir(int **Matr, int n, int num, int *Q, int *q_l, int *M, int *path, int *p_l)
{
    int d, t, t_l = *q_l;

    for (int i=0; i < n; i++)
    {
        if (Matr[num][i] == 1 && num != i)
        {
            d = M[num]+1;
            if (d > M[i])
            {
                M[i] = d;
                if (is_in_q(Q, *q_l, i) == 0)
                {
                    Q[(*q_l)++] = i;
                    shir(Matr, n, i, Q, q_l, M, path, p_l);
                }
                else if (i == Q[0])
                {
                    t_l = *q_l+1;
                    t = i;
                }
            }
        }
    }

    if (*q_l < t_l)
        Q[(*q_l)++] = t;

    if (*p_l < *q_l)
    {
        *p_l = *q_l;
        for (int i=0; i < *p_l; i++)
            path[i] = Q[i];
    }

    (*q_l)--;

    return 0;
}

int is_in_q(int *Q, int n, int i)
{
    for (int j=0; j<n; j++)
    {
        if (Q[j] == i)
            return 1;
    }

    return 0;
}

int** alloc_matr_rows(int n)
{
    int **data = calloc(n, sizeof(int*));
    if (!data)
        return NULL;

    for (int i = 0; i < n; i++)
    {
        data[i] = calloc(n, sizeof(int));
        if (!data[i])
        {
            free_matr_rows(data, n);
            return NULL;
        }
     }

    return data;
}

void free_matr_rows(int **data, int n)
{
    for (int i = 0; i < n; i++)
       free(data[i]);

    free(data);
}
