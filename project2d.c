#include <stdio.h>
#include <math.h>

double b[20][20],c[20][20],f[20][20],e[20][20],g[20][20],last[20][20],d=0.85;
int n,a[20][20];

void recursion()
{
    int cvg=0,i,j;
    double tvalue;
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
        {
            g[i][1]=g[i][1]+f[i][j]*e[j][1];
        }
    }
    for(i=1;i<=n;i++)
    {
        tvalue=last[i][1]-g[i][1];
        if(tvalue>0.01)
        {
            cvg=1;
            break;
        }
    }
    if(cvg==1)
    {
        for(i=1;i<=n;i++)
        {
            e[i][1]=g[i][1];
            last[i][1]=e[i][1];
            g[i][1]=0;
        }
        return recursion();
    }
    else
    {
        return;
    }
}
int main()
{
    int i,j,k;
    double flag=0;
    printf("Please input the number of pages:");
    scanf("%d",&n);


    //First array
    for(i=1;i<=n;i++)
    {
        printf("Please input the page %d's link relationship:",i);
        for(j=1;j<=n;j++)
        {
            scanf("%d",&k);
            a[j][i]=k;//直接输出为转置矩阵的形式
        }
    }

    printf("This is the transpose matrix:\n");
    for(i=1;i<=n;i++)
    {
            for(j=1;j<=n;j++)
            {
                printf("%d ",a[i][j]);
            }
        printf("\n");
    }

    //Second array
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
        {
            if(a[j][i]==1)
            {
                flag++;   //计算每列有几个1
            }
            else
                b[j][i]=0; //赋值
        }

        //计算1的部分
        for(j=1;j<=n;j++)
        {
            if(a[j][i]==1)
            {
                b[j][i]=1/flag;    //赋值
            }
        }
        flag=0;
    }

    printf("This is the probability transition matrix:\n");
    for(i=1;i<=n;i++)
    {
            for(j=1;j<=n;j++)
            {
                printf("%lf ",b[i][j]);
            }
        printf("\n");
    }


    //Third array
    double x=n;
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
        {
            c[i][j]=1/x;
        }
    }


    printf("This is the matrix ee^t/N:\n");
    for(i=1;i<=n;i++)
    {
            for(j=1;j<=n;j++)
            {
                printf("%lf ",c[i][j]);
            }
        printf("\n");
    }


    //Fourth array
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
        {
            f[i][j]=d*b[i][j]+(1-d)*c[i][j];
        }
    }

    printf("This is the matrix B (B=d×P+(1-d)*Q/N):\n");
    for(i=1;i<=n;i++)
    {
            for(j=1;j<=n;j++)
            {
                printf("%lf ",f[i][j]);
            }
        printf("\n");
    }

    //Fifth & Sixth array
    for(i=1;i<=n;i++)
    {
        e[i][1]=1;
        g[i][1]=0;
        last[i][1]=10;
    }
    recursion();

    //final
    printf("PageRank Value is as below:\n");
    for(i=1;i<=n;i++)
    {
        printf("Page %d:%lf\n",i,g[i][1]);
    }
    return 0;
}
