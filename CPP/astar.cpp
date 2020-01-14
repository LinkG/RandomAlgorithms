#include <iostream>
#include <math.h>
#include <fstream>
#include <stdio.h>
#include "sortArray.H"

#define prntln(x) std::cout << x << '\n'
#define prnt(x) std::cout << x

struct  vertex {
    int pos[2];
    int gscore;
    int fscore;
    vertex *parent;
};

bool comparer(vertex v1, vertex v2) {
    return v2.fscore > v1.fscore;
}

bool equality(vertex v1, vertex v2) {
    return v1.pos[0] == v2.pos[0] && v1.pos[1] == v2.pos[1];
}


int get_dist(vertex &v1, vertex &v2) {
    return abs(v1.pos[0] - v2.pos[0]) + abs(v1.pos[1] - v2.pos[1]);
}

int main(int argc, char const *argv[])
{
    int i, j;
    //prnt("Enter file name: ");
    //char filen[50];
    std::ifstream input("input.txt", std::ios::in);
    int r, c;
    input >> r >> c;
    char** map = new char*[r];
    vertex start, end;
    for(i = 0; i < r; i++) {
        map[i] = new char[j];
        for(j = 0; j < c; j++) {
            input >> map[i][j];
            if(map[i][j] == 'S') {
                start.pos[0] = i;
                start.pos[1] = j;
            } else if(map[i][j] == 'E') {
                end.pos[0] = i;
                end.pos[1] = j;
                end.gscore = get_dist(end, start);
            }
        }
    }

    sortArray<vertex> openlist(&comparer, &equality);
    sortArray<vertex> closedlist(&comparer, &equality);

    int d[][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

    vertex *final_v;

    openlist.insert(start);
    while(openlist.len > 0) {
        vertex *current = openlist.pop();
        if(equality(*current, end)) {
            final_v = current;
            break;
        }
        int cpos[2] = {current->pos[0], current->pos[1]};
        for(int i = 0; i < 4; i++) {
            int newk[2] = {cpos[0] + d[i][0], cpos[1] + d[i][1]};
            //Check legality
            if( (newk[0] < 0) || (newk[0] >= r) || (newk[1] < 0) || (newk[1] >= c) || map[newk[0]][newk[1]] == 'B' ) {
                continue;
            }
            vertex succ = {{newk[0], newk[1]}, current->gscore + 1, 0, current};
            int h = get_dist(succ, end);
            succ.fscore = succ.gscore + h;
            if(openlist.find_check(succ) || closedlist.find_check(succ)) {
                continue;
            }
            openlist.insert(succ);
        }

        closedlist.insert(*current);
    }

    while(final_v->gscore != 0) {
        prntln(final_v->pos[0] << ", " << final_v->pos[1]);
        final_v = final_v->parent;
    }
    prntln("OK");
    return 0;
}
