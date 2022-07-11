// TH05_ChuTrinhHamilton.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#define V 5
using namespace std;

bool kiemtraFiletontai(ifstream& fi) {
    bool cotontai = true;
    bool khongtontai = fi.fail();
    if (khongtontai == true) {
        cotontai = false;
    }
    return cotontai;
}

void docfile(ifstream& fi, int** a, int n)
{
    int x, i;
    while (!fi.eof())
    {
        fi >> i;
        while (true)
        {
            fi >> x;
            if (x > 0)
                a[i][x] = 1;
            if (fi.eof())
                break;
            char c;
            fi.get(c);
            char ch[2] = { c };
            if (strcmp(ch, " ") != 0)
            {
                break;
            }
        }
    }
}


void xuatmatranke(int** a, int n, int graph[V][V]) {
    int tmp;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            tmp = a[i][j];
            a[i][j] = graph[i][j];
            graph[i][j] = tmp;
            cout << graph[i][j] << " ";
        } cout << endl;
    }
}

void printSolution(int path[]);

bool isSafe(int v, int graph[V][V],
    int path[], int pos)
{
    // kiểm tra xem đỉnh này có phải đỉnh liền kề của v hay không
    if (graph[path[pos - 1]][v] == 0)
        return false;

    // kiểm tra xem đỉnh này đã bao gồm trong đường đi chưa?
    for (int i = 0; i < pos; i++)
        if (path[i] == v)
            return false;

    return true;
}

bool hamCycleUtil(int graph[V][V],
    int path[], int pos)
{
    // nếu tất cả các đỉnh bao gồm trong chu trình hamilton
    if (pos == V)
    {
        // và nếu như có một cạnh cuối cùng trong đường đi đã bao gồm đỉnh đầu tiên
        if (graph[path[pos - 1]][path[0]] == 1)
            return true;
        else
            return false;
    }

    for (int v = 1; v <= V; v++)
    {
        // Kiểm tra xem có thể thêm đỉnh này vào Chu trình Hamilton hay không 
        if (isSafe(v, graph, path, pos))
        {
            path[pos] = v;
            // lặp lại để tạo đường đi tiếp theo
            if (hamCycleUtil(graph, path, pos + 1) == true)
                return true;
            // Nếu thêm đỉnh v không tạo thành đường đi, loại bỏ nó
            path[pos] = -1;
        }
    }
    // Nếu không có đỉnh nào có thể được thêm vào Chu kỳ Hamilton cho tới chỗ này, trả về false
    return false;
}

int hamCycle(int graph[V][V])
{
    int* path = new int[V];
    for (int i = 1; i <= V; i++)
        path[i] = -1;

    path[0] = 1;
    if (hamCycleUtil(graph, path, 1) == false)
    {
        cout << "\nKhong ton tai duong di";
        return false;
    }

    printSolution(path);
    return true;
}

void printSolution(int path[])
{
    cout << "Ton tai chu trinh Hamilton:" << " Duoi day la chu trinh Hamilton \n";
    for (int i = 0; i < V; i++)
        cout << path[i] << " ";

    cout << path[0] << " ";
    cout << endl;
}



int main()
{
    cout << "BT5: Bieu dien do thi --- 2051120333/Tcheng Nhu Quan\n";
    ifstream fi("data.txt");
    kiemtraFiletontai(fi);
    if (kiemtraFiletontai(fi) == true) {
        cout << "File ton tai\n";
    }
    else {
        cout << "Loi. File khong ton tai!\n";
    }

    int n = 0;
    fi >> n;
    string s;
    getline(fi, s);

    int** a = new int* [n + 1];
    for (int i = 1; i <= n; i++)
        a[i] = new int[n + 1];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) a[i][j] = 0;

    docfile(fi, a, n);
    cout << "Xuat ma tran ke cua do thi la: " << endl;
    fi.close();
    int graph[V][V];
    xuatmatranke(a, n, graph); 
    hamCycle(graph);
    for (int i = 1; i <= n; i++)
        delete[] a[i];
    delete[] a;
    return 0;
}