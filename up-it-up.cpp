
#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <tuple>
#include <cmath>
#include <queue>
#include <assert.h>
#include <cstdint>
#include <queue>
using namespace std;

struct board
{
    int arr[3][3];
};

enum
{
    X = 1,
    O = 2
};

void init_board(const board &board)
{
    for (int r = 0; r < 3; r++)
    {
        for (int c = 0; c < 3; c++)
        {
            cout << board.arr[r][c] << " ";
        }
        cout << endl;
    }
    return;
}

pair<int, int> find_space(const board &board)
{
    int r = 0, c = 0;
    for (r = 0; r < 3; r++)
    {
        for (c = 0; c < 3; c++)
        {
            if (board.arr[r][c] == 0)
            {
                return make_pair(r, c);
            }
        }
    }
    assert(0);
}
bool checkvalidity(const board &board)
{

    for (int r = 0; r < 3; r++)
    {
        for (int c = 0; c < 3; c++)
        {
            if (board.arr[r][c] > 1)
            {
                return false;
            }
            if ((r * c == 1))
            {
                if (board.arr[1][1] != 0)
                {
                    return false;
                }
            }
        }
    }
    return true;
}

int ord(const board &board)
{
    int o = 0;
    int i = 0;
    for (int r = 0; r < 3; r++)
    {
        for (int c = 0; c < 3; c++)
        {
            o += board.arr[r][c] * pow(7, i);
            i++;
        }
    }
    return o;
}
board up(board b, int r, int c)
{
    board new_board = b;
    int val = b.arr[r - 1][c];
    if (val == 1)
    {
        val = 6;
    }
    else if (val == 2)
    {
        val = 5;
    }
    else if (val == 5)
    {
        val = 1;
    }
    else if (val == 6)
    {
        val = 2;
    }
    new_board.arr[r][c] = val;
    new_board.arr[r - 1][c] = 0;

    return new_board;
}

board turn_down(const board &b, int r, int c)
{
    board new_board = b;
    int val = b.arr[r + 1][c];
    if (val == 1)
    {
        val = 5;
    }
    else if (val == 2)
    {
        val = 6;
    }
    else if (val == 5)
    {
        val = 2;
    }
    else if (val == 6)
    {
        val = 1;
    }
    new_board.arr[r][c] = val;
    new_board.arr[r + 1][c] = 0;
    return new_board;
}

board turn_left(const board &b, int r, int c)
{
    board new_board = b;
    int val = b.arr[r][c - 1];
    if (val == 1)
    {
        val = 4;
    }
    else if (val == 2)
    {
        val = 3;
    }
    else if (val == 3)
    {
        val = 1;
    }
    else if (val == 4)
    {
        val = 2;
    }
    new_board.arr[r][c] = val;
    new_board.arr[r][c - 1] = 0;
    return new_board;
}

board turn_right(const board &b, int r, int c)
{
    board new_board = b;
    int val = b.arr[r][c + 1];
    if (val == 1)
    {
        val = 3;
    }
    else if (val == 2)
    {
        val = 4;
    }
    else if (val == 3)
    {
        val = 2;
    }
    else if (val == 4)
    {
        val = 1;
    }
    new_board.arr[r][c] = val;
    new_board.arr[r][c + 1] = 0;
    return new_board;
}

uint8_t visited[40353600] = {0};
uint64_t parent[40353600];

vector<char> solve(const board &b)
{
    int count = 0;
    queue<board> q;
    q.push(b);
    visited[ord(b)] = 'S'; // Starts Solving
    while (!q.empty())
    {
        board u = q.front();
        q.pop();
        if (checkvalidity(u))
        {
            vector<char> moves;
            int o = ord(u);
            while (visited[o] != 'S')
            {
                moves.push_back(visited[o]);
                o = parent[o];
            }
            std::reverse(moves.begin(), moves.end());
            init_board(u);
            return moves;
        }

        auto p = find_space(u);
        int row = p.first;
        int col = p.second;
        board a, b, c, d;
        if (row != 0)
        {
            a = up(u, row, col); // move upper box down
            int aord = ord(a);
            if (!visited[aord])
            {
                visited[aord] = 'U';
                parent[aord] = ord(u);
                q.push(a);
                count++;
            }
        } // here
        if (row != 2)
        {
            b = turn_down(u, row, col);
            int bord = ord(b);
            if (!visited[bord])
            {
                visited[bord] = 'D';
                parent[bord] = ord(u);
                q.push(b);
                count++;
            }
        }
        if (col != 0)
        {
            c = turn_left(u, row, col);
            int cord = ord(c);
            if (!visited[cord])
            {
                visited[cord] = 'L';
                parent[cord] = ord(u);
                q.push(c);
                count++;
            }
        }
        if (col != 2)
        {
            d = turn_right(u, row, col);
            int dord = ord(d);
            if (!visited[dord])
            {
                visited[dord] = 'R';
                parent[dord] = ord(u);
                q.push(d);
                count++;
            }
        }
    }
    vector<char> v;
    v.push_back(0);
    return v;
}

void read_board(board &b)
{ // T B L R U D
    for (int r = 0; r < 3; r++)
    { // 1 2 3 4 5 6 0
        for (int c = 0; c < 3; c++)
        {
            if (r * c == 1)
            {
                b.arr[r][c] = 0;
            }
            else
            {
                int val = 2;
                assert(val != 0);
                b.arr[r][c] = val;
            }
        }
    }
    return;
}

int main()
{
    board b; // give board
    read_board(b);
    init_board(b);
    auto moves = solve(b);
    if (moves[0] == 0)
    {
        cout << "The board is unsolvable";
    }
    for (char c : moves)
    {
        cout << c << endl;
    }
    return 0;
}
