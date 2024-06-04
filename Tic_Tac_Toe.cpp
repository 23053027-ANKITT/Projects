#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <time.h>
#include <stdlib.h>
#include <math.h>
using namespace std;

void GRID(vector<vector<char>> &grid) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (j != 2) cout << grid[i][j] << " | ";
            else cout << grid[i][j];
        }
        if (i != 2) cout << "\n---------\n";
        else cout << endl;
    }
}

bool USER(vector<vector<char>> &grid) {
    int x, y;
    cout << "\nEnter the row and column of the cell you want to mark 'x' (in the form of <x> <y>): ";
    cin >> x >> y;
    cout << "\nUser turn -> \n" << endl;
    if (grid[x][y] == ':') {
        grid[x][y] = 'x';
        GRID(grid);
        //Checking for win
        string str = "";
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                str += grid[i][j];
            }
            if (str == "xxx") return true;
            str = "";
        }
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                str += grid[j][i];
            }
            if (str == "xxx") return true;
            str = "";
        }
        if (grid[0][0] == 'x' and grid[1][1] == 'x' and grid[2][2] == 'x') return true;
        if (grid[0][2] == 'x' and grid[1][1] == 'x' and grid[2][0] == 'x') return true;
    }
    else USER(grid);
    return false;
}

bool AI(vector<vector<char>> &grid) {
    cout << "\nComputer turn -> \n" << endl;
    //Winning Logic
    string str = "";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            str += grid[i][j];
        }
        if (str == "oo:" or str == "o:o" or str == ":oo") {
            for (int k = 0; k < 3; k++) {
                if (grid[i][k] == ':') {
                    grid[i][k] = 'o';
                    GRID(grid);
                    return true;
                }
            }
        }
        str = "";
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            str += grid[j][i];
        }
        if (str == "oo:" or str == "o:o" or str == ":oo") {
            for (int k = 0; k < 3; k++) {
                if (grid[k][i] == ':') {
                    grid[k][i] = 'o';
                    GRID(grid);
                    return true;
                }
            }
        }
        str = "";
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i == j) str += grid[i][j];
        }
        if (str == "oo:" or str == "o:o" or str == ":oo") {
            for (int k = 0; k < 3; k++) {
                if (grid[k][k] == ':') {
                    grid[k][k] = 'o';
                    GRID(grid);
                    return true;
                }
            }
        }
    }
    if (grid[0][2] == 'o' and grid[1][1] == 'o' and grid[2][0] == ':') {
        grid[2][0] = 'o';
        GRID(grid);
        return true;
    }
    else if (grid[0][2] == 'o' and grid[1][1] == ':' and grid[2][0] == 'o') {
        grid[1][1] = 'o';
        GRID(grid);
        return true;
    }
    else if (grid[0][2] == ':' and grid[1][1] == 'o' and grid[2][0] == 'o') {
        grid[0][2] = 'o';
        GRID(grid);
        return true;
    }
    
    //Counter Logic
    string s = "";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            s += grid[i][j];
        }
        if (s == "xx:" or s == "x:x" or s == ":xx") {
            for (int k = 0; k < 3; k++) {
                if (grid[i][k] == ':') {
                    grid[i][k] = 'o';
                    GRID(grid);
                    return false;
                }
            }
        }
        s = "";
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            s += grid[j][i];
        }
        if (s == "xx:" or s == "x:x" or s == ":xx") {
            for (int k = 0; k < 3; k++) {
                if (grid[k][i] == ':') {
                    grid[k][i] = 'o';
                    GRID(grid);
                    return false;
                }
            }
        }
        s = "";
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i == j) s += grid[i][j];
        }
        if (s == "xx:" or s == "x:x" or s == ":xx") {
            for (int k = 0; k < 3; k++) {
                if (grid[k][k] == ':') {
                    grid[k][k] = 'o';
                    GRID(grid);
                    return false;
                }
            }
        }
    }
    if (grid[0][2] == 'x' and grid[1][1] == 'x' and grid[2][0] == ':') {
        grid[2][0] = 'o';
        GRID(grid);
        return false;
    }
    else if (grid[0][2] == 'x' and grid[1][1] == ':' and grid[2][0] == 'x') {
        grid[1][1] = 'o';
        GRID(grid);
        return false;
    }
    else if (grid[0][2] == ':' and grid[1][1] == 'x' and grid[2][0] == 'x') {
        grid[0][2] = 'o';
        GRID(grid);
        return false;
    }

    //Strategy Logic
    if (grid[1][1] == ':') {
        grid[1][1] = 'o';
        GRID(grid);
        return false;
    }
    if (grid[1][1] == 'x') {
        int arr1[4][2] = {{0, 0}, {0, 2}, {2, 0}, {2, 2}};
        srand(time(NULL));
        int rand1 = rand() % 4;
        grid[arr1[rand1][0]][arr1[rand1][1]] = 'o';
        GRID(grid);
        return false;
    }
    if (grid[1][1] == 'x' and ((grid[0][0] == 'o' and grid[2][2] == 'x') or (grid[0][0] == 'x' and grid[2][2] == 'o'))) {
        int arr2[2][2] = {{0, 2}, {2, 0}};
        srand(time(NULL));
        int rand2 = rand() % 2;
        grid[arr2[rand2][0]][arr2[rand2][1]] = 'o';
        GRID(grid);
        return false;
    }
    if (grid[1][1] == 'x' and ((grid[2][0] == 'o' and grid[0][2] == 'x') or (grid[2][0] == 'x' and grid[0][2] == 'o'))) {
        int arr3[2][2] = {{0, 0}, {2, 2}};
        srand(time(NULL));
        int rand3 = rand() % 2;
        grid[arr3[rand3][0]][arr3[rand3][1]] = 'o';
        GRID(grid);
        return false;
    }
    if (grid[1][1] == 'o' and (grid[0][0] == 'x' and grid[2][2] == 'x')) {
        int arr4[4][2] = {{0, 1}, {1, 0}, {2, 1}, {1, 2}};
        srand(time(NULL));
        int rand4 = rand() % 4;
        grid[arr4[rand4][0]][arr4[rand4][1]] = 'o';
        GRID(grid);
        return false;
    }
    if (grid[1][1] == 'o' and (grid[0][2] == 'x' and grid[2][0] == 'x')) {
        int arr5[4][2] = {{0, 1}, {1, 0}, {2, 1}, {1, 2}};
        srand(time(NULL));
        int rand5 = rand() % 4;
        grid[arr5[rand5][0]][arr5[rand5][1]] = 'o';
        GRID(grid);
        return false;
    }
    
    //Random
    int x, y;
    do {
        srand(time(NULL));
        x = rand() % 3;
        y = rand() % 3;
    } while (grid[x][y] != ':');
    grid[x][y] = 'o';
    GRID(grid);
    return false;
}

int main() {
    cout << "Welcome to Tic_Tac_Toe!\n" << endl;
    cout << "Press <0> if Computer should start -OR- <1> if User should start: ";
    int choice;
    cin >> choice;

    vector<vector<char>> grid(3, vector<char>(3, ':'));
    
    int x, y, c;
    while (true) {
        if (choice == 0) {
            x = AI(grid);
            cout << endl;
            y = USER(grid);
            if (x == true) {
                cout << "\nComputer won!" << endl;
                break;
            }
            if (y == true) {
                cout << "\nUser won!" << endl;
                break;
            }
        }
        else {
            y = USER(grid);
            cout << endl;
            x = AI(grid);
            if (y == true) {
                cout << "\nUser won!" << endl;
                break;
            }
            if (x == true) {
                cout << "\nComputer won!" << endl;
                break;
            }
        }
        c = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (grid[i][j] == ':') c++;
            }
        }
        if (c == 0) {
            cout << "\nIt's a tie!" << endl;
            break;
        }
    }
    return 0;
}