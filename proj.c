/*402415078 沈上荏 408415073 侯建邦*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define max_time 20     //定義counter最大值

typedef struct storage {
    int ID;
    int Type;
    int arrival_time;
    struct storage* next;
}item;

typedef struct {
    int count;
    struct storage* front;
    struct storage* rear;
}queue;

queue* create();    //創造一個queue 其中 front = NULL, rear = NULL, and count = 0
void enqueue(queue*, int, int, int);    // 把資料插在queue末端
void dequeue(queue*, item**);   //讀取第一筆資料再刪除
void order(item**, int, int, int);  //根據arrival time做升序排列
int search(item*, item*);   //找出相同ID 以及 同Type且同時抵達 的資料
int check_most_item(int, int); 	//利用比較法找出一個queue中最多在等待的個數
void print_list(item*); //印出list的資料
int count(item*);   	//求得queue中的node數量

int main(void){
    
    srand(time(NULL));
    int ID, Type, arrival_time;
    int num_of_data, i;
    char filename[10];
    int Waiting_time_1 = 0, Waiting_time_2 = 0, Waiting_time_3 = 0;     //資料在queue中等待時間
    int counter = 0;        //計數器
    int process_complete_1 = 0, process_complete_2 = 0, process_complete_3 = 0;     //處理完成的資料
    int max_item_1 = 0, max_item_2 = 0, max_item_3 = 0;     //在queue中累積的資料的最大值
    int deque_num_1 = 0, deque_num_2 = 0, deque_num_3 = 0;  //計算已dequeue的數量
    int q1_counter = 100, q2_counter = 100, q3_counter = 100;   //處理器的計數器
    int time_p1, time_p2, time_p3;  //設定處理器的處理時間
    int count_1, count_2, count_3;  //計算當前queue中的資料個數
    
    queue* Q1 = create();   //創造一個queue
    queue* Q2 = create();
    queue* Q3 = create();
    item* I = NULL;
    item* data_reader_1 = malloc(sizeof(item));     //接收dequeue出來的資料
    item* data_reader_2 = malloc(sizeof(item));
    item* data_reader_3 = malloc(sizeof(item));
    item* processor_1 = NULL;
    item* processor_2 = NULL;
    item* processor_3 = NULL;

    FILE* filepointer;
    
    printf("Set processor 1 process time:");
    scanf("%d", &time_p1);
    printf("Set processor 2 process time:");
    scanf("%d", &time_p2);
    printf("Set processor 3 process time:");
    scanf("%d", &time_p3);

    printf("Please enter the number of data to generate: ");
    scanf("%d", &num_of_data);
    printf("Please enter the name of file to store: ");
    scanf("%s", filename);

    filepointer = fopen(filename, "w");

    for (i = 0; i < num_of_data; ++i) {
        fprintf(filepointer, "%d %d %d\n", rand() % 1000, rand() % 3 + 1, rand() % 20);
    }
    fclose(filepointer);

    filepointer = fopen(filename, "r");
    while (fscanf(filepointer, "%d %d %d", &ID, &Type, &arrival_time) != EOF) {
        order(&I, ID, Type, arrival_time);
    }
    fclose(filepointer);
    print_list(I);

    while (counter < max_time) {

        printf("\nTime:%d\n", counter);

        /*當counter值與資料的arrival time相同時 根據資料的type enqueue至對應的queue中*/
        while (I != NULL  && I->arrival_time == counter) {
            switch (I->Type) {
                case 1: {
                    enqueue(Q1, I->ID, I->Type, I->arrival_time);
                    printf("Item %d Enqueue in Q1\n", I->ID);

                    break;
                }
                case 2: {
                    enqueue(Q2, I->ID, I->Type, I->arrival_time);
                    printf("Item %d Enqueue in Q2\n", I->ID);

                    break;
                }
                case 3: {
                    enqueue(Q3, I->ID, I->Type, I->arrival_time);
                    printf("Item %d Enqueue in Q3\n", I->ID);

                    break;
                }
            }
            I = I->next;
        }
        /*判斷處理器狀態*/
        if (q1_counter == time_p1) {
            printf("Item %d in Processor 1  completed!\n", data_reader_1->ID);
            processor_1 = NULL;
            process_complete_1++; //item num of complete
        }
        if (Q1->count != 0 && processor_1 == NULL) {
            dequeue(Q1, &data_reader_1);
            processor_1 = data_reader_1;
            q1_counter = 0;
            printf("dequeue Item %d from Q1\n", data_reader_1->ID);
            deque_num_1++;
            Waiting_time_1 += counter - data_reader_1->arrival_time;
        }
        if (q1_counter < time_p1)
            printf("Item %d in Processor 1  processing...\n",data_reader_1->ID);

        if (q2_counter == time_p2) {
            printf("Item %d in Processor 2  completed!\n", data_reader_2->ID);
            processor_2 = NULL;
            process_complete_2++; //item num of complete
        }
        if (Q2->count != 0 && processor_2 == NULL) {
            dequeue(Q2, &data_reader_2);
            processor_2 = data_reader_2;
            q2_counter = 0;
            printf("dequeue Item %d from Q2\n", data_reader_2->ID);
            deque_num_2++;
            Waiting_time_2 += counter - data_reader_2->arrival_time;
        }
        if (q2_counter < time_p2)
            printf("Item %d in Processor 2  processing...\n", data_reader_2->ID);

        if (q3_counter == time_p3) {
            printf("Item %d in Processor 3  completed!\n", data_reader_3->ID);
            processor_3 = NULL;
            process_complete_3++; //item num of complete
        }
        if (Q3->count != 0 && processor_3 == NULL) {
            dequeue(Q3, &data_reader_3);
            processor_3 = data_reader_3;
            q3_counter = 0;
            printf("dequeue Item %d from Q3\n", data_reader_3->ID);
            deque_num_3++;
            Waiting_time_3 += counter - data_reader_3->arrival_time;
        }
        if (q3_counter < time_p3)
            printf("Item %d in Processor 3  processing...\n", data_reader_3->ID);

        count_1 = count(Q1->front);
        count_2 = count(Q2->front);
        count_3 = count(Q3->front);
        max_item_1 = check_most_item(count_1, max_item_1);
        max_item_2 = check_most_item(count_2, max_item_2);
        max_item_3 = check_most_item(count_3, max_item_3);

        counter++;
        q1_counter++;
        q2_counter++;
        q3_counter++;
    }

    printf("\nQ1 has processed %d items\nQ2 has processed %d items\nQ3 has processed %d items\n", process_complete_1, process_complete_2, process_complete_3);
    printf("\nQ1 Max items: %d \nQ2 Max items: %d \nQ3 Max items: %d \n", max_item_1, max_item_2, max_item_3);
    printf("\nAverage waiting time of Q1: %f\nAverage waiting time of Q2: %f \nAverage waiting time of Q3: %f\n", (float)Waiting_time_1 / deque_num_1, (float)Waiting_time_2 / deque_num_2, (float)Waiting_time_3 / deque_num_3);

    free(data_reader_1);
    free(data_reader_2);
    free(data_reader_3);
    return 0;
}

queue* create(void) {
    queue* node;
    node = malloc(sizeof(queue));

    node->front = NULL;
    node->rear = NULL;
    node->count = 0;
    return node;

}

void enqueue(queue* Q, int ID, int Type, int time) {
    item* I;
    I = malloc(sizeof(item));
    I->ID = ID;
    I->Type = Type;
    I->arrival_time = time;
    I->next = NULL;

    if (Q->count == 0) 
        Q->front = I;
    else 
        Q->rear->next = I;
    
    Q->rear = I;
    Q->count++;
}

void dequeue(queue* Q, item** temp) {
    item* del;
    if (Q->count == 0)
        return;
    else {
        (*temp)->ID = Q->front->ID;
        (*temp)->Type = Q->front->Type;
        (*temp)->arrival_time = Q->front->arrival_time;
        del = Q->front;
        if (Q->count == 1) {
            Q->front = NULL;
            Q->rear = NULL;
        }
        else
            Q->front = Q->front->next;
        Q->count--;
    }
    free(del);

}

void order(item** I, int ID, int Type, int time) {
    item* temp;
    item* current;
    current = *I;

    temp = malloc(sizeof(item));
    temp->ID = ID;
    temp->Type = Type;
    temp->arrival_time = time;
    temp->next = NULL;

    if (*I == NULL) {
        *I = temp;
    }
    else if ((*I)->arrival_time > temp->arrival_time && search(*I, temp) != -1) {
        temp->next = *I;
        *I = temp;
    }
    else {
        if (search(*I, temp) != -1) {
            while (current->next != NULL && (current->next)->arrival_time < temp->arrival_time) {
                current = current->next;
            }
            temp->next = current->next;
            current->next = temp;
        }
    }

}

int search(item* I, item* temp) {
    item* current = I;
    while (current->next != NULL) {
        if (current->ID == temp->ID || (current->Type == temp->Type && current->arrival_time == temp->arrival_time))
            return -1;
        else
            current = current->next;
    }
    return 1;
}

int check_most_item(int old, int new) {
    if (old > new)
        return old;
    else
        return new;
}

void print_list(item* I) {
    while (I != NULL) {
        printf("%3d %3d %4d\n", I->ID, I->Type, I->arrival_time);
        I = I->next;
    }
}

int count(item* I) {
    int num = 0;
    while (I != NULL) {
        num++;
        I = I->next;
    }
    return num;
}
