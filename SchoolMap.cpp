#include <stdio.h>
#include <string.h>
#include <stdlib.h>  
#include <io.h>
#define MAXVEX 20
#define INFINITY 30000
//定义顶点类型
typedef struct {
    char id[3];                                 //地点ID
    char name[20];                     //地点名称
    char info[100];        //地点介绍
    char green[4];                          //绿化指数
} VexType;
//定义邻接矩阵
typedef struct {
    VexType vexs[14];            //顶点集
    int arc[14][14];      //边集
    int numVertexes;              //顶点数目
    int numEdges;                 //边数目
} Graph;
//定义队列 
typedef struct {
    int data[MAXVEX];
    int rear, front;
}CSeQueue;

Graph SGraph;   //全局变量导游图
int visited[MAXVEX];   //访问标志的数组

//函数声明
void CreateGraph();       //创建导游图
void ReadGraph ();        //存储导游图
void ShowPlaces();        //展示学校内所有地点 
void SearchInfo();
void InitQueue(CSeQueue *q);
int QueueEmpty(CSeQueue *q);
void DeQueue(CSeQueue *q, int *i);    //将i入队列
void EnQueue(CSeQueue *q, int i);    //将队中元素出队列，赋值给i
void BFS(Graph *G, int start, int end); 
void Shortcut(Graph *G);
int Locate(Graph *G, char name[]); 
void Shortconnect(Graph *G);
void AllPath();
int next(int n, int now);
int first(int n);
void DFS(int nowPoint, int count, int endPoint, int pathNumber, int path[]);
int sumCount(int n);

//置空队
void InitQueue(CSeQueue *q) {
	q = (CSeQueue*)malloc(sizeof(CSeQueue));
	q->front = q->rear = 14 - 1;
}
//入队
void EnQueue(CSeQueue *q, int i) {
	if((q->rear+1) % 14 == q->front) {
		printf("队满");
	} else {
		q->rear = (q->rear + 1) % 14;
		q->data[q->rear] = i;
	}
} 
//出队
void DeQueue(CSeQueue *q, int *i) {
	if(q->front == q->rear) {
		printf("队空");
	} else {
		q->front = (q->front + 1) % 14;
		*i = q->data[q->front];
	}
} 
//判队空
int QueueEmpty(CSeQueue *q) {
	if(q->front == q->rear) return 1;
	else return 0;
}

void ReadGraph ()
{
	FILE *fp;
	int count = 0;
	if( (fp = fopen("info.txt", "rt")) == NULL ){//打开文件并判断是否出错
		printf("创建文件失败！\n\n");
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
	printf("\t\t\t|---------------------【学  校  北  门】-------------------------------------------------------------|\n");
	printf("\t\t\t|                     /   /       |  |                                  |  |                         |\n");
	printf("\t\t\t|                    /   /        |  |__________                        |  |                         |\n");
	printf("\t\t\t|                   /   /         |_____________【行政楼】              |  |                         |\n");
	printf("\t\t\t|             【  基  础  】                                            |  |                         |\n");
	printf("\t\t\t|             【 教 学 楼】                                             |  |________【 东 区】       |\n");
	printf("\t\t\t|                 |    |                                                |___________【教学楼】       |\n");
	printf("\t\t\t|                 |    |     _____________________                                      |  |         |\n");
	printf("\t\t\t|             【一号 实验楼】__________________   |                                     |  |         |\n");
	printf("\t\t\t|                 |    |                       |  |                                     |  |         |\n");
	printf("\t\t\t|                 |    |   _____________       |  |                                     |  |         |\n"); 
	printf("\t\t\t|              【电子工程】_____________【大学生活动中心】                              |  |         |\n");
	printf("\t\t\t|              【 学  院 】                 |  |    |  |                                |  |         |\n");
	printf("\t\t\t|                 |    |                    |  |    |  |                             【宿舍】        |\n");
	printf("\t\t\t|              【通信工程】_________________|  |    |  |                               【楼】        |\n");
	printf("\t\t\t|              【 学   院】____________________|    |  |                                 |           |\n");
	printf("\t\t\t|                 |    |                            |  |                                 |           |\n");
	printf("\t\t\t|        _________|    |                            |  |       【东升苑】————————            |\n");
	printf("\t\t\t|       |   ____【篮球场】                          |  |             |                               |\n");
	printf("\t\t\t|       |   |        |   |                          |  |             |                               |\n");
	printf("\t\t\t|       |   |        |   |                          |  |             |                               |\n");
	printf("\t\t\t|       |   |        |   |_________________________ |  |             |                               |\n");
	printf("\t\t\t|       |   |        |    _________________________【体育馆】--------                                |\n");
	printf("\t\t\t|       |   |        |   |                           |                                               |\n");
	printf("\t\t\t|       |   |        |   |                           |                                               |\n");
	printf("\t\t\t|       |   |        |   |                           |                                               |\n");
	printf("\t\t\t|       |   |        |   |                           |                                               |\n");
	printf("\t\t\t|       |   |        |   |                           |                                               |\n");
	printf("\t\t\t|     【美食】       |   |                           |                                               |\n");
	printf("\t\t\t|     【广场】       |   |                           |                                               |\n");
	printf("\t\t\t|          |         |   |                           |                                               |\n");
	printf("\t\t\t|          |         |   |                           |                                               |\n");
	printf("\t\t\t|          |________【旭日苑】_______________________|                                               |\n");
	printf("\t\t\t|                                                                                                    |\n");
	printf("\t\t\t|----------------------------------------------------------------------------------------------------|\n");
}



void Menu()
{
    system("color F0");
    char a[200] = {0};
    do{
        printf("\t\t---欢迎进入西安邮电大学长安校区校园导游系统---\n");
        printf("\t============================================================================\n");
        printf("\t--------☆ 1.显示校园全景图                                       ☆--------\n\n");
        printf("\t--------☆ 2.查询校园内具体某一地点的相关信息                     ☆--------\n\n");
        printf("\t--------☆ 3.查询两个地点之间所有的简单路径                       ☆--------\n\n");
        printf("\t--------☆ 4.查询两个地点之间的一条最短的简单路径（中转地点最少） ☆--------\n\n");
        printf("\t--------☆ 5.查询两个地点之间的一条最佳访问路线（途中公里数最少） ☆--------\n\n");
        printf("\t--------☆ 0.退出系统                                             ☆--------\n\n");
        printf("\t============================================================================\n");
        printf("请在0~6中选择，以回车键结束输入\n");
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
            printf("输入信息有误，请重新输入\n");
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
            SGraph.arc[i][j] = INFINITY;         //邻接矩阵初始化
    //输入权值（路程米数）
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
	printf("请输入要查询地点的名称或者地点ID序号\n");
	scanf("%s", name);
	for (i = 0; i < SGraph.numVertexes; i++) {
		if ( !strcmp(name, SGraph.vexs[i].id) || !strcmp(name, SGraph.vexs[i].name) ) {
			system("CLS");
			printf("地点名称：%s\n", SGraph.vexs[i].name);
			printf("地点简介：%s\n", SGraph.vexs[i].info);
			printf("地点绿化指数：%s\n", SGraph.vexs[i].green);
			flag = 0;
			break;
		}
	}
	if (flag == 1) {
		printf("输入信息有误\n");
	}
}


//邻接矩阵的广度遍历操作
int FirstAdjVex(Graph G,int v)
{   //获取与顶点v相邻的第一个顶点下标 
    int i;
    for(i = 0; i < G.numVertexes; i++)
    {
        if(G.arc[v][i]!=0 && G.arc[v][i]!=INFINITY && !visited[i])
            return i;
    }
    return -1;
}

int NextAdjVex(Graph G,int v,int w)
{   //得到v的下一个未被访问的相邻顶点下标 
    int i;
    for(i = w; i < G.numVertexes; i++)
    {
        if(G.arc[v][i]!= 0 && G.arc[v][i]!=INFINITY && !visited[i])
            return i;
     } 
     return -1;
}

void BFS(Graph *G, int start, int end) {
    int w, i, v, pre[MAXVEX], path[MAXVEX], p, count = 0;//p是临时记录前一个顶点的量 
    memset(pre, -1, sizeof(pre));
    memset(path, -1, sizeof(path));
    CSeQueue Q;
    for (i = 0; i < G->numVertexes; i++) {
        visited[i] = 0;
    }
    InitQueue(&Q);   //初始化一辅助用的队列
    EnQueue(&Q, start);
    pre[start] = -1;
    visited[start] = 1;
    while (!QueueEmpty(&Q)) {
        DeQueue(&Q, &v);
        p = v;
        w = FirstAdjVex(*G, v);
        while (w != -1) {
            //判断其他顶点与当前顶点存在边且未访问过
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
            	printf("%s--->%s的最短的简单路径为：", G->vexs[start].name, G->vexs[end].name);
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


//寻找最短路线
void Shortconnect(Graph *G) {
	char place[20];
	int start, end;
	printf("请输入起点地点:");
	scanf("%s", place);
	start = Locate(G, place);
	printf("请输入终点地点:");
	scanf("%s", place);
	end = Locate(G, place);
	BFS(G, start, end);
} 

void Dijkstra(Graph *G, int start, int end, int dist[], int path[][MAXVEX]) {
	//dist数组记录各条最短路径长度，path数组记录对应路径上的各顶点
    int mindist, i, j, k, t = 1;
    for (i = 0; i < G->numVertexes; i++) {       //初始化
        dist[i] = G->arc[start][i];
        if (G->arc[start][i] != INFINITY) {
            path[i][1] = start;
        }
    }
    path[start][0] = 1;
    for (i = 1; i < G->numVertexes; i++) {      //寻找各条最短路径
        mindist = INFINITY;
        for (j = 0; j < G->numVertexes; j++)   //选择最小权值的路径
            if (path[j][0] == -1 && dist[j] < mindist) {
                k = j;
                mindist = dist[j];
            }
        if (mindist == INFINITY) break;
        path[k][0] = 1;
        
        for (j = 0; j < G->arc[k][j]; j++) {  //修改路径
            if (path[j][0] == -1 && G->arc[k][j] < INFINITY && dist[k] + G->arc[k][j] < dist[j]) {
                    dist[j] = dist[k] + G->arc[k][j];
                t = 1;
                while (path[k][t] != -1) {     //记录最新的最短路径
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
	printf("%s--->%s的最短路线为：从%s", G->vexs[start].name, G->vexs[end].name, G->vexs[start].name);
	for (j = 2; path[i][j] != -1; j++) 
		printf("->%s", G->vexs[path[i][j]].name);
	printf("->%s,距离为%dm\n", G->vexs[end].name,dist[i]);
}

//根据地点名确定城市序号
int Locate(Graph *G, char name[]) {
	int i;
	for (i = 0; i < G->numVertexes; i++) 
		if(!strcmp(name, G->vexs[i].name)) return i;
	return -1;
} 

//寻找最短路线
void Shortcut(Graph *G) {
	ShowPlaces();
	char place[20];
	int start, end;
	int dist[MAXVEX], path[MAXVEX][MAXVEX];
	memset(path, -1, sizeof(path));
	memset(dist, -1, sizeof(dist));
	printf("请输入起点地点:");
	scanf("%s", place);
	start = Locate(G, place);
	printf("请输入终点地点:");
	scanf("%s", place);
	end = Locate(G, place);
	Dijkstra(G, start, end, dist, path);
} 

//返回第n个节点相连接序号最小的节点 
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

//返回第n个节点相邻的点的个数
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
 
//返回第n个节点相连的比now节点序号大的节点
int next(int n, int now)
{
	int i;
	for (i = now + 1; i < SGraph.numVertexes; i++)
	{
		if (SGraph.arc[n][i]!=0 && SGraph.arc[n][i]!=INFINITY )
			return i;
	}
	return 1000;  //当找不到节点n的下一个节点，返回1000
}
 
//DFS寻找所有路径 
//count为从起点到当前节点经过的节点数,pathNumber为寻找到的路径条数 
void DFS(int nowPoint, int count, int endPoint, int pathNumber, int path[])
{
	int i;
	visited[nowPoint] = 1;
	path[count++] = nowPoint;
	if (nowPoint == endPoint && (count) >= 1)
	{
		pathNumber++;
		printf("这两个城市间第%d条简单路径为: ", pathNumber);
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
	visited[nowPoint] = 0;  //回溯，将访问过状态变为未访问状态 
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
	printf("请输入要找到路径的起点序号:");
	scanf("%d", &startPoint);
	printf("请输入要找到路径的起点序号:");
	scanf("%d", &endPoint);
	startPoint--;
	endPoint--;
	DFS(startPoint, count, endPoint, pathNumber, path);
}

int main() {
    CreateGraph();
    Menu();
}

