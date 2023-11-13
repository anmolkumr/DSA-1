
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#define dimension_rubiks 2
enum {
    RED = 0,
    BLUE = 1,
    WHITE = 2,
    YELLOW = 3,
    GREEN = 4,
    ORANGE = 5
};

char color(int cc){
    switch (cc)
    {
    case RED:
        return 'R';
        break;
    case BLUE:
        return 'B';
        break;
    case ORANGE:
        return 'O';
        break;
    case GREEN:
        return 'G';
        break;
    case WHITE:
        return 'W';
        break;

    default:
        return 'Y';
        break;
    }
}

typedef char face[2][2];
typedef struct {
    face face0;
    face face1;
    face face2;
    face face3;
    face face4;
    face face5;
} rubiks_t;

void intialize_cudes(rubiks_t* rubiks) {
    for (int i = 0; i < dimension_rubiks; i++) {
        for (int j = 0; j < dimension_rubiks; j++) {
            rubiks->face0[i][j] = color(RED);
            rubiks->face1[i][j] = color(BLUE);
            rubiks->face2[i][j] = color(WHITE);
            rubiks->face3[i][j] = color(YELLOW);
            rubiks->face4[i][j] = color(GREEN);
            rubiks->face5[i][j] = color(ORANGE);
        }
    }
}

void clockwise_move(face of,face cf){

    for (int i = 0; i < dimension_rubiks; i++)

    {
        for (int j = 0; j < dimension_rubiks; j++)
        {
            switch (i+j)
            {
            case 0:
                of[i][j]= cf[1][0];
                break;
            case 1:
                if (i<j){
                of[i][j]= cf[0][0];
                break;
                }
                else{
                    of[i][j] = cf[1][1];
                    break;
                }

            case 2:

                of[i][j]= cf[0][1];
                break;

            }
        }

    }

}
void anticlockwise_move(face of,face cf){

    for (int i = 0; i < dimension_rubiks; i++)

    {
        for (int j = 0; j < dimension_rubiks; j++)
        {
            switch (i+j)
            {
            case 0:
                of[i][j]= cf[0][1];
                break;
            case 1:
                if (i<j){
                of[i][j]= cf[1][1];
                break;
                }
                else{
                    of[i][j] = cf[0][0];
                    break;
                }

            case 2:

                of[i][j]= cf[1][0];
                break;

            }
        }

    }

}

void printrubiks(rubiks_t* rubiks) {
    printf("Face 0 Front face: %c %c\n", rubiks->face0[0][0], rubiks->face0[0][1]);
    printf("                   %c %c\n", rubiks->face0[1][0], rubiks->face0[1][1]);
    printf("Face 1 Top face:   %c %c\n", rubiks->face1[0][0], rubiks->face1[0][1]);
    printf("                   %c %c\n", rubiks->face1[1][0], rubiks->face1[1][1]);
    printf("Face 2 Left face:  %c %c\n", rubiks->face2[0][0], rubiks->face2[0][1]);
    printf("                   %c %c\n", rubiks->face2[1][0], rubiks->face2[1][1]);
    printf("Face 3 Right face: %c %c\n", rubiks->face3[0][0], rubiks->face3[0][1]);
    printf("                   %c %c\n", rubiks->face3[1][0], rubiks->face3[1][1]);
    printf("Face 4 Bottom face:%c %c\n", rubiks->face4[0][0], rubiks->face4[0][1]);
    printf("                   %c %c\n", rubiks->face4[1][0], rubiks->face4[1][1]);
    printf("Face 5 Back Face:  %c %c\n", rubiks->face5[0][0], rubiks->face5[0][1]);
    printf("                   %c %c\n", rubiks->face5[1][0], rubiks->face5[1][1]);
}

void move_R(rubiks_t* rubiks) {
    // Save a temporary copy of faces
    face temporary_face0, temporary_face1, temporary_face2, temporary_face3, temporary_face4, temporary_face5;
    //saving the state
    memcpy(temporary_face0, rubiks->face0, sizeof(face));
    memcpy(temporary_face1, rubiks->face1, sizeof(face));
    memcpy(temporary_face2, rubiks->face2, sizeof(face));
    memcpy(temporary_face3, rubiks->face3, sizeof(face));
    memcpy(temporary_face4, rubiks->face4, sizeof(face));
    memcpy(temporary_face5, rubiks->face5, sizeof(face));

    // Perform the R move (right face clockwise move)
    for (int i = 0; i < dimension_rubiks; i++) {
        rubiks->face0[i][1] = temporary_face4[i][1];
        rubiks->face1[i][1] = temporary_face0[i][1];
        rubiks->face4[i][1] = temporary_face5[i][0];
        rubiks->face5[i][0] = temporary_face1[1-i][1];
    }
    clockwise_move(rubiks->face3,temporary_face3);
}

void move_Rp(rubiks_t* rubiks) {
    // Save a temporary copy of the affected faces
    face temporary_face0, temporary_face1, temporary_face2, temporary_face3, temporary_face4, temporary_face5;

    memcpy(temporary_face0, rubiks->face0, sizeof(face));
    memcpy(temporary_face1, rubiks->face1, sizeof(face));
    memcpy(temporary_face2, rubiks->face2, sizeof(face));
    memcpy(temporary_face3, rubiks->face3, sizeof(face));
    memcpy(temporary_face4, rubiks->face4, sizeof(face));
    memcpy(temporary_face5, rubiks->face5, sizeof(face));

    for (int i = 0; i < dimension_rubiks; i++) {
        rubiks->face0[i][1] = temporary_face1[i][1];
        rubiks->face1[i][1] = temporary_face5[1-i][0];
        rubiks->face4[i][1] = temporary_face0[i][1];
        rubiks->face5[i][0] = temporary_face4[1-i][1];
    }
    anticlockwise_move(rubiks->face3,temporary_face3);
}

void move_U(rubiks_t* rubiks) {

    face temporary_face0, temporary_face1, temporary_face2, temporary_face3, temporary_face4, temporary_face5;

    memcpy(temporary_face0, rubiks->face0, sizeof(face));
    memcpy(temporary_face1, rubiks->face1, sizeof(face));
    memcpy(temporary_face2, rubiks->face2, sizeof(face));
    memcpy(temporary_face3, rubiks->face3, sizeof(face));
    memcpy(temporary_face4, rubiks->face4, sizeof(face));
    memcpy(temporary_face5, rubiks->face5, sizeof(face));

    for (int i = 0; i < dimension_rubiks; i++) {
        rubiks->face0[0][i] = temporary_face3[0][i];
        rubiks->face2[0][i] = temporary_face0[0][i];
        rubiks->face3[0][i] = temporary_face5[0][i];
        rubiks->face5[0][i] = temporary_face2[0][i];
    }
    clockwise_move(rubiks->face1,temporary_face1);
}

void move_Up(rubiks_t* rubiks) {

    face temporary_face0, temporary_face1, temporary_face2, temporary_face3, temporary_face4, temporary_face5;

    memcpy(temporary_face0, rubiks->face0, sizeof(face));
    memcpy(temporary_face1, rubiks->face1, sizeof(face));
    memcpy(temporary_face2, rubiks->face2, sizeof(face));
    memcpy(temporary_face3, rubiks->face3, sizeof(face));
    memcpy(temporary_face4, rubiks->face4, sizeof(face));
    memcpy(temporary_face5, rubiks->face5, sizeof(face));

    anticlockwise_move(rubiks->face1,temporary_face1);
    for (int i = 0; i < dimension_rubiks; i++) {
        rubiks->face0[0][i] = temporary_face2[0][i];
        rubiks->face2[0][i] = temporary_face5[0][i];
        rubiks->face3[0][i] = temporary_face0[0][i];
        rubiks->face5[0][i] = temporary_face3[0][i];
    }

}
void move_F(rubiks_t* rubiks) {

    face temporary_face0, temporary_face1, temporary_face2, temporary_face3, temporary_face4, temporary_face5;

    memcpy(temporary_face0, rubiks->face0, sizeof(face));
    memcpy(temporary_face1, rubiks->face1, sizeof(face));
    memcpy(temporary_face2, rubiks->face2, sizeof(face));
    memcpy(temporary_face3, rubiks->face3, sizeof(face));
    memcpy(temporary_face4, rubiks->face4, sizeof(face));
    memcpy(temporary_face5, rubiks->face5, sizeof(face));

    clockwise_move(rubiks->face0,temporary_face0);
    for (int i = 0; i < dimension_rubiks; i++) {
        rubiks->face1[1][i] = temporary_face2[1-i][1];
        rubiks->face2[i][1] = temporary_face4[0][i];
        rubiks->face3[i][0] = temporary_face1[1][i];
        rubiks->face4[0][i] = temporary_face3[1-i][0];
    }

}
void move_Fp(rubiks_t* rubiks) {

    face temporary_face0, temporary_face1, temporary_face2, temporary_face3, temporary_face4, temporary_face5;

    memcpy(temporary_face0, rubiks->face0, sizeof(face));
    memcpy(temporary_face1, rubiks->face1, sizeof(face));
    memcpy(temporary_face2, rubiks->face2, sizeof(face));
    memcpy(temporary_face3, rubiks->face3, sizeof(face));
    memcpy(temporary_face4, rubiks->face4, sizeof(face));
    memcpy(temporary_face5, rubiks->face5, sizeof(face));

    anticlockwise_move(rubiks->face0,temporary_face0);
    for (int i = 0; i < dimension_rubiks; i++) {
        rubiks->face1[1][i] = temporary_face3[i][0];
        rubiks->face2[i][1] = temporary_face1[1][1-i];
        rubiks->face3[i][0] = temporary_face4[0][1-i];
        rubiks->face4[0][i] = temporary_face2[i][1];
    }

}

void move_R2(rubiks_t* rubiks){
    move_R(rubiks);
    move_R(rubiks);
}
void move_U2(rubiks_t* rubiks){
    move_U(rubiks);
    move_U(rubiks);
}
void move_F2(rubiks_t* rubiks){
    move_F(rubiks);
    move_F(rubiks);
}

int completed(rubiks_t* rubiks){
    char x= rubiks->face0[0][0];
    for (int i = 0; i < dimension_rubiks; i++)
    {
        for (int j = 0; j < dimension_rubiks; j++)
        {
            if (rubiks->face0[i][j] != x){
                return 0;
            }
        }

    }
    char y= rubiks->face1[0][0];
    for (int i = 0; i < dimension_rubiks; i++)
    {
        for (int j = 0; j < dimension_rubiks; j++)
        {
            if (rubiks->face1[i][j] != y){
                return 0;
            }
        }

    }
    char z= rubiks->face2[0][0];
    for (int i = 0; i < dimension_rubiks; i++)
    {
        for (int j = 0; j < dimension_rubiks; j++)
        {
            if (rubiks->face2[i][j] != z){
                return 0;
            }
        }

    }
    char a= rubiks->face3[0][0];
    for (int i = 0; i < dimension_rubiks; i++)
    {
        for (int j = 0; j < dimension_rubiks; j++)
        {
            if (rubiks->face3[i][j] != a){
                return 0;
            }
        }

    }
    char b= rubiks->face4[0][0];
    for (int i = 0; i < dimension_rubiks; i++)
    {
        for (int j = 0; j < dimension_rubiks; j++)
        {
            if (rubiks->face4[i][j] != b){
                return 0;
            }
        }

    }
    char c= rubiks->face5[0][0];
    for (int i = 0; i < dimension_rubiks; i++)
    {
        for (int j = 0; j < dimension_rubiks; j++)
        {
            if (rubiks->face5[i][j] != c){
                return 0;
            }
        }

    }

    return 1;

}

typedef struct state_of_rubiks {
    rubiks_t rubiks;
    char moves[50];//Storing the memories
} state_of_rubiks;

typedef struct QueueNode {
    state_of_rubiks state;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
} Queue;

void initializing_queue(Queue* queue) {
    queue->front = NULL;
    queue->rear = NULL;
}

void enqueue(Queue* queue, state_of_rubiks state) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->state = state;
    newNode->next = NULL;
    if (queue->rear == NULL) {
        queue->front = newNode;
        queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

state_of_rubiks dequeue(Queue* queue) {
    if (queue->front == NULL) {
        state_of_rubiks emptyState;
        return emptyState;
    }
    state_of_rubiks state = queue->front->state;
    QueueNode* temp = queue->front;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(temp);
    return state;
}

bool check_solved(rubiks_t* rubiks) {
    // checking here the colors(If same or not)
    return completed(rubiks);
}

void solve_rubiks(rubiks_t* initialrubiks, int * count) {
    Queue queue;
    initializing_queue(&queue);
    int a =1;
    state_of_rubiks inital_state;
    inital_state.rubiks = *initialrubiks;
    memset(inital_state.moves, 0, sizeof(inital_state.moves));

    enqueue(&queue, inital_state);

    while (queue.front) {
        state_of_rubiks current_state = dequeue(&queue);

        if (check_solved(&current_state.rubiks)) {

            printf("Solved! Sequence of moves: %s\n", current_state.moves);
            return;
        }
        state_of_rubiks childState = current_state;

        strcat(childState.moves, "R ");
        move_R(&childState.rubiks);
        enqueue(&queue, childState);

        state_of_rubiks childState1 = current_state;
        strcat(childState1.moves, "U ");
        move_U(&childState1.rubiks);
        enqueue(&queue, childState1);

        state_of_rubiks childState3 = current_state;
        strcat(childState3.moves, "F ");
        move_F(&childState3.rubiks);
        enqueue(&queue, childState3);

        state_of_rubiks childState4 = current_state;
        strcat(childState4.moves, "Rp ");
        move_Rp(&childState4.rubiks);
        enqueue(&queue, childState4);

        state_of_rubiks childState5 = current_state;
        strcat(childState5.moves, "Up ");
        move_Up(&childState5.rubiks);
        enqueue(&queue, childState5);

        state_of_rubiks childState6 = current_state;
        strcat(childState6.moves, "Fp ");
        move_Fp(&childState6.rubiks);
        enqueue(&queue, childState6);

        state_of_rubiks childState7 = current_state;
        strcat(childState7.moves, "R2 ");
        move_R2(&childState7.rubiks);
        enqueue(&queue, childState7);

        state_of_rubiks childState8 = current_state;
        strcat(childState8.moves, "U2 ");
        move_U2(&childState8.rubiks);
        enqueue(&queue, childState8);

        state_of_rubiks childState2 = current_state;
        strcat(childState2.moves, "F2 ");
        move_F2(&childState2.rubiks);
        enqueue(&queue, childState2);

        a+=9;

    }

    printf("Unable to solve the 2x2x2 rubiks.\n");
}

int main(int argc, char const *argv[]) {
    rubiks_t rubiks;
    int count= 0;
    intialize_cudes(&rubiks);
    move_R2(&rubiks);
    move_Fp(&rubiks);
    move_Up(&rubiks);
    move_Fp(&rubiks);
    move_F(&rubiks);
    move_Up(&rubiks);
    move_R(&rubiks);
    move_Rp(&rubiks);
    move_U2(&rubiks);
    move_F(&rubiks);
    move_R2(&rubiks);
    printrubiks(&rubiks);
    //Print the rubiks
    printf("Calculating moves....");
    solve_rubiks(&rubiks,&count);

    return 0;
}