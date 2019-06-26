#include <stdio.h>
#include <string.h>
#include <stdlib.h>  
#include <io.h>
#define MAXVEX 20
#define INFINITY 30000
//���嶥������
typedef struct {
    char id[3];                                 //�ص�ID
    char name[20];                     //�ص�����
    char info[100];        //�ص����
    char green[4];                          //�̻�ָ��
} VexType;
//�����ڽӾ���
typedef struct {
    VexType vexs[14];            //���㼯
    int arc[14][14];      //�߼�
    int numVertexes;              //������Ŀ
    int numEdges;                 //����Ŀ
} Graph;
//������� 
typedef struct {
    int data[MAXVEX];
    int rear, front;
}CSeQueue;

Graph SGraph;   //ȫ�ֱ�������ͼ
int visited[MAXVEX];   //���ʱ�־������

//��������
void CreateGraph();       //��������ͼ
void ReadGraph ();        //�洢����ͼ
void ShowPlaces();        //չʾѧУ�����еص� 
void SearchInfo();
void InitQueue(CSeQueue *q);
int QueueEmpty(CSeQueue *q);
void DeQueue(CSeQueue *q, int *i);    //��i�����
void EnQueue(CSeQueue *q, int i);    //������Ԫ�س����У���ֵ��i
void BFS(Graph *G, int start, int end); 
void Shortcut(Graph *G);
int Locate(Graph *G, char name[]); 
void Shortconnect(Graph *G);
void AllPath();
int next(int n, int now);
int first(int n);
void DFS(int nowPoint, int count, int endPoint, int pathNumber, int path[]);
int sumCount(int n);

//�ÿն�
void InitQueue(CSeQueue *q) {
	q = (CSeQueue*)malloc(sizeof(CSeQueue));
	q->front = q->rear = 14 - 1;
}
//���
void EnQueue(CSeQueue *q, int i) {
	if((q->rear+1) % 14 == q->front) {
		printf("����");
	} else {
		q->rear = (q->rear + 1) % 14;
		q->data[q->rear] = i;
	}
} 
//����
void DeQueue(CSeQueue *q, int *i) {
	if(q->front == q->rear) {
		printf("�ӿ�");
	} else {
		q->front = (q->front + 1) % 14;
		*i = q->data[q->front];
	}
} 
//�жӿ�
int QueueEmpty(CSeQueue *q) {
	if(q->front == q->rear) return 1;
	else return 0;
}

void ReadGraph ()
{
	FILE *fp;
	int count = 0;
	if( (fp = fopen("info.txt", "rt")) == NULL ){//���ļ����ж��Ƿ����
		printf("�����ļ�ʧ�ܣ�\n\n");
		getchar(); 
	} else{
		while(!feof(fp)){  
			fscanf(fp,"%s %s %s %s", SGraph.vexs[count].id, SGraph.vexs[count].name, SGraph.vexs[count].info, SGraph.vexs[count].green); 
    		count++;
		}
	}
	fclose(fp);
}

void PrintMap() {
	printf("\t\t\t|---------------------��ѧ  У  ��  �š�-------------------------------------------------------------|\n");
	printf("\t\t\t|                     /   /       |  |                                  |  |                         |\n");
	printf("\t\t\t|                    /   /        |  |__________                        |  |                         |\n");
	printf("\t\t\t|                   /   /         |_____________������¥��              |  |                         |\n");
	printf("\t\t\t|             ��  ��  ��  ��                                            |  |                         |\n");
	printf("\t\t\t|             �� �� ѧ ¥��                                             |  |________�� �� ����       |\n");
	printf("\t\t\t|                 |    |                                                |___________����ѧ¥��       |\n");
	printf("\t\t\t|                 |    |     _____________________                                      |  |         |\n");
	printf("\t\t\t|             ��һ�� ʵ��¥��__________________   |                                     |  |         |\n");
	printf("\t\t\t|                 |    |                       |  |                                     |  |         |\n");
	printf("\t\t\t|                 |    |   _____________       |  |                                     |  |         |\n"); 
	printf("\t\t\t|              �����ӹ��̡�_____________����ѧ������ġ�                              |  |         |\n");
	printf("\t\t\t|              �� ѧ  Ժ ��                 |  |    |  |                                |  |         |\n");
	printf("\t\t\t|                 |    |                    |  |    |  |                             �����᡿        |\n");
	printf("\t\t\t|              ��ͨ�Ź��̡�_________________|  |    |  |                               ��¥��        |\n");
	printf("\t\t\t|              �� ѧ   Ժ��____________________|    |  |                                 |           |\n");
	printf("\t\t\t|                 |    |                            |  |                                 |           |\n");
	printf("\t\t\t|        _________|    |                            |  |       ������Է������������������            |\n");
	printf("\t\t\t|       |   ____�����򳡡�                          |  |             |                               |\n");
	printf("\t\t\t|       |   |        |   |                          |  |             |                               |\n");
	printf("\t\t\t|       |   |        |   |                          |  |             |                               |\n");
	printf("\t\t\t|       |   |        |   |_________________________ |  |             |                               |\n");
	printf("\t\t\t|       |   |        |    _________________________�������ݡ�--------                                |\n");
	printf("\t\t\t|       |   |        |   |                           |                                               |\n");
	printf("\t\t\t|       |   |        |   |                           |                                               |\n");
	printf("\t\t\t|       |   |        |   |                           |                                               |\n");
	printf("\t\t\t|       |   |        |   |                           |                                               |\n");
	printf("\t\t\t|       |   |        |   |                           |                                               |\n");
	printf("\t\t\t|     ����ʳ��       |   |                           |                                               |\n");
	printf("\t\t\t|     ���㳡��       |   |                           |                                               |\n");
	printf("\t\t\t|          |         |   |                           |                                               |\n");
	printf("\t\t\t|          |         |   |                           |                                               |\n");
	printf("\t\t\t|          |________������Է��_______________________|                                               |\n");
	printf("\t\t\t|                                                                                                    |\n");
	printf("\t\t\t|----------------------------------------------------------------------------------------------------|\n");
}



void Menu()
{
    system("color F0");
    char a[200] = {0};
    do{
        printf("\t\t---��ӭ���������ʵ��ѧ����У��У԰����ϵͳ---\n");
        printf("\t============================================================================\n");
        printf("\t--------�� 1.��ʾУ԰ȫ��ͼ                                       ��--------\n\n");
        printf("\t--------�� 2.��ѯУ԰�ھ���ĳһ�ص�������Ϣ                     ��--------\n\n");
        printf("\t--------�� 3.��ѯ�����ص�֮�����еļ�·��                       ��--------\n\n");
        printf("\t--------�� 4.��ѯ�����ص�֮���һ����̵ļ�·������ת�ص����٣� ��--------\n\n");
        printf("\t--------�� 5.��ѯ�����ص�֮���һ����ѷ���·�ߣ�;�й��������٣� ��--------\n\n");
        printf("\t--------�� 0.�˳�ϵͳ                                             ��--------\n\n");
        printf("\t============================================================================\n");
        printf("����0~6��ѡ���Իس�����������\n");
        gets(a);
        if ( !strcmp(a,"1") ) {
            system("CLS");
            PrintMap();
            system( "pause" );
            system("CLS");
        }
        else if ( !strcmp(a,"2") ) {
            system("CLS");
            ShowPlaces();
            SearchInfo();
            system( "pause" );
            getchar();
            system("CLS");
        }
        else if ( !strcmp(a,"3") ) {
            system("CLS");
            AllPath();
            system( "pause" );
            getchar();
            system("CLS");
        }
        else if ( !strcmp(a,"4") ) {
            system("CLS");
            ShowPlaces();
            Shortconnect(&SGraph);
            system( "pause" );
            getchar();
            system("CLS");
        }
        else if ( !strcmp(a,"5") ) {
            system("CLS");
            Shortcut(&SGraph);
            system( "pause" );
            getchar();
            system("CLS");
        }
        else if ( !strcmp(a,"0") ) ;
        else{
            printf("������Ϣ��������������\n");
            system( "pause" );
            system("CLS");
        }
    }while( strcmp(a,"0") );
}

void CreateGraph (){
    int i, j;
    SGraph.numVertexes = 14;
    SGraph.numEdges = 20;
    for (i = 0; i < SGraph.numVertexes; i++)
        for (j = 0; j < SGraph.numVertexes; j++)
            SGraph.arc[i][j] = INFINITY;         //�ڽӾ����ʼ��
    //����Ȩֵ��·��������
    SGraph.arc[0][1] = SGraph.arc[1][0] = 200;
    SGraph.arc[0][2] = SGraph.arc[2][0] = 300;
    SGraph.arc[0][11] = SGraph.arc[11][0] = 2000;
    SGraph.arc[2][3] = SGraph.arc[3][2] = 100;
    SGraph.arc[3][4] = SGraph.arc[4][3] = 50;
    SGraph.arc[3][6] = SGraph.arc[6][3] = 400;
    SGraph.arc[4][5] = SGraph.arc[5][4] = 50;
    SGraph.arc[4][6] = SGraph.arc[6][4] = 380;
    SGraph.arc[5][6] = SGraph.arc[6][5] = 420;
    SGraph.arc[5][7] = SGraph.arc[7][5] = 200;
    SGraph.arc[6][8] = SGraph.arc[8][6] = 500;
    SGraph.arc[6][13] = SGraph.arc[13][6] = 1500;
    SGraph.arc[7][8] = SGraph.arc[8][7] = 100;
    SGraph.arc[7][9] = SGraph.arc[9][7] = 300;
    SGraph.arc[7][10] = SGraph.arc[10][7] = 150;
    SGraph.arc[8][9] = SGraph.arc[9][8] = 270;
    SGraph.arc[8][13] = SGraph.arc[13][8] = 1200;
    SGraph.arc[9][10] = SGraph.arc[10][9] = 250;
    SGraph.arc[11][12] = SGraph.arc[12][11] = 100;
    SGraph.arc[12][13] = SGraph.arc[13][12] = 200;
    ReadGraph();
}

void ShowPlaces() {
	int i;
	for (i = 0; i < SGraph.numVertexes; i++)
		printf("%d. %s\n", i, SGraph.vexs[i].name);
}

void SearchInfo() {
	char name[20];
	int i, flag = 1;
	printf("������Ҫ��ѯ�ص�����ƻ��ߵص�ID���\n");
	scanf("%s", name);
	for (i = 0; i < SGraph.numVertexes; i++) {
		if ( !strcmp(name, SGraph.vexs[i].id) || !strcmp(name, SGraph.vexs[i].name) ) {
			system("CLS");
			printf("�ص����ƣ�%s\n", SGraph.vexs[i].name);
			printf("�ص��飺%s\n", SGraph.vexs[i].info);
			printf("�ص��̻�ָ����%s\n", SGraph.vexs[i].green);
			flag = 0;
			break;
		}
	}
	if (flag == 1) {
		printf("������Ϣ����\n");
	}
}


//�ڽӾ���Ĺ�ȱ�������
int FirstAdjVex(Graph G,int v)
{   //��ȡ�붥��v���ڵĵ�һ�������±� 
    int i;
    for(i = 0; i < G.numVertexes; i++)
    {
        if(G.arc[v][i]!=0 && G.arc[v][i]!=INFINITY && !visited[i])
            return i;
    }
    return -1;
}

int NextAdjVex(Graph G,int v,int w)
{   //�õ�v����һ��δ�����ʵ����ڶ����±� 
    int i;
    for(i = w; i < G.numVertexes; i++)
    {
        if(G.arc[v][i]!= 0 && G.arc[v][i]!=INFINITY && !visited[i])
            return i;
     } 
     return -1;
}

void BFS(Graph *G, int start, int end) {
    int w, i, v, pre[MAXVEX], path[MAXVEX], p, count = 0;//p����ʱ��¼ǰһ��������� 
    memset(pre, -1, sizeof(pre));
    memset(path, -1, sizeof(path));
    CSeQueue Q;
    for (i = 0; i < G->numVertexes; i++) {
        visited[i] = 0;
    }
    InitQueue(&Q);   //��ʼ��һ�����õĶ���
    EnQueue(&Q, start);
    pre[start] = -1;
    visited[start] = 1;
    while (!QueueEmpty(&Q)) {
        DeQueue(&Q, &v);
        p = v;
        w = FirstAdjVex(*G, v);
        while (w != -1) {
            //�ж����������뵱ǰ������ڱ���δ���ʹ�
            if (!visited[w]) {
                visited[w] = 1;
                pre[w] = p;
                EnQueue(&Q, w);
            }
            if (w == end) {
            	i = end;
            	while (i != -1) {
            		path[count] = pre[i];
            		count++;
            		i = pre[i];
				} 
            	printf("%s--->%s����̵ļ�·��Ϊ��", G->vexs[start].name, G->vexs[end].name);
            	for (i = count-1; i >= 0; i--)
            	{
            		if (strcmp(G->vexs[path[i]].name,"")){
						printf("->%s", G->vexs[path[i]].name);
					}
            		
				} 
				printf("->%s\n", G->vexs[end].name);
				return;
			}
            w = NextAdjVex(*G, v, w);
        }
    }
}


//Ѱ�����·��
void Shortconnect(Graph *G) {
	char place[20];
	int start, end;
	printf("���������ص�:");
	scanf("%s", place);
	start = Locate(G, place);
	printf("�������յ�ص�:");
	scanf("%s", place);
	end = Locate(G, place);
	BFS(G, start, end);
} 

void Dijkstra(Graph *G, int start, int end, int dist[], int path[][MAXVEX]) {
	//dist�����¼�������·�����ȣ�path�����¼��Ӧ·���ϵĸ�����
    int mindist, i, j, k, t = 1;
    for (i = 0; i < G->numVertexes; i++) {       //��ʼ��
        dist[i] = G->arc[start][i];
        if (G->arc[start][i] != INFINITY) {
            path[i][1] = start;
        }
    }
    path[start][0] = 1;
    for (i = 1; i < G->numVertexes; i++) {      //Ѱ�Ҹ������·��
        mindist = INFINITY;
        for (j = 0; j < G->numVertexes; j++)   //ѡ����СȨֵ��·��
            if (path[j][0] == -1 && dist[j] < mindist) {
                k = j;
                mindist = dist[j];
            }
        if (mindist == INFINITY) break;
        path[k][0] = 1;
        
        for (j = 0; j < G->arc[k][j]; j++) {  //�޸�·��
            if (path[j][0] == -1 && G->arc[k][j] < INFINITY && dist[k] + G->arc[k][j] < dist[j]) {
                    dist[j] = dist[k] + G->arc[k][j];
                t = 1;
                while (path[k][t] != -1) {     //��¼���µ����·��
                    path[j][t] = path[k][t];
                    t++;
                }
                path[j][t] = k;
                path[j][t+1] = -1;
            }
        }    
    }
	for (i = 0; i <= G->numVertexes; i++) {
		if (i == end) break;
	}
	printf("%s--->%s�����·��Ϊ����%s", G->vexs[start].name, G->vexs[end].name, G->vexs[start].name);
	for (j = 2; path[i][j] != -1; j++) 
		printf("->%s", G->vexs[path[i][j]].name);
	printf("->%s,����Ϊ%dm\n", G->vexs[end].name,dist[i]);
}

//���ݵص���ȷ���������
int Locate(Graph *G, char name[]) {
	int i;
	for (i = 0; i < G->numVertexes; i++) 
		if(!strcmp(name, G->vexs[i].name)) return i;
	return -1;
} 

//Ѱ�����·��
void Shortcut(Graph *G) {
	ShowPlaces();
	char place[20];
	int start, end;
	int dist[MAXVEX], path[MAXVEX][MAXVEX];
	memset(path, -1, sizeof(path));
	memset(dist, -1, sizeof(dist));
	printf("���������ص�:");
	scanf("%s", place);
	start = Locate(G, place);
	printf("�������յ�ص�:");
	scanf("%s", place);
	end = Locate(G, place);
	Dijkstra(G, start, end, dist, path);
} 

//���ص�n���ڵ������������С�Ľڵ� 
int first(int n)
{
	int i;
	for (i = 0; i < SGraph.numVertexes; i++)
	{
		if (SGraph.arc[n][i]!=0 && SGraph.arc[n][i]!=INFINITY )
			return i;
	}
	return 0;
}

//���ص�n���ڵ����ڵĵ�ĸ���
int sumCount(int n)
{
	int count = 0, i = 0;
	for (i = 0; i < SGraph.numVertexes; i++)
	{
		if (SGraph.arc[n][i]!=0 && SGraph.arc[n][i]!=INFINITY )
			count++;
	}
	return count;
}
 
//���ص�n���ڵ������ı�now�ڵ���Ŵ�Ľڵ�
int next(int n, int now)
{
	int i;
	for (i = now + 1; i < SGraph.numVertexes; i++)
	{
		if (SGraph.arc[n][i]!=0 && SGraph.arc[n][i]!=INFINITY )
			return i;
	}
	return 1000;  //���Ҳ����ڵ�n����һ���ڵ㣬����1000
}
 
//DFSѰ������·�� 
//countΪ����㵽��ǰ�ڵ㾭���Ľڵ���,pathNumberΪѰ�ҵ���·������ 
void DFS(int nowPoint, int count, int endPoint, int pathNumber, int path[])
{
	int i;
	visited[nowPoint] = 1;
	path[count++] = nowPoint;
	if (nowPoint == endPoint && (count) >= 1)
	{
		pathNumber++;
		printf("���������м��%d����·��Ϊ: ", pathNumber);
		for (i = 0; i < (count)-1; i++)
		{
			printf("%d-->", path[i] + 1);
		}
		printf("%d\n", path[(count)-1] + 1);
	}
	else
	{
		int k;
		for (k = first(nowPoint); k < SGraph.numVertexes; k = next(nowPoint, k))
		{
			if (visited[k] == 0)
				DFS(k, count, endPoint, pathNumber, path);
		}
	}
	visited[nowPoint] = 0;  //���ݣ������ʹ�״̬��Ϊδ����״̬ 
	(count)--;
	return;
}

void AllPath()
{
	int count = 0, pathNumber = 0, i, startPoint, endPoint, path[20];
	memset(path, -1, sizeof(path));
	for (i = 0; i < SGraph.numVertexes; i++) {
        visited[i] = 0;
    }
	for (i = 0; i < SGraph.numVertexes; i++)
		printf("%d. %s\n", i+1, SGraph.vexs[i].name);
	printf("������Ҫ�ҵ�·����������:");
	scanf("%d", &startPoint);
	printf("������Ҫ�ҵ�·����������:");
	scanf("%d", &endPoint);
	startPoint--;
	endPoint--;
	DFS(startPoint, count, endPoint, pathNumber, path);
}

int main() {
    CreateGraph();
    Menu();
}

