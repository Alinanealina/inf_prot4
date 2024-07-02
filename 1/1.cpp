#include <iostream>
#include <time.h>
#include <fstream>
using namespace std;
const int N = 3, M = 15, k = 2, b = 5;
bool simple(long long int a)
{
    int i;
    for (i = 2; i < sqrt(a); i++)
    {
        if (a % i == 0)
            return false;
    }
    return true;
}

long long int pow_mod(long long int a, long long int n, long long int p)
{
    long long int i, k, n2 = 0, res = 1, * N2;
    /*if (!simple(p))
    {
        cout << " p не простое.\n";
        return 0;
    }*/
    for (i = 1, n2 = 1; i * 2 < n; i *= 2, n2++);
    N2 = new long long int[n2 + 1];
    for (i = 0, k = n; i <= n2; i++, k /= 2)
        N2[i] = k % 2;

    for (i = 0; i <= n2; i++)
    {
        if (i > 0)
            k = ((k % p) * (k % p)) % p;
        else
            k = a % p;
        if (N2[i] > 0)
            res = ((res % p) * (k % p)) % p;
    }
    delete[] N2;
    return res;
}

int evk(long long int a, long long int b, long long int& x, long long int& y)
{
    int i;
    long long int obm, q, U[3] = { a, 1, 0 }, V[3] = { b, 0, 1 }, T[3];
    if (a < b)
    {
        obm = a;
        a = b;
        b = obm;
    }
    while (V[0] != 0)
    {
        q = U[0] / V[0];
        for (i = 0; i < 3; i++)
        {
            if (i > 0)
                T[i] = U[i] - q * V[i];
            else
                T[i] = U[i] % V[i];
            U[i] = V[i];
            V[i] = T[i];
        }
    }
    x = U[1];
    y = U[2];
    return U[0];
}

void shuf(long long int* K, int n)
{
    int i, j, obm;
    for (i = 0; i < n; i++)
    {
        j = rand() % n;
        obm = K[i];
        K[i] = K[j];
        K[j] = obm;
    }
}

struct st { long long int c; long long int d; long long int K[k]; };
void pok()
{
    long long int i, j, l, K[M], p = 0, Kb[b];
    st a[N];
    while ((p == 0) || !simple(p))
        p = rand() % (long long int)pow(10, 9);
    for (i = 0; i < M; i++)
    {
        K[i] = rand() % (long long int)pow(10, 3);
        cout << " " << K[i];
    }
    cout << endl;

    for (i = 0; i < N; i++)
    {
        do
        {
            a[i].c = rand() % (long long int)pow(10, 9);
        } while (evk(a[i].c, p - 1, a[i].d, l) != 1);
        while (a[i].d < 0)
            a[i].d += (p - 1);
    }

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
            K[j] = pow_mod(K[j], a[i].c, p);
        shuf(K, M);
    }

    for (i = 0; i < N; i++)
    {
        cout << "\n " << i + 1 << " получил:";
        for (j = 0; j < k; j++)
        {
            a[i].K[j] = K[k * i + j];
            cout << " " << a[i].K[j];
        }
    }
    cout << "\n стол: ";
    for (i = M - 1, j = 0; j < b; i--, j++)
    {
        Kb[j] = K[i];
        cout << " " << Kb[j];
    }

    cout << "\n_____________";
    for (i = 0; i < N; i++)
    {
        cout << "\n " << i + 1 << ":";
        for (j = 0; j < N; j++)
        {
            if (i == j)
                continue;
            cout << "\n\t " << j + 1 << " снимает:";
            for (l = 0; l < k; l++)
            {
                a[i].K[l] = pow_mod(a[i].K[l], a[j].d, p);
                cout << " " << a[i].K[l];
            }
        }
    }
    cout << "\n стол:";
    for (i = 0; i < N; i++)
    {
        cout << "\n\t " << i + 1 << " снимает:";
        for (j = 0; j < b; j++)
        {
            Kb[j] = pow_mod(Kb[j], a[i].d, p);
            cout << " " << Kb[j];
        }
    }

    cout << "\n_____________";
    for (i = 0; i < N; i++)
    {
        cout << "\n " << i + 1 << " снимает и получает:";
        for (j = 0; j < k; j++)
        {
            a[i].K[j] = pow_mod(a[i].K[j], a[i].d, p);
            cout << " " << a[i].K[j];
        }
    }
    cout << "\n стол:";
    for (i = 0; i < b; i++)
        cout << " " << Kb[i];
}

int main()
{
    setlocale(LC_ALL, "Russian");
    srand(time(0));
    pok();
    return 0;
}