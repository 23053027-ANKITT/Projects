#include <conio.h>
#include <Windows.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <stack>
#include <unordered_map>
using namespace std;

class MAZE_SOLVER {
    public:
        vector<vector<char>> maze = {
            {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
            {'#','B',' ',' ',' ',' ','#',' ',' ',' ',' ','#','#','#','#','#','#','#','#','#'},
            {'#','#','#',' ','#','#','#',' ','#','#',' ','#','#','#','b','o','t','#','#','#'},
            {'#',' ',' ',' ',' ',' ',' ','#',' ','#',' ','#','#','#','#','#','#','#','#','#'},
            {'#',' ','#','#',' ',' ','#',' ',' ','#',' ','#','e','s','c','a','p','e','!','#'},
            {'#',' ',' ','#','#',' ',' ',' ',' ','#',' ','#','#','#','#','#','#','#','#','#'},
            {'#',' ','#','#','#',' ','#',' ',' ','#',' ','#','#','#','#','#','#','#','#','#'},
            {'#','#','#',' ',' ',' ','#','#','#','#',' ','#','b','o','t',':','B','#','#','#'},
            {'#',' ',' ',' ','#',' ',' ',' ',' ',' ',' ','#','#','#','#','#','#','#','#','#'},
            {'#','#','#',' ','#','#','#','#','#','#',' ','#','e','x','i','t',':','E','#','#'},
            {'#','#','#','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#','#','#'},
            {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#','#','#','#','#','#','#','#'},
            {'#','#','#',' ','#','#','#',' ','#','#',' ','#','t','h','e','#','b','o','t','#'},
            {'#',' ',' ',' ',' ',' ',' ','#',' ','#',' ','#','c','a','n','#','s','e','e','#'},
            {'#',' ','#','#',' ',' ','#',' ',' ','#',' ','#','o','n','l','y','#','i','n','#'},
            {'#',' ',' ','#','#',' ',' ',' ',' ','#',' ','#','u','p','#','d','o','w','n','#'},
            {'#',' ','#','#','#',' ','#',' ',' ','#',' ','#','l','e','f','t','#','#','#','#'},
            {'#','#','#',' ',' ',' ','#','#','#','#',' ','#','r','i','g','h','t','#','#','#'},
            {'#','E',' ',' ','#',' ',' ',' ',' ','#',' ','#','#','#','#','#','#','#','#','#'},
            {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'}
        };
        void print_maze(vector<vector<char>> maze) {
            system("cls");
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            for (int i = 0; i < maze.size(); i++) {
                for (int j = 0; j < maze[i].size(); j++) {
                    if (maze[i][j] == '#') cout << (char)254 << "  ";
                    if (maze[i][j] == ' ') cout << ".  ";
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                    if (maze[i][j] == 'B') cout << (char)254 << "  ";
                    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
                    if (maze[i][j] == 'E') cout << (char)254 << "  ";
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE);
                    if (maze[i][j] == 'V') cout << "V" << "  ";
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                    if (islower(maze[i][j])) cout << maze[i][j] << "  ";
                    if (maze[i][j] == ':' or maze[i][j] == '!') cout << maze[i][j] << "  ";
            }
            cout << endl;
            }
        }

        void BOT(vector<vector<char>>& maze, int x, int y, stack<pair<int, int>>& memory, unordered_map<int, unordered_map<int, bool>>& visited) {
            Sleep(250);
            vector<pair<int, int>> moves = {{x + 1, y}, {x, y + 1}, {x - 1, y}, {x, y - 1}};
            for (auto move : moves) {
                if (maze[move.first][move.second] == 'E') {
                    maze[move.first][move.second] = 'V';
                    print_maze(maze);
                    cout << "\nVICTORY!" << endl;
                    return;
                }
            }
            vector<pair<int, int>> valid_moves;
            valid_moves.clear();
            for (auto move : moves) {
                if (maze[move.first][move.second] == ' ' && !visited[move.first][move.second]) {
                    valid_moves.push_back(move);
                }
            }
            if (valid_moves.size() == 1) {
                int new_x = valid_moves[0].first;
                int new_y = valid_moves[0].second;
                maze[new_x][new_y] = 'B';
                maze[x][y] = ' ';
                memory.push({new_x, new_y});
                visited[new_x][new_y] = true;
                print_maze(maze);
                BOT(maze, new_x, new_y, memory, visited);
            } else if (valid_moves.size() > 1) {
                srand(time(NULL));
                int random_index = rand() % valid_moves.size();
                int new_x = valid_moves[random_index].first;
                int new_y = valid_moves[random_index].second;
                maze[new_x][new_y] = 'B';
                maze[x][y] = ' ';
                memory.push({new_x, new_y});
                visited[new_x][new_y] = true;
                print_maze(maze);
                BOT(maze, new_x, new_y, memory, visited);
            } else { //backtracking algorithm
                //if memory is empty print no exit available
                if (memory.size() == 1) {
                    cout << "\nNo exit available..." << endl;
                    return;
                }
                memory.pop();
                auto itr = memory.top();
                int prev_x = itr.first;
                int prev_y = itr.second;
                maze[x][y] = ' '; // restore current cell to empty space
                maze[prev_x][prev_y] = 'B'; // restore previous cell to bot
                print_maze(maze);
                BOT(maze, prev_x, prev_y, memory, visited);
            }
        }
};

int main() {
    MAZE_SOLVER Maze;
    unordered_map<int, unordered_map<int, bool>> visited;
    stack<pair<int, int>> memory;
    Maze.print_maze(Maze.maze);
    cout << endl;
    memory.push({1, 1}); // starting position
    visited[1][1] = true;
    cout << "Press <ENTER> to Start: ";
    _getch();
    Maze.BOT(Maze.maze, 1, 1, memory, visited);
}