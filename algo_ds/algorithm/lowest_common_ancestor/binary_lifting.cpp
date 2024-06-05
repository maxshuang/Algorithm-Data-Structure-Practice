#if 0

#include <bits/stdc++.h>
using namespace std;
const int N=500005,M=500005; //N存储节点总数,M存储边的总数
struct edge{
    int to, next;
}e[M*2]; //链状数组
int head[N],deep[N],fa[N][22],lg2[N];//head[]为每个节点的起始边，deep[]记录深度
//fa[i][j]表示i的2^j级祖先
//lg2数组记录log2(i), 用来记录在特定深度下最多需要记录多少个父节点
int tot=0;//tot统计边数 
bool vis[N];//节点访问标记 

// 本质上就是邻接边的形式表示树，只不过用链状数组存储了所有链表
void add(int x,int y)
{
        // 从 1 开始
    e[++tot].to=y;//存储节点
    e[tot].next=head[x];//链表
    head[x]=tot;//标记节点位置
}

void dfs(int x,int y=0)
{
    if(vis[x]) return;//已经访问过，则已经得到deep和fa数组，返回 
    vis[x] = true;
    deep[x]=deep[y]+1;//x是y的儿子节点,所以要+1
    fa[x][0]=y;//fa[x][0]表示x的父亲节点,而y是x的父亲节点.
        // 因为到这里说明所有的父节点信息都被初始化过了
    for(int i=1; i<=lg2[deep[x]]; i++) //因为x的2^i级祖先最多是根，则2^i<=deep[x],i<=lg2[deep[x]] 
        fa[x][i]=fa[fa[x][i-1]][i-1];//状态转移 2^i=2^(i-1)+2^(i-1)
         // 链状数组访问子结点方式
         for(int i=head[x]; i; i=e[i].next)
        dfs(e[i].to, x);//访问儿子节点,并且标记自己是父亲节点
}

int LCA(int x,int y)
{
    if(deep[x]<deep[y])//不妨让x节点是在y下方的节点
        swap(x,y);//交换,维持性质
    while(deep[x] != deep[y])//当我们还没有使得节点同样深度
        x=fa[x][lg2[deep[x]-deep[y]]];//往上面跳跃,deep[x]-deep[y]是高度差. // lg2() 是最大的 1 对应的值
    if(x==y)//发现Lca(x,y)=y
        return x;//返回吧,找到了...
         // depth 可以分解成 2 进制，所以从最大的步子跳再逐步变小肯定能跳到
         // 4(2^2) => (2+1)+1,  3 => (2) + 1
         for(int k=lg2[deep[x]]; k>=0; k--) //如何在x,y不相遇的情况下跳到尽可能高的位置？如果找到了这个位置，它的父亲就是LCA了
        if(fa[x][k]!=fa[y][k]) //如果发现x,y节点还没有上升到最近公共祖先节点，公共祖先节点以上的节点都是相同的
        {
            x=fa[x][k];//当然要跳跃
            y=fa[y][k];//当然要跳跃
        }
    return fa[x][0];//必须返回x的父亲节点,也就是Lca(x,y)
}
 
int main()
{
    int n,m,s,x,y;
    scanf("%d%d%d",&n,&m,&s);//n个节点,m次询问,s为根节点
    for(int i=1; i<n; i++) //n-1条边
    {
        scanf("%d%d",&x,&y);//读入边
        add(x,y);//建立边
        add(y,x);//建立无向图，为什么这里是双向的？
    }
    for(int i=2; i<=n; i++)
        lg2[i]=lg2[i/2]+1;//处理log数组的关系
    dfs(s);//dfs预处理得到深度信息和祖先关系 
    for(int i=1; i<=m; i++)
    {
        scanf("%d%d",&x,&y);//读入需要查询的节点
        printf("%d\n",LCA(x,y));//输出查询的结果
    }
    return 0;
}

#endif