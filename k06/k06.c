#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#if 0
//  デバッグ用データ
#define NAP_SIZE    15

#define NUM_ITEMS   6
typedef struct {
    int price;
    int calorie;    
} Menu;

Menu ArrayItem[] = {
    {1, 2},
    {2, 3},
    {3, 1},
    {4, 4},
    {5, 8},
    {11, 15}
};
#endif

#if 1
#define NAP_SIZE    1000    //  所持金(1000円)
#define NUM_ITEMS   135     //  メニュー数   
typedef struct tagMenu{
    int id;         //  メニューのID
    char name[91];  //  メニューの名前
    char category[10];  //  カテゴリ
    char type[15];  //  タイプ
    int price;      //  価格
    int calorie;    //  カロリー
    float salt;     //  塩分量
} Menu;


int LoadData(Menu arrayItem[])
{
    FILE* fp;
    int cn = 0;
    char buf[256];

    fp = fopen("saizeriya.csv", "r");
    if(fp==NULL){
        fputs("File open error\n",stderr);
        return -1;
    }

    while(fgets(buf,sizeof(buf),fp) != NULL){
        sscanf(buf,"%d,%[^,],%[^,],%[^,],%d,%d,%f", 
            &(arrayItem[cn].id), arrayItem[cn].name, arrayItem[cn].category, arrayItem[cn].type, 
            &(arrayItem[cn].price), &(arrayItem[cn].calorie), &(arrayItem[cn].salt));
        cn++;
    }

    if(fclose(fp) == EOF){
        fputs("file close error\n",stderr);
        return -1;
    }

    return cn;
}
#endif


void DynamicProgLimited(Menu arrayItem[], int items, int nap_size)
{
    int nap_value[items+1][nap_size + 1];   //  動的計画法で作成するテーブル
    int history[items+1][nap_size + 1];     //  履歴を保存するテーブル(選択したメニューを探すときに使用)

    //　ここを実装する
    int i, j, k, ns, s, pre_j, cur_j, tp=0;

    for(i=0; i <= items; i++)
    {
        for(j=0; j <= nap_size; j++)
        {
            nap_value[i][j] = 0;
            history[i][j] = 0;
        }
    }
    for(i=1; i <= items; i++){
        for(k=1; k < arrayItem[i-1].price; k++)
        {
            nap_value[i][k] = nap_value[i-1][k];
            history[i][k] = k;
        }
        for(j=k; j <= nap_size; j++)
        {
            ns = nap_value[i-1][j];
            s = nap_value[i-1][j-arrayItem[i-1].price] + arrayItem[i-1].calorie;
            if(ns > s)
            {
                nap_value[i][j] = ns;
                history[i][j] = j;
            }
            else
            {
                nap_value[i][j] = s;
                history[i][j] = j - arrayItem[i-1].price;
            }
        }
    }
    printf("最大摂取可能カロリー : %d\n", nap_value[items][nap_size]);
    printf("menu\n");
    cur_j = nap_size;
    for(i = items; i > 0; i--)
    {
        pre_j = history[i][cur_j];
        if(pre_j != cur_j)
        {
            printf("%s\n", arrayItem[i-1].name);
        }
        cur_j = pre_j;
    }
    for(i=1; i <= items; i++)
    {
        for(j=1; j <= nap_size; j++)
        {
            if(nap_value[i][j] > nap_value[items][nap_size])
            {
                printf("calorie not max");
                break;
            }
        }
    }
    cur_j = nap_size;
    for(i = items; i > 0; i--)
    {
        pre_j=history[i][cur_j];
        if(pre_j!=cur_j)
        {
            tp=tp+arrayItem[i-1].price;
        }
        cur_j=pre_j;
    }
    if(tp>nap_size)
    {
        printf("cost over");
    }
    return;
}


int main(void)
{
    Menu* arrayItem;
    int cnt;

    arrayItem = (Menu*)malloc(sizeof(Menu) * NUM_ITEMS);
    cnt = LoadData(arrayItem);

    //  動的プログラムで最大摂取カロリーを求める
    DynamicProgLimited(arrayItem, cnt, NAP_SIZE);
    return 0;
}